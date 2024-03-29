/*******************************************************************************
################################################################################
#   Copyright (c) [2017-2019] [Radisys]                                        #
#                                                                              #
#   Licensed under the Apache License, Version 2.0 (the "License");            #
#   you may not use this file except in compliance with the License.           #
#   You may obtain a copy of the License at                                    #
#                                                                              #
#       http://www.apache.org/licenses/LICENSE-2.0                             #
#                                                                              #
#   Unless required by applicable law or agreed to in writing, software        #
#   distributed under the License is distributed on an "AS IS" BASIS,          #
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   #
#   See the License for the specific language governing permissions and        #
#   limitations under the License.                                             #
################################################################################
*******************************************************************************/
#include "common_def.h"
#include "du_tmr.h"
#include "lrg.h"
#include "lkw.x"
#include "lrg.x"
#include "legtp.h"
#include "du_app_mac_inf.h"
#include "du_app_rlc_inf.h"
#include "du_e2ap_mgr.h"
#include "du_e2ap_msg_hdl.h"
#include "du_cfg.h"
#include "du_mgr.h"
#include "du_mgr_main.h"
#include "du_utils.h"
#include "GlobalE2node-gNB-ID.h"
#include "ProtocolIE-FieldE2.h"
#include "E2setupRequest.h"
#include "InitiatingMessageE2.h"
#include "SuccessfulOutcomeE2.h"
#include "UnsuccessfulOutcomeE2.h"
#include "E2AP-PDU.h"
#include "odu_common_codec.h"
#include "E2nodeComponentInterfaceF1.h"
#include "E2setupRequest.h"
#include "du_e2_conversions.h"
#include "E2SM-KPM-RANfunction-Description.h"
#include "RANfunction-Name.h"
#include "RIC-EventTriggerStyle-Item.h"
#include "RIC-ReportStyle-Item.h"
#include "MeasurementInfo-Action-Item.h"

/*******************************************************************
 *
 * @brief Builds Global gNodeB Params
 *
 * @details
 *
 *    Function : BuildGlobalgNBId
 *
 *    Functionality: Building the Plmn and gNB id
 *
 * @params[in] GlobalE2node_gNB_ID_t *gNbId
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t BuildGlobalgNBId(GlobalE2node_gNB_ID_t *gNbId)
{
   uint8_t unused = 0;
   uint8_t byteSize = 4;
   uint8_t gnbId = duCb.gnbId;
   uint8_t ret = ROK;

   /* fill Global gNB ID Id */
   gNbId->global_gNB_ID.plmn_id.size = 3 * sizeof(uint8_t);
   gNbId->global_gNB_ID.plmn_id.buf = NULLP;
   DU_ALLOC(gNbId->global_gNB_ID.plmn_id.buf , gNbId->global_gNB_ID.plmn_id.size);
   if(gNbId->global_gNB_ID.plmn_id.buf == NULLP)
   {
      DU_LOG("\nERROR  -->  E2AP: Memory allocation failed for Plmn buffer");
      ret = RFAILED;
   }
   else
   {
      buildPlmnId(duCfgParam.srvdCellLst[0].duCellInfo.cellInfo.nrCgi.plmn, \
            gNbId->global_gNB_ID.plmn_id.buf);
      gNbId->global_gNB_ID.gnb_id.present = GNB_ID_Choice_PR_gnb_ID;
      /* Allocate Buffer size */
      gNbId->global_gNB_ID.gnb_id.choice.gnb_ID.size = byteSize * sizeof(uint8_t);
      gNbId->global_gNB_ID.gnb_id.choice.gnb_ID.buf = NULLP;
      DU_ALLOC(gNbId->global_gNB_ID.gnb_id.choice.gnb_ID.buf, \
            gNbId->global_gNB_ID.gnb_id.choice.gnb_ID.size);
      if(gNbId->global_gNB_ID.gnb_id.choice.gnb_ID.buf == NULLP)
      {
         DU_LOG("\nERROR  -->  E2AP: Memory allocation failed for gnb buffer");
         ret = RFAILED;
      }
      else
      {
         fillBitString(&gNbId->global_gNB_ID.gnb_id.choice.gnb_ID, unused, byteSize, gnbId);
      }
   }

   /* fill gNB-DU ID */ 
   DU_ALLOC( gNbId->gNB_DU_ID, sizeof(GNB_DU_ID_t));
   if(gNbId->gNB_DU_ID == NULLP)
   {
      DU_LOG("\nERROR  -->  E2AP: Memory allocation failed for gNB_DU_ID ");
      ret = RFAILED;
   }
   else
   {
      gNbId->gNB_DU_ID->size = sizeof(uint8_t);
      DU_ALLOC( gNbId->gNB_DU_ID->buf, sizeof(uint8_t));
      if(gNbId->gNB_DU_ID->buf)
      {
         gNbId->gNB_DU_ID->buf[0] =duCb.e2apDb.e2NodeId;
      }
      else
      {
         DU_LOG("\nERROR  -->  E2AP: Memory allocation failed for gNB_DU_ID buffer");
         ret = RFAILED;
      }
   }

   return ret;
}

/******************************************************************
 *
 * @brief Search E2 node component with the help of action type
 *
 * @details
 *
 *    Function : searchE2NodeComponentInfo 
 *
 *    Functionality: Search E2 node component with the help of action type 
 *
 * @params[in] uint8_t componentActionType
 * @return CmLList
 *
 * ****************************************************************/

CmLList *searchE2NodeComponentInfo(InterfaceType interfaceType, uint8_t componentActionType)
{
   E2NodeComponent *e2NodeComponentInfo;
   CmLList         *node;

   if(duCb.e2apDb.e2NodeComponentList.count)
   {
      CM_LLIST_FIRST_NODE(&duCb.e2apDb.e2NodeComponentList, node);
      while(node)
      {
         e2NodeComponentInfo = (E2NodeComponent*)node->node;
         if((e2NodeComponentInfo->interfaceType == interfaceType) && (e2NodeComponentInfo->componentActionType == componentActionType))
            break;
         else
            node = node->next;
      }
   }
   return node; 
}

/*******************************************************************
 *
 * @brief Builds E2 node config addition list 
 *
 * @details
 *
 *    Function : BuildE2NodeConfigAddList
 *
 *    Functionality: Building E2 node config addition list
 *
 * @params[in] E2nodeComponentConfigAddition_List_t *e2NodeAddList 
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t BuildE2NodeConfigAddList(E2nodeComponentConfigAddition_List_t *e2NodeAddList)
{
   uint8_t arrIdx = 0;
   CmLList         *node;
   E2NodeComponent *e2NodeComponentInfo;
   E2nodeComponentConfigAddition_ItemIEs_t *e2NodeAddItemIe;
   E2nodeComponentConfigAddition_Item_t *e2NodeAddItem;

   e2NodeAddList->list.count = 1;
   e2NodeAddList->list.size = e2NodeAddList->list.count * sizeof(E2nodeComponentConfigAddition_ItemIEs_t *);
   DU_ALLOC(e2NodeAddList->list.array, e2NodeAddList->list.size);
   if(e2NodeAddList->list.array == NULLP)
   {
       DU_LOG("\nERROR  --> E2AP: Memory allocation failed for BuildE2NodeConfigAddList %d",__LINE__);
       return RFAILED;
   }

   for(arrIdx = 0; arrIdx< e2NodeAddList->list.count; arrIdx++)
   {
      DU_ALLOC(e2NodeAddList->list.array[arrIdx], sizeof(E2nodeComponentConfigAddition_ItemIEs_t));
      if(e2NodeAddList->list.array[arrIdx] == NULLP)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed for BuildE2NodeConfigAddList %d",__LINE__);
         return RFAILED;
      }
   }
   
   node = searchE2NodeComponentInfo(F1, E2_NODE_COMPONENT_ADD);
   if(!node)
   {
      DU_LOG("\nERROR  --> E2AP : Received e2NodeComponentInfo is null");
      return RFAILED;
   }
   e2NodeComponentInfo = (E2NodeComponent*)node->node;
   
   arrIdx = 0;
   e2NodeAddItemIe = (E2nodeComponentConfigAddition_ItemIEs_t *) e2NodeAddList->list.array[arrIdx];
   e2NodeAddItemIe->id = ProtocolIE_IDE2_id_E2nodeComponentConfigAddition_Item;
   e2NodeAddItemIe->criticality = CriticalityE2_reject;
   e2NodeAddItemIe->value.present = E2nodeComponentConfigAddition_ItemIEs__value_PR_E2nodeComponentConfigAddition_Item;
   e2NodeAddItem = &e2NodeAddItemIe->value.choice.E2nodeComponentConfigAddition_Item;
   
   /* E2nodeComponentInterfaceType */
   e2NodeAddItem->e2nodeComponentInterfaceType = E2nodeComponentInterfaceType_f1;

   /* E2 Node Component Request Part */
   if(e2NodeComponentInfo->componentRequestPart)
   {
      e2NodeAddItem->e2nodeComponentConfiguration.e2nodeComponentRequestPart.size = e2NodeComponentInfo->reqBufSize ;
      DU_ALLOC(e2NodeAddItem->e2nodeComponentConfiguration.e2nodeComponentRequestPart.buf,\
            e2NodeAddItem->e2nodeComponentConfiguration.e2nodeComponentRequestPart.size);
      if(e2NodeAddItem->e2nodeComponentConfiguration.e2nodeComponentRequestPart.buf == NULLP)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed for BuildE2NodeConfigAddList %d",__LINE__);
         return RFAILED;
      }

      memcpy(e2NodeAddItem->e2nodeComponentConfiguration.e2nodeComponentRequestPart.buf,\
            e2NodeComponentInfo->componentRequestPart, e2NodeAddItem->e2nodeComponentConfiguration.\
            e2nodeComponentRequestPart.size);
   }
   else
   {
      DU_LOG("\nERROR  --> E2AP: componentRequestPart is null ");
      return RFAILED;
   }


   /* E2 Node Component Response Part */
   if(e2NodeComponentInfo->componentResponsePart)
   {
      e2NodeAddItem->e2nodeComponentConfiguration.e2nodeComponentResponsePart.size = e2NodeComponentInfo->rspBufSize; 
      DU_ALLOC(e2NodeAddItem->e2nodeComponentConfiguration.e2nodeComponentResponsePart.buf, \
            e2NodeAddItem->e2nodeComponentConfiguration.e2nodeComponentResponsePart.size);
      if(e2NodeAddItem->e2nodeComponentConfiguration.e2nodeComponentResponsePart.buf == NULLP)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed for BuildE2NodeConfigAddList %d",__LINE__);
         return RFAILED;
      }
      memcpy(e2NodeAddItem->e2nodeComponentConfiguration.e2nodeComponentResponsePart.buf, \
            e2NodeComponentInfo->componentResponsePart, e2NodeAddItem->e2nodeComponentConfiguration.\
            e2nodeComponentResponsePart.size);
   }
   else
   {
      DU_LOG("\nERROR  --> E2AP: componentResponsePart is null");
      return RFAILED;
   }
   
   /* E2 Node Component ID */
   e2NodeAddItem->e2nodeComponentID.present = E2nodeComponentID_PR_e2nodeComponentInterfaceTypeF1;
   DU_ALLOC(e2NodeAddItem->e2nodeComponentID.choice.e2nodeComponentInterfaceTypeF1,\
   sizeof(E2nodeComponentInterfaceF1_t));
   if(e2NodeAddItem->e2nodeComponentID.choice.e2nodeComponentInterfaceTypeF1 == NULLP)
   {
       DU_LOG("\nERROR  --> E2AP: Memory allocation failed for BuildE2NodeConfigAddList %d",__LINE__);
       return RFAILED;
   }
   e2NodeAddItem->e2nodeComponentID.choice.e2nodeComponentInterfaceTypeF1->gNB_DU_ID.size = sizeof(uint8_t);
   DU_ALLOC(e2NodeAddItem->e2nodeComponentID.choice.e2nodeComponentInterfaceTypeF1->gNB_DU_ID.buf,\
   e2NodeAddItem->e2nodeComponentID.choice.e2nodeComponentInterfaceTypeF1->gNB_DU_ID.size);

   if(e2NodeAddItem->e2nodeComponentID.choice.e2nodeComponentInterfaceTypeF1->gNB_DU_ID.buf == NULLP)
   {
      DU_LOG("\nERROR  -->list.  E2AP: Memory allocation failed for BuildE2NodeConfigAddList %d",__LINE__);
      return RFAILED;
   }
   e2NodeAddItem->e2nodeComponentID.choice.e2nodeComponentInterfaceTypeF1->gNB_DU_ID.buf[arrIdx]  = e2NodeComponentInfo->componentId;
   return ROK;

}

/*******************************************************************
 *
 * @brief deallocation of E2SM_KPM_RANfunction_Description_t
 *
 * @details
 *
 *    Function : freeE2smKpmRanFunctionDefinition
 *
 *    Functionality: deallocation of E2SM_KPM_RANfunction_Description_t
 *
 * @params[in]  E2SM_KPM_RANfunction_Description_t *ranFunctionDefinition
 * @return void
 *
 ******************************************************************/

void freeE2smKpmRanFunctionDefinition(E2SM_KPM_RANfunction_Description_t *ranFunctionDefinition)
{
   MeasurementInfo_Action_Item_t *measInfoList;
   uint8_t eventTriggerIdx, reportStyleIdx, measInfoIdx;
   RANfunction_Name_t *ranFuncName;
   struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List *ricReportStyle;
   struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List *eventTriggerStyle;
   if(ranFunctionDefinition)
   {
      ranFuncName = &ranFunctionDefinition->ranFunction_Name;
      /* Free RAN function Name */     
      DU_FREE(ranFuncName->ranFunction_ShortName.buf,  ranFuncName->ranFunction_ShortName.size);
      DU_FREE(ranFuncName->ranFunction_E2SM_OID.buf, ranFuncName->ranFunction_E2SM_OID.size);
      DU_FREE(ranFuncName->ranFunction_Description.buf, ranFuncName->ranFunction_Description.size);

      /* Sequence of Event Trigger styles */
      eventTriggerStyle = ranFunctionDefinition->ric_EventTriggerStyle_List;
      if(eventTriggerStyle)
      {
         if(eventTriggerStyle->list.array)
         {
            for(eventTriggerIdx =0;eventTriggerIdx<eventTriggerStyle->list.count; eventTriggerIdx++)
            {
               if(eventTriggerStyle->list.array[eventTriggerIdx])
               {
                  DU_FREE(eventTriggerStyle->list.array[eventTriggerIdx]->ric_EventTriggerStyle_Name.buf,\
                        eventTriggerStyle->list.array[eventTriggerIdx]->ric_EventTriggerStyle_Name.size);
                  DU_FREE(eventTriggerStyle->list.array[eventTriggerIdx], sizeof(RIC_EventTriggerStyle_Item_t ));
               }
            }
            DU_FREE(eventTriggerStyle->list.array, eventTriggerStyle->list.size)
         }
         DU_FREE(eventTriggerStyle, sizeof(struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List));
      }
      
      /* Sequence of Report styles */
      ricReportStyle = ranFunctionDefinition->ric_ReportStyle_List;
      if(ricReportStyle)
      {
         if(ricReportStyle->list.array)
         {
            for(reportStyleIdx =0;reportStyleIdx<ricReportStyle->list.count; reportStyleIdx++)
            {
               if(ricReportStyle->list.array[reportStyleIdx])
               {
                  if(ricReportStyle->list.array[reportStyleIdx]->ric_ReportStyle_Name.buf)
                  {
                     DU_FREE(ricReportStyle->list.array[reportStyleIdx]->ric_ReportStyle_Name.buf,\
                           ricReportStyle->list.array[reportStyleIdx]->ric_ReportStyle_Name.size);
                  }
                  if(ricReportStyle->list.array[reportStyleIdx]->measInfo_Action_List.list.array)
                  {
                     for(measInfoIdx=0; measInfoIdx<ricReportStyle->list.array[reportStyleIdx]->measInfo_Action_List.list.count; \
                           measInfoIdx++)
                     {
                        measInfoList = ricReportStyle->list.array[reportStyleIdx]->measInfo_Action_List.list.array[measInfoIdx];
                        if(measInfoList)
                        {
                           DU_FREE(measInfoList->measID, sizeof(long));
                           DU_FREE(measInfoList->measName.buf, measInfoList->measName.size);
                           DU_FREE(measInfoList,sizeof(MeasurementInfo_Action_Item_t)); 
                        }
                     }
                     DU_FREE(measInfoList,ricReportStyle->list.array[reportStyleIdx]->measInfo_Action_List.list.size);
                  }
                  DU_FREE(ricReportStyle->list.array[reportStyleIdx], sizeof(RIC_ReportStyle_Item_t));
               }
            }
            DU_FREE(ricReportStyle->list.array, ricReportStyle->list.size);
         }
         DU_FREE(ricReportStyle, sizeof(struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List));
      }
      DU_FREE(ranFunctionDefinition, sizeof(E2SM_KPM_RANfunction_Description_t)); 
   }
}

/*******************************************************************
 *
 * @brief fill the e2sm ric report style
 *
 * @details
 *
 *    Function : fillRicReportStyle
 *
 *    Functionality: fill the report style
 *
 * @params[in]   RanFunction *ranFuncDb, struct
 * E2SM_KPM_RANfunction_Description__ric_ReportStyle_List *ricReportStyle
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/
uint8_t fillRicReportStyle(RanFunction *ranFuncDb, struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List *ricReportStyle)
{
   uint8_t styleIdx, measInfoIdx;
   MeasurementInfo_Action_List_t *measInfo;
   CmLList  *node;
   
   ricReportStyle->list.count = ranFuncDb->numOfReportStyleSupported;
   ricReportStyle->list.size = ricReportStyle->list.count * sizeof(RIC_ReportStyle_Item_t*);
   DU_ALLOC(ricReportStyle->list.array, ricReportStyle->list.size);
   if(!ricReportStyle->list.array)
   {
      DU_LOG("\nERROR  --> E2AP: Memory allocation failed for ranFuncDefinition %d",__LINE__);
      return RFAILED;
   }

   for(styleIdx =0;styleIdx<ricReportStyle->list.count; styleIdx++)
   {
      DU_ALLOC(ricReportStyle->list.array[styleIdx], sizeof(RIC_ReportStyle_Item_t));
      if(!ricReportStyle->list.array[styleIdx])
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }
      
      /* RIC Report Style Type */
      ricReportStyle->list.array[styleIdx]->ric_ReportStyle_Type = ranFuncDb->reportStyleList[styleIdx].reportStyle.styleType;
      
      /* RIC Report Style Format Type */
      ricReportStyle->list.array[styleIdx]->ric_ActionFormat_Type = ranFuncDb->reportStyleList[styleIdx].reportStyle.formatType;
      
      /* RIC Report Style Name */
      ricReportStyle->list.array[styleIdx]->ric_ReportStyle_Name.size = strlen(ranFuncDb->reportStyleList[styleIdx].reportStyle.name);
      DU_ALLOC(ricReportStyle->list.array[styleIdx]->ric_ReportStyle_Name.buf,\
            ricReportStyle->list.array[styleIdx]->ric_ReportStyle_Name.size);
      if(!ricReportStyle->list.array[styleIdx]->ric_ReportStyle_Name.buf)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }
      memcpy(ricReportStyle->list.array[styleIdx]->ric_ReportStyle_Name.buf, ranFuncDb->reportStyleList[styleIdx].reportStyle.name,\
            ricReportStyle->list.array[styleIdx]->ric_ReportStyle_Name.size);

      /* RIC Indication Header Format Type*/
      ricReportStyle->list.array[styleIdx]->ric_IndicationHeaderFormat_Type = ranFuncDb->ricIndicationHeaderFormat;

      /* RIC Indication Message Format Type*/
      ricReportStyle->list.array[styleIdx]->ric_IndicationMessageFormat_Type = ranFuncDb->ricIndicationMessageFormat;
      
      /* Measurement Info Action List */
      CmLListCp measInfoList =ranFuncDb->reportStyleList[styleIdx].measurementInfoList;
      if(!measInfoList.count)
      {
         continue;      
      }

      CM_LLIST_FIRST_NODE(&ranFuncDb->reportStyleList[styleIdx].measurementInfoList, node);
      measInfo = &ricReportStyle->list.array[styleIdx]->measInfo_Action_List;

      measInfo->list.count = measInfoList.count; 
      measInfo->list.size =  measInfoList.count*sizeof(MeasurementInfo_Action_Item_t*);
      DU_ALLOC(measInfo->list.array, measInfo->list.size);
      if(!measInfo->list.array)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }

      for(measInfoIdx=0; measInfoIdx<measInfo->list.count; measInfoIdx++)
      {
         if(!node)
         {
            DU_LOG("\nERROR  --> E2AP: Measurement info node is null");
            return RFAILED;
         }

         DU_ALLOC(measInfo->list.array[measInfoIdx],sizeof(MeasurementInfo_Action_Item_t));  
         if(!measInfo->list.array[measInfoIdx])
         {
            DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
            return RFAILED;
         }
         MeasurementInfoForAction *measInfoForAction= (MeasurementInfoForAction*)node->node;
         DU_ALLOC(measInfo->list.array[measInfoIdx]->measID, sizeof(long));
         if(!measInfo->list.array[measInfoIdx]->measID)
         {
            DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
            return RFAILED;
         }
         
         memcpy(measInfo->list.array[measInfoIdx]->measID, &measInfoForAction->measurementTypeId,sizeof(long));
         measInfo->list.array[measInfoIdx]->measName.size= strlen(measInfoForAction->measurementTypeName);
         DU_ALLOC(measInfo->list.array[measInfoIdx]->measName.buf, measInfo->list.array[measInfoIdx]->measName.size);
         if(!measInfo->list.array[measInfoIdx]->measName.size)
         {
            DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
            return RFAILED;
         }

         memcpy(measInfo->list.array[measInfoIdx]->measName.buf, \
               measInfoForAction->measurementTypeName,\
               measInfo->list.array[measInfoIdx]->measName.size);
         node = node->next;
      }

   }
   return ROK;
}
/*******************************************************************
 *
 * @brief fill the ric event trigger style
 *
 * @details
 *
 *    Function : fillRicEventTriggerStyle
 *
 *    Functionality: fill the ric event trigger style
 *
 * @params[in]   
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/
uint8_t fillRicEventTriggerStyle(RanFunction *ranFuncDb, struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List *ricEventTriggerStyle)
{
   uint8_t styleIdx;

   ricEventTriggerStyle->list.count = ranFuncDb->numOfEventTriggerStyleSupported;
   ricEventTriggerStyle->list.size = ricEventTriggerStyle->list.count*  sizeof(RIC_EventTriggerStyle_Item_t *);
   DU_ALLOC(ricEventTriggerStyle->list.array, ricEventTriggerStyle->list.size);
   if(!ricEventTriggerStyle->list.array)
   {
      DU_LOG("\nERROR  --> E2AP: Memory allocation failed for ric_EventTriggerStyle_List %d",__LINE__);
      return RFAILED;
   }

   for(styleIdx =0;styleIdx<ricEventTriggerStyle->list.count; styleIdx++)
   {
      DU_ALLOC(ricEventTriggerStyle->list.array[styleIdx], sizeof(RIC_EventTriggerStyle_Item_t ));
      if(!ricEventTriggerStyle->list.array[styleIdx])
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }
      ricEventTriggerStyle->list.array[styleIdx]->ric_EventTriggerStyle_Type = ranFuncDb->eventTriggerStyleList[styleIdx].styleType;

      ricEventTriggerStyle->list.array[styleIdx]->ric_EventTriggerFormat_Type = ranFuncDb->eventTriggerStyleList[styleIdx].formatType;

      ricEventTriggerStyle->list.array[styleIdx]->ric_EventTriggerStyle_Name.size = strlen(ranFuncDb->eventTriggerStyleList[styleIdx].name);
      DU_ALLOC(ricEventTriggerStyle->list.array[styleIdx]->ric_EventTriggerStyle_Name.buf,\
            ricEventTriggerStyle->list.array[styleIdx]->ric_EventTriggerStyle_Name.size);
      if(!ricEventTriggerStyle->list.array[styleIdx]->ric_EventTriggerStyle_Name.buf)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }
      memcpy(ricEventTriggerStyle->list.array[styleIdx]->ric_EventTriggerStyle_Name.buf,ranFuncDb->eventTriggerStyleList[styleIdx].name,\
            ricEventTriggerStyle->list.array[styleIdx]->ric_EventTriggerStyle_Name.size);
   
   }
   return ROK;
}

/*******************************************************************
 *
 * @brief Builds Ran function add list
 *
 * @details
 *
 *    Function : BuildRanFunctionAddList 
 *
 *    Functionality: Building RAN addition addition list
 *
 * @params[in]  RANfunctions_List_t *RANfunctions_List 
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t BuildRanFunctionAddList(RANfunctions_List_t *ranFunctionsList)
{
   asn_enc_rval_t encRetVal;
   RanFunction *ranFuncDb;
   RANfunction_Name_t *ranFuncName;
   uint8_t ranFuncIdx;
   RANfunction_ItemIEs_t *ranFuncItemIe;
   RANfunction_Item_t  *ranFuncItem;
   E2SM_KPM_RANfunction_Description_t *ranFuncDefinition;

   ranFunctionsList->list.count = duCb.e2apDb.numOfRanFunction;
   ranFunctionsList->list.size = ranFunctionsList->list.count * sizeof(RANfunction_ItemIEs_t*);
   DU_ALLOC(ranFunctionsList->list.array, ranFunctionsList->list.size);
   if(ranFunctionsList->list.array == NULLP)
   {
      DU_LOG("\nERROR  --> E2AP: Memory allocation failed in %s at %d",__func__, __LINE__);
      return RFAILED;
   }

   for(ranFuncIdx = 0; ranFuncIdx< ranFunctionsList->list.count; ranFuncIdx++)
   {
      DU_ALLOC(ranFunctionsList->list.array[ranFuncIdx], sizeof(RANfunction_ItemIEs_t));
      if(ranFunctionsList->list.array[ranFuncIdx] == NULLP)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in %s at %d",__func__, __LINE__);
         return RFAILED;
      }

      ranFuncItemIe = (RANfunction_ItemIEs_t *) ranFunctionsList->list.array[ranFuncIdx];
      ranFuncItemIe->id = ProtocolIE_IDE2_id_RANfunction_Item;
      ranFuncItemIe->criticality = CriticalityE2_ignore;
      ranFuncItemIe->value.present = RANfunction_ItemIEs__value_PR_RANfunction_Item;
      ranFuncItem = &ranFuncItemIe->value.choice.RANfunction_Item;
      ranFuncDb = &duCb.e2apDb.ranFunction[ranFuncIdx];   
      /* RAN function Id*/
      ranFuncItem->ranFunctionID = ranFuncDb->id;
      
      /* RAN Function Revision*/
      ranFuncItem->ranFunctionRevision = ranFuncDb->revisionCounter;
      
      /* RAN function OID*/
      ranFuncItem->ranFunctionOID.size = strlen(ranFuncDb->name.serviceModelOID);
      DU_ALLOC(ranFuncItem->ranFunctionOID.buf, ranFuncItem->ranFunctionOID.size);
      if(!ranFuncItem->ranFunctionOID.buf)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }
      memcpy(ranFuncItem->ranFunctionOID.buf, ranFuncDb->name.serviceModelOID, ranFuncItem->ranFunctionOID.size);

      /* RAN function Definition */
      DU_ALLOC(ranFuncDefinition, sizeof(E2SM_KPM_RANfunction_Description_t));
      if(!ranFuncDefinition)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }
      
      /* RAN function Name */
      ranFuncName = &ranFuncDefinition->ranFunction_Name;
      
      /* RAN function ShortName */
      ranFuncName->ranFunction_ShortName.size = strlen(ranFuncDb->name.shortName); 
      DU_ALLOC(ranFuncName->ranFunction_ShortName.buf,  ranFuncName->ranFunction_ShortName.size);
      if(!ranFuncName->ranFunction_ShortName.buf)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }
      memcpy(ranFuncName->ranFunction_ShortName.buf, ranFuncDb->name.shortName, strlen(ranFuncDb->name.shortName));
      
      /* RAN function E2SM_OID */
      ranFuncName->ranFunction_E2SM_OID.size = strlen(ranFuncDb->name.serviceModelOID);
      DU_ALLOC(ranFuncName->ranFunction_E2SM_OID.buf, ranFuncName->ranFunction_E2SM_OID.size);
      if(!ranFuncName->ranFunction_E2SM_OID.buf)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }
      memcpy(ranFuncName->ranFunction_E2SM_OID.buf, ranFuncDb->name.serviceModelOID, ranFuncName->ranFunction_E2SM_OID.size);

      /* RAN function Description */
      ranFuncName->ranFunction_Description.size = strlen(ranFuncDb->name.description);
      DU_ALLOC(ranFuncName->ranFunction_Description.buf, ranFuncName->ranFunction_Description.size);
      if(!ranFuncName->ranFunction_Description.buf)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }
      memcpy(ranFuncName->ranFunction_Description.buf, ranFuncDb->name.description, ranFuncName->ranFunction_Description.size);
      
      /* RIC Event Trigger Style List */
      DU_ALLOC(ranFuncDefinition->ric_EventTriggerStyle_List, sizeof(struct E2SM_KPM_RANfunction_Description__ric_EventTriggerStyle_List));
      if(!ranFuncDefinition->ric_EventTriggerStyle_List)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }
      
      if(fillRicEventTriggerStyle(ranFuncDb, ranFuncDefinition->ric_EventTriggerStyle_List)!=ROK)
      {
         DU_LOG("\nERROR  --> E2AP: failed to fill ric event trigger style");
         return RFAILED;
      }

      /* RIC Report Style List */
      DU_ALLOC(ranFuncDefinition->ric_ReportStyle_List, sizeof(struct E2SM_KPM_RANfunction_Description__ric_ReportStyle_List));
      if(!ranFuncDefinition->ric_ReportStyle_List)
      {
         DU_LOG("\nERROR  --> E2AP: Memory allocation failed in function %s at %d",__func__,__LINE__);
         return RFAILED;
      }
      if(fillRicReportStyle(ranFuncDb, ranFuncDefinition->ric_ReportStyle_List) != ROK)
      {
         DU_LOG("\nERROR  --> E2AP: failed to fill ric report style");
         return RFAILED;
      }

      /* Encode the F1SetupRequest type as APER */
      xer_fprint(stdout, &asn_DEF_E2SM_KPM_RANfunction_Description, ranFuncDefinition);

      memset(encBuf, 0, ENC_BUF_MAX_LEN);
      encBufSize = 0;
      encRetVal = aper_encode(&asn_DEF_E2SM_KPM_RANfunction_Description, 0, ranFuncDefinition, PrepFinalEncBuf, encBuf);

      /* Encode results */
      if(encRetVal.encoded == ENCODE_FAIL)
      {
         DU_LOG("\nERROR  -->  F1AP : Could not encode RAN function definition  (at %s)\n",\
               encRetVal.failed_type ? encRetVal.failed_type->name : "unknown");
         break;
      }
      else
      {
         DU_LOG("\nDEBUG   -->  F1AP : Created APER encoded buffer for RAN function definition \n");
         for(uint8_t measIeIdx=0; measIeIdx< encBufSize; measIeIdx++)
         {
            printf("%x",encBuf[measIeIdx]);
         }

      }
      ranFuncItem->ranFunctionDefinition.size = encBufSize;
      DU_ALLOC(ranFuncItem->ranFunctionDefinition.buf, encBufSize);
      if(ranFuncItem->ranFunctionDefinition.buf == NULLP)
      {
         DU_LOG("\nERROR  -->  F1AP : Memory allocation failed for RAN function definition buffer");
         return RFAILED;
      }
      memcpy(ranFuncItem->ranFunctionDefinition.buf, &encBuf, encBufSize);
   }
   freeE2smKpmRanFunctionDefinition(ranFuncDefinition);
   return ROK;
}

/*******************************************************************
 *
 * @brief De Allocate E2 Setup Request Message
 *
 * @details
 *
 *    Function : FreeE2SetupReq
 *
 *    Functionality: De-Allocating E2 Setup request Message
 *
 * @params[in] E2AP_PDU_t *e2apMsg
 
 * @return void
 *
 * ****************************************************************/

void FreeE2SetupReq(E2AP_PDU_t *e2apMsg)
{
   uint8_t arrIdx = 0;
   uint8_t e2NodeAddListIdx =0, ranFuncAddListIdx;
   E2setupRequest_t *e2SetupReq;
   E2nodeComponentConfigAddition_List_t *e2NodeAddList;
   E2nodeComponentConfigAddition_ItemIEs_t *e2NodeAddItem;
   RANfunctions_List_t *ranFunctionsList;
   RANfunction_ItemIEs_t *ranFuncItemIe;
   RANfunction_Item_t  *ranFunItem;

   /* De-allocating Memory */
   if(e2apMsg != NULLP)
   {
      if(e2apMsg->choice.initiatingMessage != NULLP)
      {
         e2SetupReq = &e2apMsg->choice.initiatingMessage->value.choice.E2setupRequest; 
         if(e2SetupReq->protocolIEs.list.array != NULLP)
         {
            for(arrIdx = 0; arrIdx < e2SetupReq->protocolIEs.list.count; arrIdx++)
            {
               if(e2SetupReq->protocolIEs.list.array[arrIdx] != NULLP)
               {
                  switch(e2SetupReq->protocolIEs.list.array[arrIdx]->id)
                  {
                     case ProtocolIE_IDE2_id_TransactionID:
                          break;
                     case ProtocolIE_IDE2_id_GlobalE2node_ID:
                        {
                           if(e2SetupReq->protocolIEs.list.array[arrIdx]->\
                                 value.choice.GlobalE2node_ID.choice.gNB != NULLP)
                           {
                              GlobalE2node_gNB_ID_t *gNbId = NULLP;
                              gNbId = e2SetupReq->protocolIEs.list.array[arrIdx]->\
                                      value.choice.GlobalE2node_ID.choice.gNB;
                              if(gNbId->global_gNB_ID.plmn_id.buf != NULLP)
                              {
                                 DU_FREE(gNbId->global_gNB_ID.gnb_id.choice.gnb_ID.buf,\
                                       gNbId->global_gNB_ID.gnb_id.choice.gnb_ID.size);
                                 DU_FREE(gNbId->global_gNB_ID.plmn_id.buf,\
                                       gNbId->global_gNB_ID.plmn_id.size);
                              }

                              if(gNbId->gNB_DU_ID != NULLP)
                              {
                                 DU_FREE( gNbId->gNB_DU_ID->buf, gNbId->gNB_DU_ID->size);
                                 DU_FREE(gNbId->gNB_DU_ID, sizeof(GNB_DU_ID_t));
                              }
                              DU_FREE(e2SetupReq->protocolIEs.list.array[arrIdx]->value.\
                                    choice.GlobalE2node_ID.choice.gNB, sizeof(GlobalE2node_gNB_ID_t));
                           }
                           break;
                        }
                     case ProtocolIE_IDE2_id_E2nodeComponentConfigAddition:
                     {
                         e2NodeAddList = &e2SetupReq->protocolIEs.list.array[arrIdx]->value.choice.E2nodeComponentConfigAddition_List;
                         if(e2NodeAddList->list.array)
                         {
                             for(e2NodeAddListIdx = 0; e2NodeAddListIdx< e2NodeAddList->list.count; e2NodeAddListIdx++)
                             {
                                e2NodeAddItem = (E2nodeComponentConfigAddition_ItemIEs_t *) e2NodeAddList->list.array[e2NodeAddListIdx];
                                
                                /* Free E2 Node Component Request Part */
                                DU_FREE(e2NodeAddItem->value.choice.E2nodeComponentConfigAddition_Item.e2nodeComponentConfiguration.e2nodeComponentRequestPart.buf,\
                                      e2NodeAddItem->value.choice.E2nodeComponentConfigAddition_Item.e2nodeComponentConfiguration.e2nodeComponentRequestPart.size);
                                
                                /* Free E2 Node Component Response Part */
                                DU_FREE(e2NodeAddItem->value.choice.E2nodeComponentConfigAddition_Item.e2nodeComponentConfiguration.\
                                      e2nodeComponentResponsePart.buf, \
                                      e2NodeAddItem->value.choice.E2nodeComponentConfigAddition_Item.e2nodeComponentConfiguration.e2nodeComponentResponsePart.size);
                                 
                                 /* Free E2 Node Component ID */
                                if(e2NodeAddItem->value.choice.E2nodeComponentConfigAddition_Item.e2nodeComponentID.choice.e2nodeComponentInterfaceTypeF1)
                                {
                                    DU_FREE(e2NodeAddItem->value.choice.E2nodeComponentConfigAddition_Item.e2nodeComponentID.choice.\
                                    e2nodeComponentInterfaceTypeF1->gNB_DU_ID.buf,\
                                    e2NodeAddItem->value.choice.E2nodeComponentConfigAddition_Item.e2nodeComponentID.choice.\
                                    e2nodeComponentInterfaceTypeF1->gNB_DU_ID.size);
                                    DU_FREE(e2NodeAddItem->value.choice.E2nodeComponentConfigAddition_Item.e2nodeComponentID.choice.e2nodeComponentInterfaceTypeF1,\
                                    sizeof(E2nodeComponentInterfaceF1_t));
                                }
                                DU_FREE(e2NodeAddList->list.array[e2NodeAddListIdx], sizeof(E2nodeComponentConfigAddition_ItemIEs_t));
                             }
                             DU_FREE(e2NodeAddList->list.array, e2NodeAddList->list.size);
                         }
                         break;
                     }
                     case ProtocolIE_IDE2_id_RANfunctionsAdded:
                     {
                        ranFunctionsList = &(e2SetupReq->protocolIEs.list.array[arrIdx]->value.choice.RANfunctions_List);  
                        if(ranFunctionsList->list.array)
                        {  
                           for(ranFuncAddListIdx= 0; ranFuncAddListIdx< ranFunctionsList->list.count; ranFuncAddListIdx++)
                           {
                              if(ranFunctionsList->list.array[ranFuncAddListIdx])
                              {
                                 ranFuncItemIe = (RANfunction_ItemIEs_t *) ranFunctionsList->list.array[ranFuncAddListIdx];
                                 ranFunItem = &ranFuncItemIe->value.choice.RANfunction_Item;
                                 DU_FREE(ranFunItem->ranFunctionOID.buf, ranFunItem->ranFunctionOID.size);
                                 DU_FREE(ranFunItem->ranFunctionDefinition.buf, ranFunItem->ranFunctionDefinition.size);
                                 DU_FREE(ranFunctionsList->list.array[ranFuncAddListIdx], sizeof(RANfunction_ItemIEs_t));
                              }
                           }
                           DU_FREE(ranFunctionsList->list.array, ranFunctionsList->list.size);
                        }
                        break;
                     }

                     default:
                        DU_LOG("\nERROR  --> E2AP: Invalid event at e2SetupRequet %ld ",\
                              (e2SetupReq->protocolIEs.list.array[arrIdx]->id));
                        break;
                  }
                  DU_FREE(e2SetupReq->protocolIEs.list.array[arrIdx], sizeof(E2setupRequestIEs_t));
               }
            }
            DU_FREE(e2SetupReq->protocolIEs.list.array, e2SetupReq->protocolIEs.list.size);
         }
         DU_FREE(e2apMsg->choice.initiatingMessage, sizeof(InitiatingMessageE2_t));
      }
      DU_FREE(e2apMsg, sizeof(E2AP_PDU_t));
   }
}

/*******************************************************************
 *
 * @brief Builds and Send the E2SetupRequest
 *
 * @details
 *
 *    Function : BuildAndSendE2SetupReq
 *
 * Functionality:Fills the E2SetupRequest
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t BuildAndSendE2SetupReq()
{
   uint8_t arrIdx = 0, elementCnt=0;
   uint8_t transId = 0, ret = ROK;
   bool memAllocFailed;
   E2AP_PDU_t        *e2apMsg = NULLP;
   E2setupRequest_t  *e2SetupReq = NULLP;
   asn_enc_rval_t     encRetVal;       /* Encoder return value */

   DU_LOG("\nINFO   -->  E2AP : Building E2 Setup Request\n");
   do
   {
      DU_ALLOC(e2apMsg, sizeof(E2AP_PDU_t));
      if(e2apMsg == NULLP)
      {
         DU_LOG("\nERROR  -->  E2AP : Memory allocation for E2AP-PDU failed");
         break;
      }
      e2apMsg->present = E2AP_PDU_PR_initiatingMessage;
      DU_ALLOC(e2apMsg->choice.initiatingMessage, sizeof(InitiatingMessageE2_t));
      if(e2apMsg->choice.initiatingMessage == NULLP)
      {
         DU_LOG("\nERROR  -->  E2AP : Memory allocation for E2AP-PDU failed");
         break;
      }
      e2apMsg->choice.initiatingMessage->criticality = CriticalityE2_reject;
      e2apMsg->choice.initiatingMessage->procedureCode = ProcedureCodeE2_id_E2setup;
      e2apMsg->choice.initiatingMessage->value.present = InitiatingMessageE2__value_PR_E2setupRequest;
      e2SetupReq = &e2apMsg->choice.initiatingMessage->value.choice.E2setupRequest;

      elementCnt = 4;
      e2SetupReq->protocolIEs.list.count = elementCnt;
      e2SetupReq->protocolIEs.list.size = elementCnt * sizeof(E2setupRequestIEs_t*);

      /* Initialize the E2Setup members */
      DU_ALLOC(e2SetupReq->protocolIEs.list.array, \
            e2SetupReq->protocolIEs.list.size);
      if(e2SetupReq->protocolIEs.list.array == NULLP)
      {
         DU_LOG("\nERROR  -->  E2AP : Memory allocation failed for array elements");
         break;
      }
      for(arrIdx = 0; arrIdx < elementCnt; (arrIdx)++)
      {
         DU_ALLOC(e2SetupReq->protocolIEs.list.array[arrIdx],\
               sizeof(E2setupRequestIEs_t));
         if(e2SetupReq->protocolIEs.list.array[arrIdx] == NULLP)
         {
            memAllocFailed = true;
            DU_LOG("\nERROR  -->  E2AP : Memory allocation failed for arrayarrIdx [%d]", arrIdx);
            break;
         }
      }
      if(memAllocFailed == true)
         break;

      arrIdx = 0;

      /* TransactionID */
      e2SetupReq->protocolIEs.list.array[arrIdx]->id = ProtocolIE_IDE2_id_TransactionID;
      e2SetupReq->protocolIEs.list.array[arrIdx]->criticality = CriticalityE2_reject;
      e2SetupReq->protocolIEs.list.array[arrIdx]->value.present = E2setupRequestIEs__value_PR_TransactionID;
      transId = assignTransactionId();
      e2SetupReq->protocolIEs.list.array[arrIdx]->value.choice.TransactionID = transId;

      arrIdx++;
      /* GlobalE2node_gNB_ID */
      e2SetupReq->protocolIEs.list.array[arrIdx]->id = ProtocolIE_IDE2_id_GlobalE2node_ID;
      e2SetupReq->protocolIEs.list.array[arrIdx]->criticality = CriticalityE2_reject;
      e2SetupReq->protocolIEs.list.array[arrIdx]->value.present = E2setupRequestIEs__value_PR_GlobalE2node_ID;
      e2SetupReq->protocolIEs.list.array[arrIdx]->value.choice.GlobalE2node_ID.present = GlobalE2node_ID_PR_gNB;

      DU_ALLOC(e2SetupReq->protocolIEs.list.array[arrIdx]->value.choice.\
            GlobalE2node_ID.choice.gNB, sizeof(GlobalE2node_gNB_ID_t));
      if(e2SetupReq->protocolIEs.list.array[arrIdx]->value.choice.\
            GlobalE2node_ID.choice.gNB == NULLP)
      {
         DU_LOG("\nERROR  -->  E2AP : Memory allocation failed for gNbId");
         break;
      }
      else
      {
         ret = BuildGlobalgNBId(e2SetupReq->protocolIEs.list.array[arrIdx]->value.\
               choice.GlobalE2node_ID.choice.gNB);
         if(ret != ROK)
         {
             DU_LOG("\nERROR  -->  E2AP : Failed to build Global Gnb Id");
             break;
         }
      }
      
      /* RAN Functions Added List */
      arrIdx++;
      e2SetupReq->protocolIEs.list.array[arrIdx]->id = ProtocolIE_IDE2_id_RANfunctionsAdded;
      e2SetupReq->protocolIEs.list.array[arrIdx]->criticality = CriticalityE2_reject;
      e2SetupReq->protocolIEs.list.array[arrIdx]->value.present = E2setupRequestIEs__value_PR_RANfunctions_List;
      if(BuildRanFunctionAddList(&(e2SetupReq->protocolIEs.list.array[arrIdx]->value.choice.RANfunctions_List))!=ROK)
      {
         DU_LOG("\nERROR  -->  E2AP : Failed to create RAN Function");
         break;
      }

      /* E2 Node Component Configuration Addition List */
      arrIdx++;
      e2SetupReq->protocolIEs.list.array[arrIdx]->id = ProtocolIE_IDE2_id_E2nodeComponentConfigAddition;
      e2SetupReq->protocolIEs.list.array[arrIdx]->criticality = CriticalityE2_reject;
      e2SetupReq->protocolIEs.list.array[arrIdx]->value.present = E2setupRequestIEs__value_PR_E2nodeComponentConfigAddition_List;
      if(BuildE2NodeConfigAddList(&(e2SetupReq->protocolIEs.list.array[arrIdx]->value.choice.E2nodeComponentConfigAddition_List))!=ROK)
      {
         DU_LOG("\nERROR  -->  E2AP : Failed to create E2 Node config list");
         break;
      }



      /* Prints the Msg formed */
      xer_fprint(stdout, &asn_DEF_E2AP_PDU, e2apMsg);

      memset(encBuf, 0, ENC_BUF_MAX_LEN);
      encBufSize = 0;
      encRetVal = aper_encode(&asn_DEF_E2AP_PDU, 0, e2apMsg, PrepFinalEncBuf,\
            encBuf);
      if(encRetVal.encoded == ENCODE_FAIL)
      {
         DU_LOG("\nERROR  -->  E2AP : Could not encode E2SetupRequest structure (at %s)\n",\
               encRetVal.failed_type ? encRetVal.failed_type->name : "unknown");
         break;
      }
      else
      {
         DU_LOG("\nDEBUG   -->  E2AP : Created APER encoded buffer for E2SetupRequest\n");
#ifdef DEBUG_ASN_PRINT
         for(int i=0; i< encBufSize; i++)
         {
            printf("%x",encBuf[i]);
         }
#endif
      }
      if(SendE2APMsg(DU_APP_MEM_REGION, DU_POOL, encBuf, encBufSize) != ROK)
      {
         DU_LOG("\nERROR  -->  E2AP : Sending E2 Setup request failed");
      }
      break;
   }while(true);

   duCb.e2apDb.e2TransInfo.onGoingTransaction[transId].transactionId = transId;
   duCb.e2apDb.e2TransInfo.onGoingTransaction[transId].procedureCode = e2apMsg->choice.initiatingMessage->procedureCode;
   
   FreeE2SetupReq(e2apMsg);
   return ret;
}/* End of BuildAndSendE2SetupReq */

/*******************************************************************
 *
 * @brief Builds Ric Request Id
 *
 * @details
 *
 *    Function : BuildRicRequestId
 *
 *    Functionality: Building the Ric Request Id
 *
 * @params[in] RICrequestID_t *ricReqId
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t BuildRicRequestId(RICrequestID_t *ricReqId)
{
   if(ricReqId == NULLP)
   {
      return RFAILED;
   }

   ricReqId->ricRequestorID = 1;
   ricReqId->ricInstanceID  = 1;
   return ROK;
}

/*******************************************************************
 *
 * @brief Fills the mandatory RicAdmitted List Items
 *
 * @details
 *
 *    Function : fillRicAdmitList
 *
 *    Functionality: Fills the mandatory Ric Admitted List Items
 *
 * @params[in] RICaction_Admitted_ItemIEs_t *ricAdmitItems
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t fillRicAdmitList(RICaction_Admitted_ItemIEs_t *ricAdmitItems)
{

   if(ricAdmitItems != NULLP)
   {
      ricAdmitItems->id = ProtocolIE_IDE2_id_RICaction_Admitted_Item;
      ricAdmitItems->criticality = CriticalityE2_reject;
      ricAdmitItems->value.present = RICaction_Admitted_ItemIEs__value_PR_RICaction_Admitted_Item;
      ricAdmitItems->value.choice.RICaction_Admitted_Item.ricActionID = 1; 
   }
   else
   {
      return RFAILED;
   }
   return ROK;
}
/*******************************************************************
 *
 * @brief Builds the mandatory RicAdmitted List Params
 *
 * @details
 *
 *    Function : BuildRicAdmitList
 *
 *    Functionality: Builds the mandatory Ric Admitted List Params
 *
 * @params[in] RICaction_Admitted_List_t *admitListPtr
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t BuildRicAdmitList(RICaction_Admitted_List_t *admitListPtr)
{
   uint8_t idx ;
   uint8_t elementCnt;  
   uint8_t ret= ROK;
   elementCnt = 1;

   if(admitListPtr == NULLP)
   {
      DU_LOG("\nERROR  -->  E2AP : Memory allocation for RIC Admit List failed");
      ret = RFAILED;
   }
   else
   {
      admitListPtr->list.count = elementCnt;
      admitListPtr->list.size  = elementCnt * sizeof(RICaction_Admitted_ItemIEs_t);
      DU_ALLOC(admitListPtr->list.array, admitListPtr->list.size);
      if(admitListPtr->list.array == NULLP)
      {
	 DU_LOG("\nERROR  -->  E2AP : Memory allocation for RIC Admit List failed");
	 ret = RFAILED;
      }
      else
      {
	 for(idx=0 ; idx<elementCnt ; idx++ )
	 {
	    DU_ALLOC(admitListPtr->list.array[idx], sizeof(RICaction_Admitted_ItemIEs_t));
	    if(admitListPtr->list.array[idx] == NULLP)
	    {
	       ret = RFAILED;
	    }
	 }
	 if(ret != RFAILED)
	 {
	    idx=0;
	    fillRicAdmitList((RICaction_Admitted_ItemIEs_t *)admitListPtr->list.array[idx]);
	 }
      }
   }	
   return ret;
}
/*******************************************************************
 *
 * @breif Deallocation of BuildAndSendRicSubscriptionRsp memory
 *
 * @details
 *
 *    Function : FreeRicSubscriptionRsp
 *
 * Functionality:Free the RicSubscriptionRsp
 *
 * @param[in] E2AP_PDU_t *e2apRicMsg
 *
 * @return void
 *      
 *
 ******************************************************************/
void FreeRicSubscriptionRsp(E2AP_PDU_t  *e2apRicMsg)
{
   RICsubscriptionResponse_t  *ricSubscriptionRsp= NULLP;
   uint8_t idx=0;
   uint8_t idx1=0;
   RICaction_Admitted_List_t *admitListPtr;

   if(e2apRicMsg != NULLP)
   {
      if(e2apRicMsg->choice.successfulOutcome != NULLP)
      {
	 ricSubscriptionRsp = &e2apRicMsg->choice.successfulOutcome->value.choice.RICsubscriptionResponse;
	 if(ricSubscriptionRsp)
	 {
	    if(ricSubscriptionRsp->protocolIEs.list.array != NULLP)
	    {
	       for(idx=0; idx<ricSubscriptionRsp->protocolIEs.list.count; idx++)
	       {
		  if(ricSubscriptionRsp->protocolIEs.list.array[idx] != NULLP)
		  {
		     switch(ricSubscriptionRsp->protocolIEs.list.array[idx]->id)
		     {
			case ProtocolIE_IDE2_id_RICrequestID:
			   break;

			case ProtocolIE_IDE2_id_RANfunctionID:
			   break;

			case ProtocolIE_IDE2_id_RICactions_Admitted:
			   {
			      admitListPtr = &ricSubscriptionRsp->protocolIEs.list.\
					     array[idx]->value.choice.RICaction_Admitted_List;
			      if(admitListPtr->list.array != NULLP)
			      {
				 for(idx1=0 ; idx1<admitListPtr->list.count; idx1++ )
				 {
				    if(admitListPtr->list.array[idx1] != NULLP)
				    {
				       DU_FREE(admitListPtr->list.array[idx1],
					     sizeof(RICaction_Admitted_ItemIEs_t));
				    }
				 }
				 DU_FREE(admitListPtr->list.array, admitListPtr->list.size);	 
			      }
			      break;
			   }
			default:
			   break;
		     }
		     DU_FREE(ricSubscriptionRsp->protocolIEs.list.array[idx], \
			   sizeof(RICsubscriptionResponse_IEs_t));
		  }
	       }
	       DU_FREE(ricSubscriptionRsp->protocolIEs.list.array, \
		     ricSubscriptionRsp->protocolIEs.list.size);
	    }
	 }   
	 DU_FREE(e2apRicMsg->choice.successfulOutcome, sizeof(SuccessfulOutcomeE2_t));
      }		
      DU_FREE(e2apRicMsg, sizeof(E2AP_PDU_t));	      
   }
}
/*******************************************************************
 *
 * @brief Builds and Send the RicSubscriptionRsp
 *
 * @details
 *
 *    Function : BuildAndSendRicSubscriptionRsp
 *
 * functionality:Fills the RicSubscriptionRsp
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/
uint8_t  FillRicSubscriptionRsp(RICsubscriptionResponse_t  *ricSubscriptionRsp )
{
   uint8_t idx=0;
   uint8_t ret = ROK;
   uint8_t elementCnt = 0;
   uint8_t BuildRicRequestIdret=ROK;
   uint8_t BuildRicAdmitListret=ROK;

   elementCnt=3;
   ricSubscriptionRsp->protocolIEs.list.count = elementCnt;
   ricSubscriptionRsp->protocolIEs.list.size  = elementCnt * sizeof(RICsubscriptionResponse_IEs_t);
   DU_ALLOC(ricSubscriptionRsp->protocolIEs.list.array, \
	 ricSubscriptionRsp->protocolIEs.list.size);
   if(ricSubscriptionRsp->protocolIEs.list.array == NULLP)
   {
      DU_LOG("\nERROR  -->  E2AP : Memory allocation for FillRicSubscriptionRsp  failed");
      ret = RFAILED;
   }
   else
   {
      for(idx=0; idx<ricSubscriptionRsp->protocolIEs.list.count; idx++)
      {
	 DU_ALLOC(ricSubscriptionRsp->protocolIEs.list.array[idx], \
	       sizeof(RICsubscriptionResponse_IEs_t));
	 if(ricSubscriptionRsp->protocolIEs.list.array[idx] == NULLP)
	 {
	    ret = RFAILED;
	 }
      }
      if(ret != RFAILED)
      {

	 idx=0;
	 ricSubscriptionRsp->protocolIEs.list.array[idx]->id = ProtocolIE_IDE2_id_RICrequestID;
	 ricSubscriptionRsp->protocolIEs.list.array[idx]->criticality = CriticalityE2_reject;
	 ricSubscriptionRsp->protocolIEs.list.array[idx]->value.present =\
									 RICsubscriptionRequest_IEs__value_PR_RICrequestID;
	 BuildRicRequestIdret =
	    BuildRicRequestId(&ricSubscriptionRsp->protocolIEs.list.array[idx]->value.choice.RICrequestID);
	 if(BuildRicRequestIdret != ROK)
	 {
	    ret = RFAILED;
	 }
	 else
	 {
	    idx++;
	    ricSubscriptionRsp->protocolIEs.list.array[idx]->id = ProtocolIE_IDE2_id_RANfunctionID;
	    ricSubscriptionRsp->protocolIEs.list.array[idx]->criticality = CriticalityE2_reject;
	    ricSubscriptionRsp->protocolIEs.list.array[idx]->value.present =\
									    RICsubscriptionRequest_IEs__value_PR_RANfunctionID;
	    ricSubscriptionRsp->protocolIEs.list.array[idx]->value.choice.RANfunctionID = 1;

	    idx++;
	    ricSubscriptionRsp->protocolIEs.list.array[idx]->id = ProtocolIE_IDE2_id_RICactions_Admitted;
	    ricSubscriptionRsp->protocolIEs.list.array[idx]->criticality = CriticalityE2_reject;
	    ricSubscriptionRsp->protocolIEs.list.array[idx]->value.present =\
									    RICsubscriptionResponse_IEs__value_PR_RICaction_Admitted_List;
	    BuildRicAdmitListret =
	       BuildRicAdmitList(&ricSubscriptionRsp->protocolIEs.list.array[idx]->value.choice.RICaction_Admitted_List);
	    if(BuildRicAdmitListret != ROK)
	    {
	       ret = RFAILED;
	    }
	 }
      }
   }	
   return ret;
}
/*******************************************************************
 *
 * @brief Builds and Send the RicSubscriptionRsp
 *
 * @details
 *
 *    Function : BuildAndSendRicSubscriptionRsp
 *
 * Functionality:Fills the RicSubscriptionRsp
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t BuildAndSendRicSubscriptionRsp()
{

   E2AP_PDU_t         *e2apRicMsg = NULLP;
   RICsubscriptionResponse_t  *ricSubscriptionRsp=NULLP;
   asn_enc_rval_t     encRetVal; 
   uint8_t ret = RFAILED;
   uint8_t FillRicricSubscriptionRspret;

   while(true)
   {
      DU_LOG("\nINFO   -->  E2AP : Building RIC Subscription Response\n");

      DU_ALLOC(e2apRicMsg, sizeof(E2AP_PDU_t)); 
      if(e2apRicMsg == NULLP)
      {
	 DU_LOG("\nERROR  -->  E2AP : Memory allocation for E2AP-PDU failed");
	 break;
      }
      e2apRicMsg->present =  E2AP_PDU_PR_successfulOutcome;
      DU_ALLOC(e2apRicMsg->choice.successfulOutcome, sizeof(SuccessfulOutcomeE2_t));
      if(e2apRicMsg->choice.successfulOutcome == NULLP)
      {
	 DU_LOG("\nERROR  -->  E2AP : Memory allocation for RIC subscription Response failed");
	 break;
      }

      e2apRicMsg->choice.successfulOutcome->procedureCode = ProcedureCodeE2_id_RICsubscription;
      e2apRicMsg->choice.successfulOutcome->criticality = CriticalityE2_reject;
      e2apRicMsg->choice.successfulOutcome->value.present = \
							    SuccessfulOutcomeE2__value_PR_RICsubscriptionResponse;
      ricSubscriptionRsp = &e2apRicMsg->choice.successfulOutcome->value.choice.RICsubscriptionResponse;

      FillRicricSubscriptionRspret = FillRicSubscriptionRsp(ricSubscriptionRsp);
      if(FillRicricSubscriptionRspret != ROK)
      {
	 DU_LOG("\nERROR  -->  E2AP : Memory allocation for RICsubscriptionResponseIE failed");
	 break;
      }

      /* Prints the Msg formed */
      xer_fprint(stdout, &asn_DEF_E2AP_PDU, e2apRicMsg);

      memset(encBuf, 0, ENC_BUF_MAX_LEN);
      encBufSize = 0;
      encRetVal = aper_encode(&asn_DEF_E2AP_PDU, 0, e2apRicMsg, PrepFinalEncBuf,\
	    encBuf);
      if(encRetVal.encoded == ENCODE_FAIL)
      {
	 DU_LOG("\nERROR  -->  E2AP : Could not encode RIC Subscription Response structure (at %s)\n",\
	       encRetVal.failed_type ? encRetVal.failed_type->name : "unknown");
	 break;
      }
      else
      {
	 DU_LOG("\nDEBUG   -->  E2AP : Created APER encoded buffer for RIC subscription response \n");
#ifdef DEBUG_ASN_PRINT
	 for(int i=0; i< encBufSize; i++)
	 {
	    printf("%x",encBuf[i]);
	 } 
#endif
      } 

      if(SendE2APMsg(DU_APP_MEM_REGION, DU_POOL, encBuf, encBufSize) != ROK)
      {
	 DU_LOG("\nERROR  -->  E2AP : Sending RIC Subscription Response failed");      
	 break;
      }

      ret = ROK;
      break;

   }
   FreeRicSubscriptionRsp(e2apRicMsg);

   return ret;
}

/******************************************************************
 *
 * @brief Deallocation of memory allocated bu aper decoder for e2 setup response
 *
 * @details
 *
 *    Function : freeAperDecodingOfE2SetupRsp
 *
 *    Functionality: Deallocation of memory allocated bu aper decoder for e2
 *    setup response
 *
 * @params[in] E2setupResponse_t *e2SetRspMsg;
 * @return void
 *
 * ****************************************************************/
void freeAperDecodingOfE2SetupRsp(E2setupResponse_t *e2SetRspMsg)
{
   uint8_t arrIdx, e2NodeConfigAddAckListIdx;
   E2nodeComponentConfigAdditionAck_ItemIEs_t *e2NodeAddAckItem;
   E2nodeComponentConfigAdditionAck_List_t *e2NodeConfigAddAckList;

   if(e2SetRspMsg)
   {
      if(e2SetRspMsg->protocolIEs.list.array)
      {
         for(arrIdx=0; arrIdx<e2SetRspMsg->protocolIEs.list.count; arrIdx++)
         {
            if(e2SetRspMsg->protocolIEs.list.array[arrIdx])
            {
               switch(e2SetRspMsg->protocolIEs.list.array[arrIdx]->id)
               {
                  case ProtocolIE_IDE2_id_TransactionID:
                     break;

                  case ProtocolIE_IDE2_id_GlobalRIC_ID:
                     {
                        free(e2SetRspMsg->protocolIEs.list.array[arrIdx]->value.choice.GlobalRIC_ID.pLMN_Identity.buf);
                        free(e2SetRspMsg->protocolIEs.list.array[arrIdx]->value.choice.GlobalRIC_ID.ric_ID.buf);
                        break;
                     }

                  case ProtocolIE_IDE2_id_E2nodeComponentConfigAdditionAck:
                     {
                        e2NodeConfigAddAckList = &e2SetRspMsg->protocolIEs.list.array[arrIdx]->value.choice.E2nodeComponentConfigAdditionAck_List;
                        if(e2NodeConfigAddAckList->list.array )
                        {
                           for(e2NodeConfigAddAckListIdx = 0; e2NodeConfigAddAckListIdx< e2NodeConfigAddAckList->list.count; e2NodeConfigAddAckListIdx++)
                           {
                              if(e2NodeConfigAddAckList->list.array[e2NodeConfigAddAckListIdx])
                              {
                                 e2NodeAddAckItem = (E2nodeComponentConfigAdditionAck_ItemIEs_t*) e2NodeConfigAddAckList->list.array[e2NodeConfigAddAckListIdx];
                                 free(e2NodeAddAckItem->value.choice.E2nodeComponentConfigAdditionAck_Item.e2nodeComponentID.choice.\
                                       e2nodeComponentInterfaceTypeF1->gNB_DU_ID.buf);
                                 free(e2NodeAddAckItem->value.choice.E2nodeComponentConfigAdditionAck_Item.e2nodeComponentID.choice.\
                                       e2nodeComponentInterfaceTypeF1);
                                 free(e2NodeConfigAddAckList->list.array[e2NodeConfigAddAckListIdx]);
                              }
                           }
                           free(e2NodeConfigAddAckList->list.array);
                        }
                        break;
                     }
               }
               free(e2SetRspMsg->protocolIEs.list.array[arrIdx]);  
            }
         }
         free(e2SetRspMsg->protocolIEs.list.array);
      }
   }
}
/******************************************************************
 *
 * @brief Processes E2 Setup Response sent by RIC
 *
 * @details
 *
 *    Function : procE2SetupRsp
 *
 *    Functionality: Processes E2 Setup Response sent by RIC
 *
 * @params[in] E2AP_PDU_t ASN decoded E2AP message
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t procE2SetupRsp(E2AP_PDU_t *e2apMsg)
{
   uint8_t arrIdx =0, transId=0; 
   uint32_t recvBufLen;             
   E2setupResponse_t *e2SetRspMsg;
   CmLList         *node;
   E2NodeComponent *e2NodeComponentInfo;

   DU_LOG("\nINFO   -->  E2AP : E2 Setup Response received"); 
   duCb.e2Status = TRUE; //Set E2 status as true
   e2SetRspMsg = &e2apMsg->choice.successfulOutcome->value.choice.E2setupResponse;

   for(arrIdx=0; arrIdx<e2SetRspMsg->protocolIEs.list.count; arrIdx++)
   {
      switch(e2SetRspMsg->protocolIEs.list.array[arrIdx]->id)
      {
         case ProtocolIE_IDE2_id_TransactionID:
            {
               transId = e2SetRspMsg->protocolIEs.list.array[arrIdx]->value.choice.TransactionID;
               if((duCb.e2apDb.e2TransInfo.onGoingTransaction[transId].transactionId == transId) &&\
                     (duCb.e2apDb.e2TransInfo.onGoingTransaction[transId].procedureCode == e2apMsg->choice.successfulOutcome->procedureCode))
                  memset(&duCb.e2apDb.e2TransInfo.onGoingTransaction[transId], 0, sizeof(E2TransInfo));
               else
               {
                  DU_LOG("\nERROR  -->  E2AP : Invalid transaction id [%d]", transId);
                  return RFAILED;
               }
               break;
            }

         case ProtocolIE_IDE2_id_GlobalRIC_ID:
            {
               /* To store the Ric Id Params */
               recvBufLen = sizeof(e2SetRspMsg->protocolIEs.list.array[arrIdx]->value\
                     .choice.GlobalRIC_ID.pLMN_Identity.size);
                  memcpy(&duCb.e2apDb.ricId.plmnId, e2SetRspMsg->protocolIEs.list.array[arrIdx]\
                        ->value.choice.GlobalRIC_ID.pLMN_Identity.buf, recvBufLen);
               bitStringToInt(&e2SetRspMsg->protocolIEs.list.array[arrIdx]->value.choice.GlobalRIC_ID.ric_ID, &duCb.e2apDb.ricId);
               /*TODO : duCb.e2apDb.ricId.plmnId memory to be deallocated after the usage */
               break;
            }

         case ProtocolIE_IDE2_id_E2nodeComponentConfigAdditionAck:
            break;

         default:
            DU_LOG("\nERROR  -->  E2AP : Invalid IE received in E2SetupRsp:%ld",
                  e2SetRspMsg->protocolIEs.list.array[arrIdx]->id);
            break;
      }
   }
   freeAperDecodingOfE2SetupRsp(e2SetRspMsg);
   
   node = searchE2NodeComponentInfo(F1, E2_NODE_COMPONENT_ADD);
   if(!node)
   {
      DU_LOG("\nERROR  --> E2AP : Received e2NodeComponentInfo is null");
      return RFAILED;
   }
   else
   {
      e2NodeComponentInfo = (E2NodeComponent*)node->node;
      cmLListDelFrm(&duCb.e2apDb.e2NodeComponentList, node);
      DU_FREE(e2NodeComponentInfo->componentRequestPart, e2NodeComponentInfo->reqBufSize);
      DU_FREE(e2NodeComponentInfo->componentResponsePart, e2NodeComponentInfo->rspBufSize);
      DU_FREE(e2NodeComponentInfo, sizeof(E2NodeComponent));
      DU_FREE(node, sizeof(CmLList));
   }

   BuildAndSendE2NodeConfigUpdate();
   return ROK;
}

/******************************************************************
 *
 * @brief Processes RIC Subscription Req sent by RIC
 *
 * @details
 *
 *    Function : procRicSubsReq
 *
 *    Functionality: Processes E2 Setup Response sent by CU
 *
 * @params[in] E2AP_PDU_t ASN decoded E2AP message
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t procRicSubsReq(E2AP_PDU_t *e2apMsg)
{
   uint8_t idx; 
   uint8_t ied; 
   uint8_t ret = ROK;
   CmLList  *ricSubscriptionNode = NULLP;
   RICsubscriptionRequest_t *ricSubsReq;
   RicSubscription *ricSubscriptionInfo;
   RICaction_ToBeSetup_ItemIEs_t *actionItem;

   DU_LOG("\nINFO   -->  E2AP : RIC Subscription request received"); 
   ricSubsReq = &e2apMsg->choice.initiatingMessage->value.choice.RICsubscriptionRequest;

   for(idx=0; idx<ricSubsReq->protocolIEs.list.count; idx++)
   {
      if(ricSubsReq->protocolIEs.list.array[idx])
      {
         switch(ricSubsReq->protocolIEs.list.array[idx]->id)
         {
            case ProtocolIE_IDE2_id_RICrequestID:
               {
                  /* TODO :- ricSubscriptionInfo details will be stored based on
                   * RAN function id, so first we need to search RAN function and then add
                   * subscription details to that ran function */
                  DU_ALLOC(ricSubscriptionInfo, sizeof(RicSubscription));
                  if(!ricSubscriptionInfo)
                  {
                     DU_LOG("\nERROR  -->  E2AP : Memory allocation failed for ricSubscriptionInfo");
                     return RFAILED;
                  }
                  ricSubscriptionInfo->requestId.requestorId = ricSubsReq->protocolIEs.list.array[idx]->value.choice.RICrequestID.ricRequestorID;
                  ricSubscriptionInfo->requestId.instanceId = ricSubsReq->protocolIEs.list.array[idx]->value.choice.RICrequestID.ricInstanceID;
                  DU_ALLOC(ricSubscriptionNode, sizeof(CmLList));
                  if(ricSubscriptionNode)
                  {
                     ricSubscriptionNode->node = (PTR) ricSubscriptionInfo;
                     cmLListAdd2Tail(&duCb.e2apDb.ranFunction[0].subscriptionList,ricSubscriptionNode);
                  }
                  break;
               }
            case ProtocolIE_IDE2_id_RANfunctionID:
               {
                  duCb.e2apDb.ranFunction[0].id = ricSubsReq->protocolIEs.list.array[idx]-> \
                                          value.choice.RANfunctionID; 
                  break;
               }
            case ProtocolIE_IDE2_id_RICsubscriptionDetails:
               {
                  if(ricSubsReq->protocolIEs.list.array[idx]->value.choice.RICsubscriptionDetails.ricAction_ToBeSetup_List.\
                        list.array)
                  {
                     actionItem =(RICaction_ToBeSetup_ItemIEs_t *)ricSubsReq->protocolIEs.list\
                                 .array[idx]->value.choice.RICsubscriptionDetails.ricAction_ToBeSetup_List\
                                 .list.array[0];

                     for(ied = 0; ied < ricSubsReq->protocolIEs.list.array[idx]->value.choice.\
                           RICsubscriptionDetails.ricAction_ToBeSetup_List.list.count; ied++)
                     {
                        switch(actionItem->id)
                        {
                           case ProtocolIE_IDE2_id_RICaction_ToBeSetup_Item:
                              {
                                 ricSubscriptionInfo->actionSequence[0].id  = actionItem->value.choice.RICaction_ToBeSetup_Item.ricActionID;
                                 ricSubscriptionInfo->actionSequence[0].type = actionItem->value.choice.RICaction_ToBeSetup_Item.ricActionType;
                                 break;
                              }
                           default:
                              DU_LOG("\nERROR  -->  E2AP : Invalid IE received in RicSetupLst:%ld",actionItem->id);
                              break;
                        }
                        free(actionItem);
                     }
                     free(ricSubsReq->protocolIEs.list.array[idx]->value.choice.RICsubscriptionDetails.ricAction_ToBeSetup_List.\
                           list.array);
                  }
                  break;
               }

            default:
               DU_LOG("\nERROR  -->  E2AP : Invalid IE received in RIC SubsReq:%ld",
                     ricSubsReq->protocolIEs.list.array[idx]->id);
               break;
         }
         free(ricSubsReq->protocolIEs.list.array[idx]);
      }
   }
   free(ricSubsReq->protocolIEs.list.array);
   ret = BuildAndSendRicSubscriptionRsp();
   {
      BuildAndSendRicIndication(ricSubscriptionInfo);
   }

   return ret;
}

/*******************************************************************
 *
 * @brief Free the RicIndication Message
 *
 * @details
 *
 *    Function : FreeRicIndication
 *
 * Functionality: Free the RicIndication Message
 *
 * @return void
 *         
 *
 ******************************************************************/
void FreeRicIndication(E2AP_PDU_t  *e2apMsg) 
{
   uint8_t idx=0;
   RICindication_t *ricIndicationMsg= NULLP;


   if(e2apMsg != NULLP)
   {
      if(e2apMsg->choice.initiatingMessage != NULLP)
      {
	 ricIndicationMsg = &e2apMsg->choice.initiatingMessage->value.choice.RICindication;
	 if(ricIndicationMsg!= NULLP)
	 {
	    if(ricIndicationMsg->protocolIEs.list.array != NULLP)
	    {
	       for(idx=0; idx<ricIndicationMsg->protocolIEs.list.count; idx++)
	       {
		  if(ricIndicationMsg->protocolIEs.list.array[idx] != NULLP)
		  {
		     switch(ricIndicationMsg->protocolIEs.list.array[idx]->id)
		     {
			case ProtocolIE_IDE2_id_RICrequestID:
			   break;

			case ProtocolIE_IDE2_id_RANfunctionID:
			   break;

			case ProtocolIE_IDE2_id_RICactionID:
			   break;

			case ProtocolIE_IDE2_id_RICindicationType:
			   break;

			case ProtocolIE_IDE2_id_RICindicationHeader:
			   {
			      DU_FREE(ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationHeader.buf,\
				    ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationHeader.size);
			      break;
			   }
			case ProtocolIE_IDE2_id_RICindicationMessage:
			   {
			      DU_FREE(ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationMessage.buf,\
				    ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationMessage.size);
			      break;
			   }
			default:
			   break;
		     }
		     DU_FREE(ricIndicationMsg->protocolIEs.list.array[idx],sizeof(RICindication_IEs_t));
		  }
	       }
	       DU_FREE(ricIndicationMsg->protocolIEs.list.array,ricIndicationMsg->protocolIEs.list.size);
	    }
	 }
	 DU_FREE(e2apMsg->choice.initiatingMessage, sizeof(InitiatingMessageE2_t));
      }
      DU_FREE(e2apMsg, sizeof(E2AP_PDU_t));
   }
}
/*******************************************************************
 *
 * brief Fill the RicIndication Message
 *
 * @details
 *
 *    Function : FillRicIndication
 *
 * Functionality:Fills the RicIndication Message
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/
uint8_t FillRicIndication(RICindication_t *ricIndicationMsg, RicSubscription *ricSubscriptionInfo)
{
   uint8_t elementCnt=0;
   uint8_t idx=0;
   uint8_t ret = ROK;
   elementCnt = 6;

   ricIndicationMsg->protocolIEs.list.count = elementCnt;
   ricIndicationMsg->protocolIEs.list.size  = elementCnt * sizeof(RICindication_t);
   /* Initialize the Ric Indication members */
   DU_ALLOC(ricIndicationMsg->protocolIEs.list.array, \
	 ricIndicationMsg->protocolIEs.list.size);
   if(ricIndicationMsg->protocolIEs.list.array == NULLP)
   {
      DU_LOG("\nERROR  -->  E2AP : Memory allocation for RICindicationIEs failed");
      ret = RFAILED;
   }
   else
   {
      for(idx=0; idx<elementCnt; idx++)
      {
	 DU_ALLOC(ricIndicationMsg->protocolIEs.list.array[idx],\
	       sizeof(RICindication_IEs_t));
	 if(ricIndicationMsg->protocolIEs.list.array[idx] == NULLP)
	 {
	    DU_LOG("\nERROR  -->  E2AP : Memory allocation for RICindicationIEs failed");
	    ret = RFAILED;
	 }
      }
      if(ret != RFAILED)
      {
	 idx = 0;

	 ricIndicationMsg->protocolIEs.list.array[idx]->id = ProtocolIE_IDE2_id_RICrequestID;
	 ricIndicationMsg->protocolIEs.list.array[idx]->criticality = CriticalityE2_reject;
	 ricIndicationMsg->protocolIEs.list.array[idx]->value.present = \
									RICindication_IEs__value_PR_RICrequestID;
	 ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICrequestID.ricRequestorID =ricSubscriptionInfo->requestId.requestorId;
	 ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICrequestID.ricInstanceID = ricSubscriptionInfo->requestId.instanceId;

	 idx++;
	 ricIndicationMsg->protocolIEs.list.array[idx]->id = ProtocolIE_IDE2_id_RANfunctionID;
	 ricIndicationMsg->protocolIEs.list.array[idx]->criticality = CriticalityE2_reject;
	 ricIndicationMsg->protocolIEs.list.array[idx]->value.present = \
									RICindication_IEs__value_PR_RANfunctionID;
	 ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RANfunctionID = duCb.e2apDb.ranFunction[0].id;

	 idx++;
	 ricIndicationMsg->protocolIEs.list.array[idx]->id = ProtocolIE_IDE2_id_RICactionID;
	 ricIndicationMsg->protocolIEs.list.array[idx]->criticality = CriticalityE2_reject;
	 ricIndicationMsg->protocolIEs.list.array[idx]->value.present = \
									RICindication_IEs__value_PR_RICactionID;
	 ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICactionID = ricSubscriptionInfo->actionSequence[0].id;

	 idx++;
	 ricIndicationMsg->protocolIEs.list.array[idx]->id = ProtocolIE_IDE2_id_RICindicationType;
	 ricIndicationMsg->protocolIEs.list.array[idx]->criticality = CriticalityE2_reject;
	 ricIndicationMsg->protocolIEs.list.array[idx]->value.present = \
									RICindication_IEs__value_PR_RICindicationType;
	 ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationType = ricSubscriptionInfo->actionSequence[0].type;

	 idx++;
	 ricIndicationMsg->protocolIEs.list.array[idx]->id = ProtocolIE_IDE2_id_RICindicationHeader;
	 ricIndicationMsg->protocolIEs.list.array[idx]->criticality = CriticalityE2_reject;
	 ricIndicationMsg->protocolIEs.list.array[idx]->value.present = \
									RICindication_IEs__value_PR_RICindicationHeader;
	 ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationHeader.size = 3 *
	    sizeof(uint8_t);
	 DU_ALLOC(ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationHeader.buf ,\
	       ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationHeader.size);
	 if(ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationHeader.buf == NULLP)
	 {
	    DU_LOG("\nERROR  -->  E2AP : Memory allocation for RICindicationIEs failed");
	    ret = RFAILED;
	 }
	 else
	 {
	    buildPlmnId(duCfgParam.srvdCellLst[0].duCellInfo.cellInfo.nrCgi.plmn, \
		  ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationHeader.buf);
	    idx++;
	    /* TO BE CHANGED: RIC INDICATION DATA */
	    /* For now filling a dummy octect data, need to tested with PRBs*/
	    ricIndicationMsg->protocolIEs.list.array[idx]->id = ProtocolIE_IDE2_id_RICindicationMessage;
	    ricIndicationMsg->protocolIEs.list.array[idx]->criticality = CriticalityE2_reject;
	    ricIndicationMsg->protocolIEs.list.array[idx]->value.present = \
									   RICindication_IEs__value_PR_RICindicationMessage;
	    ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationMessage.size = 3 *
	       sizeof(uint8_t);
	    DU_ALLOC(ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationMessage.buf ,\
		  ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationMessage.size);
	    if(ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationMessage.buf == NULLP)
	    {
	       DU_LOG("\nERROR  -->  E2AP : Memory allocation for RICindicationIEs failed");
	       ret = RFAILED;
	    }
	    else
	    {
	       buildPlmnId(duCfgParam.srvdCellLst[0].duCellInfo.cellInfo.nrCgi.plmn, \
		     ricIndicationMsg->protocolIEs.list.array[idx]->value.choice.RICindicationMessage.buf);
	    }
	 }
      }
   }
   return ret;
}

/*******************************************************************
 *
 * @brief Builds and Send the RicIndication Message
 *
 * @details
 *
 *    Function : BuildAndSendRicIndication
 *
 * Functionality:Fills the RicIndication Message
 *
 * @return ROK     - success
 *         RFAILED - failure
 *
 ******************************************************************/

uint8_t BuildAndSendRicIndication(RicSubscription *ricSubscriptionInfo)
{
   E2AP_PDU_t                 *e2apMsg = NULLP;
   RICindication_t            *ricIndicationMsg=NULLP;
   asn_enc_rval_t             encRetVal;        /* Encoder return value */
   uint8_t ret = RFAILED; 
   uint8_t FillRicIndicationret = ROK;

   while(true)
   {
      DU_LOG("\nINFO   -->  E2AP : Building RIC Indication Message\n");

      DU_ALLOC(e2apMsg, sizeof(E2AP_PDU_t));
      if(e2apMsg == NULLP)
      {
	 DU_LOG("\nERROR  -->  E2AP : Memory allocation for E2AP-PDU failed");
	 break;
      }

      e2apMsg->present = E2AP_PDU_PR_initiatingMessage;
      DU_ALLOC(e2apMsg->choice.initiatingMessage, sizeof(InitiatingMessageE2_t));
      if(e2apMsg->choice.initiatingMessage == NULLP)
      {
	 DU_LOG("\nERROR  -->  E2AP : Memory allocation for E2AP-PDU failed");
	 break;
      }
      e2apMsg->choice.initiatingMessage->procedureCode = ProcedureCodeE2_id_RICindication;
      e2apMsg->choice.initiatingMessage->criticality = CriticalityE2_reject;
      e2apMsg->choice.initiatingMessage->value.present = InitiatingMessageE2__value_PR_RICindication;

      ricIndicationMsg = &e2apMsg->choice.initiatingMessage->value.choice.RICindication;

      FillRicIndicationret = FillRicIndication(ricIndicationMsg, ricSubscriptionInfo);
      if(FillRicIndicationret != ROK)
      {
	 break;
      }
      /* Prints the Msg formed */
      xer_fprint(stdout, &asn_DEF_E2AP_PDU, e2apMsg);
      memset(encBuf, 0, ENC_BUF_MAX_LEN);
      encBufSize = 0;
      encRetVal = aper_encode(&asn_DEF_E2AP_PDU, 0, e2apMsg, PrepFinalEncBuf,\
	    encBuf);
      if(encRetVal.encoded == ENCODE_FAIL)
      {
	 DU_LOG("\nERROR  -->  E2AP : Could not encode RIC Indication Message (at %s)\n",\
	       encRetVal.failed_type ? encRetVal.failed_type->name : "unknown");
	 break;
      }
      else
      {
	 DU_LOG("\nDEBUG  -->  E2AP : Created APER encoded buffer for RIC Indication Message \n");
#ifdef DEBUG_ASN_PRINT
	 for(int i=0; i< encBufSize; i++)
	 {
	    printf("%x",encBuf[i]);
	 } 
#endif
      }

      if(SendE2APMsg(DU_APP_MEM_REGION, DU_POOL, encBuf, encBufSize) != ROK)
      {
	 DU_LOG("\nINFO   -->  E2AP : Sending RIC Indication Message");      

      }
      ret = ROK;
      break;
   }
   FreeRicIndication(e2apMsg);	
   return ret;
}

/*******************************************************************
 *
 * @brief Deallocate the memory allocated for E2nodeConfigurationUpdate msg 
 *
 * @details
 *
 *    Function : FreeE2NodeConfigUpdate 
 *
 *    Functionality:
 *       - freeing the memory allocated for E2nodeConfigurationUpdate
 *
 * @params[in] E2AP_PDU_t *e2apMsg 
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
void FreeE2NodeConfigUpdate(E2AP_PDU_t *e2apMsg)
{
   uint8_t arrIdx =0;
   E2nodeConfigurationUpdate_t *e2NodeConfigUpdate;

   if(e2apMsg != NULLP)
   {
      if(e2apMsg->choice.initiatingMessage != NULLP)
      {
         e2NodeConfigUpdate = &e2apMsg->choice.initiatingMessage->value.choice.E2nodeConfigurationUpdate;
         if(e2NodeConfigUpdate->protocolIEs.list.array != NULLP)
         {
            for(arrIdx = 0; arrIdx < e2NodeConfigUpdate->protocolIEs.list.count; arrIdx++)
            {
               DU_FREE(e2NodeConfigUpdate->protocolIEs.list.array[arrIdx], sizeof(E2nodeConfigurationUpdate_IEs_t));
            }
            DU_FREE(e2NodeConfigUpdate->protocolIEs.list.array, e2NodeConfigUpdate->protocolIEs.list.size);
         }
         DU_FREE(e2apMsg->choice.initiatingMessage, sizeof(InitiatingMessageE2_t));
      }
      DU_FREE(e2apMsg, sizeof(E2AP_PDU_t));
   }
}

/*******************************************************************
 *
 * @brief Buld and send the E2 node config update msg 
 *
 * @details
 *
 *    Function : BuildAndSendE2NodeConfigUpdate
 *
 *    Functionality:
 *         - Buld and send the E2 node config update msg
 *
 * @params[in] 
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/

uint8_t BuildAndSendE2NodeConfigUpdate()
{
   uint8_t arrIdx = 0,elementCnt = 1;
   uint8_t ret = ROK;
   E2AP_PDU_t        *e2apMsg = NULLP;
   E2nodeConfigurationUpdate_t *e2NodeConfigUpdate = NULLP;
   asn_enc_rval_t     encRetVal;       /* Encoder return value */

   DU_LOG("\nINFO   -->  E2AP : Building E2 Node config update\n");
   do
   {
      DU_ALLOC(e2apMsg, sizeof(E2AP_PDU_t));
      if(e2apMsg == NULLP)
      {
         DU_LOG("\nERROR  -->  E2AP : Memory allocation for E2AP-PDU failed");
         break;
      }
      e2apMsg->present = E2AP_PDU_PR_initiatingMessage;
      DU_ALLOC(e2apMsg->choice.initiatingMessage, sizeof(InitiatingMessageE2_t));
      if(e2apMsg->choice.initiatingMessage == NULLP)
      {
         DU_LOG("\nERROR  -->  E2AP : Memory allocation for E2AP-PDU failed");
         DU_FREE(e2apMsg, sizeof(E2AP_PDU_t));
         return RFAILED;
      }
      e2apMsg->choice.initiatingMessage->criticality = CriticalityE2_reject;
      e2apMsg->choice.initiatingMessage->procedureCode = ProcedureCodeE2_id_E2nodeConfigurationUpdate;
      e2apMsg->choice.initiatingMessage->value.present = \
      InitiatingMessageE2__value_PR_E2nodeConfigurationUpdate;
      e2NodeConfigUpdate = &e2apMsg->choice.initiatingMessage->value.choice.E2nodeConfigurationUpdate;

      e2NodeConfigUpdate->protocolIEs.list.count = elementCnt;
      e2NodeConfigUpdate->protocolIEs.list.size  = elementCnt * sizeof(E2nodeConfigurationUpdate_IEs_t*);
      /* Initialize the Ric Indication members */
      DU_ALLOC(e2NodeConfigUpdate->protocolIEs.list.array, \
            e2NodeConfigUpdate->protocolIEs.list.size);
      if(e2NodeConfigUpdate->protocolIEs.list.array == NULLP)
      {
         DU_LOG("\nERROR  -->  E2AP : Memory allocation for e2NodeConfigUpdate failed");
         break;
      }
      
      for(arrIdx =0; arrIdx<elementCnt; arrIdx++)
      {
         DU_ALLOC(e2NodeConfigUpdate->protocolIEs.list.array[arrIdx], sizeof(E2nodeConfigurationUpdate_IEs_t));
         if(e2NodeConfigUpdate->protocolIEs.list.array[arrIdx] == NULLP)
         {
            
            DU_LOG("\nERROR  -->  E2AP : Memory allocation for e2NodeConfigUpdate failed");
            break;
         }
      }

      arrIdx = 0;
      /* TransactionID */
      e2NodeConfigUpdate->protocolIEs.list.array[arrIdx]->id = ProtocolIE_IDE2_id_TransactionID;
      e2NodeConfigUpdate->protocolIEs.list.array[arrIdx]->criticality = CriticalityE2_reject;
      e2NodeConfigUpdate->protocolIEs.list.array[arrIdx]->value.present = E2nodeConfigurationUpdate_IEs__value_PR_TransactionID;
      e2NodeConfigUpdate->protocolIEs.list.array[arrIdx]->value.choice.TransactionID = TRANS_ID;


      /* Prints the Msg formed */
      xer_fprint(stdout, &asn_DEF_E2AP_PDU, e2apMsg);

      memset(encBuf, 0, ENC_BUF_MAX_LEN);
      encBufSize = 0;
      encRetVal = aper_encode(&asn_DEF_E2AP_PDU, 0, e2apMsg, PrepFinalEncBuf,\
            encBuf);
      if(encRetVal.encoded == ENCODE_FAIL)
      {
         DU_LOG("\nERROR  -->  E2AP : Could not encode E2nodeConfigurationUpdate structure (at %s)\n",\
               encRetVal.failed_type ? encRetVal.failed_type->name : "unknown");
         break;
      }
      else
      {
         DU_LOG("\nDEBUG   -->  E2AP : Created APER encoded buffer for E2nodeConfigurationUpdate\n");
#ifdef DEBUG_ASN_PRINT
         for(int i=0; i< encBufSize; i++)
         {
            printf("%x",encBuf[i]);
         }
#endif
      }
      if(SendE2APMsg(DU_APP_MEM_REGION, DU_POOL, encBuf, encBufSize))
      {
         DU_LOG("\nERROR  -->  E2AP : Sending E2 node config update failed");
         return RFAILED;
      }

      break;
   }while(true);
   
   FreeE2NodeConfigUpdate(e2apMsg);
   return ret;
}

/*******************************************************************
 *
 * @brief Deallocate the memory allocated for E2ResetRequest msg
 *
 * @details
 *
 *    Function : FreeE2ResetRequest
 *
 *    Functionality:
 *       - freeing the memory allocated for E2ResetRequest
 *
 * @params[in] E2AP_PDU_t *e2apMsg
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
void FreeE2ResetRequest(E2AP_PDU_t *e2apMsg)
{
   uint8_t ieIdx =0;
   ResetRequestE2_t  *resetReq = NULLP;

   if(e2apMsg != NULLP)
   {
      if(e2apMsg->choice.initiatingMessage != NULLP)
      {
         resetReq = &e2apMsg->choice.initiatingMessage->value.choice.ResetRequestE2;
         if(resetReq->protocolIEs.list.array)
         {
            for(ieIdx = 0; ieIdx < resetReq->protocolIEs.list.count; ieIdx++)
            {
               DU_FREE(resetReq->protocolIEs.list.array[ieIdx], sizeof(ResetRequestIEs_t));
            }
            DU_FREE(resetReq->protocolIEs.list.array, resetReq->protocolIEs.list.size);
         }
         DU_FREE(e2apMsg->choice.initiatingMessage, sizeof(InitiatingMessageE2_t));
      }
      DU_FREE(e2apMsg, sizeof(E2AP_PDU_t));
   }
}

/*******************************************************************
 *
 * @brief Build and send the E2 reset request msg
 *
 * @details
 *
 *    Function : BuildAndSendE2ResetRequest
 *
 *    Functionality:
 *         - Buld and send the E2 reset request msg to RIC
 *
 * @params[in]
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t BuildAndSendE2ResetRequest(E2CauseType failureType, E2Cause failureCause)
{
   uint8_t ieIdx = 0, elementCnt = 0, transId = 0;
   uint8_t ret = RFAILED;
   E2AP_PDU_t        *e2apMsg = NULLP;
   ResetRequestE2_t  *resetReq = NULLP;
   asn_enc_rval_t     encRetVal;       /* Encoder return value */

   DU_LOG("\nINFO   -->  E2AP : Building E2 Reset Request\n");

   do
   {
      DU_ALLOC(e2apMsg, sizeof(E2AP_PDU_t));
      if(e2apMsg == NULLP)
      {
         DU_LOG("\nERROR  -->  E2AP : BuildAndSendE2ResetRequest(): Memory allocation for E2AP-PDU failed");
         break;
      }

      e2apMsg->present = E2AP_PDU_PR_initiatingMessage;
      DU_ALLOC(e2apMsg->choice.initiatingMessage, sizeof(InitiatingMessageE2_t));
      if(e2apMsg->choice.initiatingMessage == NULLP)
      {
         DU_LOG("\nERROR  -->  E2AP : BuildAndSendE2ResetRequest(): Memory allocation for initiatingMessage");
         break;
      }

      e2apMsg->choice.initiatingMessage->procedureCode = ProcedureCodeE2_id_Reset;
      e2apMsg->choice.initiatingMessage->criticality = CriticalityE2_reject;
      e2apMsg->choice.initiatingMessage->value.present = InitiatingMessageE2__value_PR_ResetRequestE2;
      resetReq = &e2apMsg->choice.initiatingMessage->value.choice.ResetRequestE2;

      elementCnt = 2;
      resetReq->protocolIEs.list.count = elementCnt;
      resetReq->protocolIEs.list.size = elementCnt * sizeof(ResetRequestIEs_t *);

      DU_ALLOC(resetReq->protocolIEs.list.array, resetReq->protocolIEs.list.size);
      if(!resetReq->protocolIEs.list.array)
      {
         DU_LOG("\nERROR  -->  E2AP : BuildAndSendE2ResetRequest(): Memory allocation failed for \
            Reset Request IE array");
         break;
      }

      for(ieIdx = 0; ieIdx < elementCnt; ieIdx++)
      {
         DU_ALLOC(resetReq->protocolIEs.list.array[ieIdx], sizeof(ResetRequestIEs_t));
         if(!resetReq->protocolIEs.list.array[ieIdx])
         {
            DU_LOG("\nERROR  -->  E2AP : BuildAndSendE2ResetRequest(): Memory allocation failed for \
            Reset Request IE array element");
            break;
         }
      }

      /* In case of failure */
      if(ieIdx < elementCnt)
         break;

      ieIdx = 0;
      resetReq->protocolIEs.list.array[ieIdx]->id = ProtocolIE_IDE2_id_TransactionID;
      resetReq->protocolIEs.list.array[ieIdx]->criticality = CriticalityE2_reject;
      resetReq->protocolIEs.list.array[ieIdx]->value.present = ResetRequestIEs__value_PR_TransactionID;
      transId = assignTransactionId();
      resetReq->protocolIEs.list.array[ieIdx]->value.choice.TransactionID = transId;

      ieIdx++;
      resetReq->protocolIEs.list.array[ieIdx]->id = ProtocolIE_IDE2_id_CauseE2;
      resetReq->protocolIEs.list.array[ieIdx]->criticality = CriticalityE2_ignore;
      resetReq->protocolIEs.list.array[ieIdx]->value.present = ResetRequestIEs__value_PR_CauseE2;
      resetReq->protocolIEs.list.array[ieIdx]->value.choice.CauseE2.present = failureType;
      switch(resetReq->protocolIEs.list.array[ieIdx]->value.choice.CauseE2.present)
      {
         case CauseE2_PR_NOTHING:
            break;
         case CauseE2_PR_ricRequest:
            resetReq->protocolIEs.list.array[ieIdx]->value.choice.CauseE2.choice.ricRequest = failureCause;
            break;
         case CauseE2_PR_ricService:
            resetReq->protocolIEs.list.array[ieIdx]->value.choice.CauseE2.choice.ricService = failureCause;
            break;
         case CauseE2_PR_e2Node:
            resetReq->protocolIEs.list.array[ieIdx]->value.choice.CauseE2.choice.e2Node = failureCause;
            break;
         case CauseE2_PR_transport:
            resetReq->protocolIEs.list.array[ieIdx]->value.choice.CauseE2.choice.transport = failureCause;
            break;
         case CauseE2_PR_protocol:
            resetReq->protocolIEs.list.array[ieIdx]->value.choice.CauseE2.choice.protocol = failureCause;
            break;
         case CauseE2_PR_misc:
            resetReq->protocolIEs.list.array[ieIdx]->value.choice.CauseE2.choice.misc = failureCause;
            break;
      }

      /* Prints the Msg formed */
      xer_fprint(stdout, &asn_DEF_E2AP_PDU, e2apMsg);

      memset(encBuf, 0, ENC_BUF_MAX_LEN);
      encBufSize = 0;
      encRetVal = aper_encode(&asn_DEF_E2AP_PDU, 0, e2apMsg, PrepFinalEncBuf,\
            encBuf);
      if(encRetVal.encoded == ENCODE_FAIL)
      {
         DU_LOG("\nERROR  -->  E2AP : Could not encode E2SetupRequest structure (at %s)\n",\
               encRetVal.failed_type ? encRetVal.failed_type->name : "unknown");
         break;
      }
      else
      {
         DU_LOG("\nDEBUG   -->  E2AP : Created APER encoded buffer for E2SetupRequest\n");
#ifdef DEBUG_ASN_PRINT
         for(int i=0; i< encBufSize; i++)
         {
            printf("%x",encBuf[i]);
         }
#endif
      }
      if(SendE2APMsg(DU_APP_MEM_REGION, DU_POOL, encBuf, encBufSize) != ROK)
      {
         DU_LOG("\nERROR  -->  E2AP : Sending E2 Setup request failed");
         break;
      }

      /* In case the message is sent successfully, store the transaction info to
       * be used when response is received */
      duCb.e2apDb.e2TransInfo.onGoingTransaction[transId].transactionId = transId;
      duCb.e2apDb.e2TransInfo.onGoingTransaction[transId].procedureCode = e2apMsg->choice.initiatingMessage->procedureCode;

      ret = ROK;
      break;
   }while(true);

   /* Free all memory */
   FreeE2ResetRequest(e2apMsg);
   return ret;
}

/*******************************************************************
 *
 * @brief Deallocate the memory allocated for Reset Response msg
 *
 * @details
 *
 *    Function : freeAperDecodingOfE2ResetRsp
 *
 *    Functionality:
 *       - freeing the memory allocated for Reset response
 *
 * @params[in] ResetResponseE2_t *resetResponse
 * @return void
 *
 * ****************************************************************/
void freeAperDecodingOfE2ResetRsp(ResetResponseE2_t *resetResponse)
{
   uint8_t ieIdx;

   if(resetResponse)
   {
      if(resetResponse->protocolIEs.list.array)
      {
         for(ieIdx=0; ieIdx < resetResponse->protocolIEs.list.count; ieIdx++)
         {
            if(resetResponse->protocolIEs.list.array[ieIdx])
            {
               switch(resetResponse->protocolIEs.list.array[ieIdx]->id)
               {
                  case ProtocolIE_IDE2_id_TransactionID:
                     break;

                  case ProtocolIE_IDE2_id_CriticalityDiagnosticsE2:
                     break;
               }
               free(resetResponse->protocolIEs.list.array[ieIdx]);
            }
         }
         free(resetResponse->protocolIEs.list.array);
      }
   }
}

/******************************************************************
 *
 * @brief Processes E2 Reset Response sent by RIC
 *
 * @details
 *
 *    Function : procResetResponse
 *
 *    Functionality: Processes E2 Reset Response sent by RIC
 *
 * @params[in] E2AP_PDU_t ASN decoded E2AP message
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
uint8_t procResetResponse(E2AP_PDU_t *e2apMsg)
{
   uint8_t ieIdx =0, transId;
   ResetResponseE2_t *resetResponse;

   DU_LOG("\nINFO   -->  E2AP : E2 Reset Response received");
   resetResponse = &e2apMsg->choice.successfulOutcome->value.choice.ResetResponseE2;;

   for(ieIdx=0; ieIdx < resetResponse->protocolIEs.list.count; ieIdx++)
   {
      switch(resetResponse->protocolIEs.list.array[ieIdx]->id)
      {
         case ProtocolIE_IDE2_id_TransactionID:
            transId = resetResponse->protocolIEs.list.array[ieIdx]->value.choice.TransactionID;
            if((duCb.e2apDb.e2TransInfo.onGoingTransaction[transId].transactionId == transId) && \
                  (duCb.e2apDb.e2TransInfo.onGoingTransaction[transId].procedureCode == e2apMsg->choice.successfulOutcome->procedureCode))
              memset(&duCb.e2apDb.e2TransInfo.onGoingTransaction[transId], 0, sizeof(E2TransInfo));
            else
            {
               DU_LOG("\nERROR  -->  E2AP : Invalid transaction id [%d]", transId);
               return RFAILED;
            }
            break;
         case ProtocolIE_IDE2_id_CriticalityDiagnosticsE2:
            /* As per ORAN WG3 E2AP spec v3.0, section 9.2.2
               Criticality Diagnostics IE is sent by Near-RT RIC when parts of a received message i.e. 
               Reset Request in this case, have not been comprehended or were missing, or if the message 
               contained logical errors.

               Processing of this ID should be implemented when negative call flows are to be supported.
             */
            break;
         default:
            DU_LOG("\nERROR  -->  E2AP : Invalid IE received in E2 Reset Response : %ld",
                  resetResponse->protocolIEs.list.array[ieIdx]->id);
            break;
      }
   }

   freeAperDecodingOfE2ResetRsp(resetResponse);
   return ROK;
}

/******************************************************************
 *
 * @brief Deallocation of memory allocated bu aper decoder for e2 setup Failure
 *
 * @details
 *
 *    Function : freeAperDecodingOfE2SetupFailure
 *
 *    Functionality: Deallocation of memory allocated bu aper decoder for e2
 *    setup Failure
 *
 * @params[in] E2setupFailure_t *e2SetupFailure;
 * @return void
 *
 * ****************************************************************/
void freeAperDecodingOfE2SetupFailure(E2setupFailure_t *e2SetupFailure)
{
   uint8_t arrIdx;

   if(e2SetupFailure)
   {
      if(e2SetupFailure->protocolIEs.list.array)
      {
         for(arrIdx=0; arrIdx<e2SetupFailure->protocolIEs.list.count; arrIdx++)
         {
            if(e2SetupFailure->protocolIEs.list.array[arrIdx])
            {
               free(e2SetupFailure->protocolIEs.list.array[arrIdx]);  
            }
         }
         free(e2SetupFailure->protocolIEs.list.array);
      }
   }
}
/******************************************************************
 *
 * @brief Processes E2 Setup Failure sent by RIC
 *
 * @details
 *
 *    Function : procE2SetupFailure
 *
 *    Functionality: Processes E2 Setup failure sent by RIC
 *
 * @params[in] E2AP_PDU_t ASN decoded E2AP message
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
void procE2SetupFailure(E2AP_PDU_t *e2apMsg)
{
   uint8_t arrIdx =0, transId =0, timerValue=0; 
   E2setupFailure_t *e2SetupFailure;

   DU_LOG("\nINFO   -->  E2AP : E2 Setup failure received"); 
   e2SetupFailure = &e2apMsg->choice.unsuccessfulOutcome->value.choice.E2setupFailure;

   for(arrIdx=0; arrIdx<e2SetupFailure->protocolIEs.list.count; arrIdx++)
   {
      switch(e2SetupFailure->protocolIEs.list.array[arrIdx]->id)
      {
         case ProtocolIE_IDE2_id_TransactionID:
         {
            transId = e2SetupFailure->protocolIEs.list.array[arrIdx]->value.choice.TransactionID;
            if((duCb.e2apDb.e2TransInfo.onGoingTransaction[transId].transactionId == transId) &&\
            (duCb.e2apDb.e2TransInfo.onGoingTransaction[transId].procedureCode == e2apMsg->choice.unsuccessfulOutcome->procedureCode))
              memset(&duCb.e2apDb.e2TransInfo.onGoingTransaction[transId], 0, sizeof(E2TransInfo));
            else
            {
               DU_LOG("\nERROR  -->  E2AP : Invalid transaction id [%d]", transId);
               return ;
            }
            break;
         }
         case ProtocolIE_IDE2_id_TimeToWaitE2:
            {
               timerValue = covertE2WaitTimerEnumToValue(e2SetupFailure->protocolIEs.list.array[arrIdx]->value.choice.TimeToWaitE2);
               if((duChkTmr((PTR)&(duCb.e2apDb), EVENT_E2_SETUP_TMR)) == FALSE)
               {
                  duStartTmr((PTR)&(duCb.e2apDb), EVENT_E2_SETUP_TMR, timerValue);
               }
               else
               {
                  DU_LOG("\nERROR   -->  E2AP : EVENT_E2_SETUP_TMR timer is already running");
                  return;
               }
               break; 
            }
      }
   }

   freeAperDecodingOfE2SetupFailure(e2SetupFailure);
}
/*******************************************************************
 *
 * @brief Handles received E2AP message and sends back response  
 *
 * @details
 *
 *    Function : E2APMsgHdlr
 *
 *    Functionality:
 *         - Decodes received E2AP control message
 *         - Prepares response message, encodes and sends to SCTP
 *
 * @params[in] 
 * @return ROK     - success
 *         RFAILED - failure
 *
 * ****************************************************************/
void E2APMsgHdlr(Buffer *mBuf)
{
   int i =0;
   char *recvBuf = NULLP;
   MsgLen copyCnt =0;
   MsgLen recvBufLen =0;
   E2AP_PDU_t *e2apMsg = NULLP;
   asn_dec_rval_t rval ={0}; /* Decoder return value */
   E2AP_PDU_t e2apasnmsg={0} ;

   DU_LOG("\nDEBUG   -->  E2AP : Received E2AP message buffer");
   ODU_PRINT_MSG(mBuf, 0,0);

   /* Copy mBuf into char array to decode it */
   ODU_GET_MSG_LEN(mBuf, &recvBufLen);
   DU_ALLOC(recvBuf, (Size)recvBufLen);

   if(recvBuf == NULLP)
   {
      DU_LOG("\nERROR  -->  E2AP : Memory allocation failed");
      return;
   }
   if(ODU_COPY_MSG_TO_FIX_BUF(mBuf, 0, recvBufLen, (Data *)recvBuf, &copyCnt) != ROK)
   {
      DU_LOG("\nERROR  -->  E2AP : Failed while copying %d", copyCnt);
      return;
   }

#ifdef DEBUG_ASN_PRINT
   printf("\nDEBUG   -->  E2AP : Received flat buffer to be decoded : ");
   for(i=0; i< recvBufLen; i++)
   {
      printf("%x",recvBuf[i]);
   }
#endif

   /* Decoding flat buffer into E2AP messsage */
   e2apMsg = &e2apasnmsg;
   memset(e2apMsg, 0, sizeof(E2AP_PDU_t));

   rval = aper_decode(0, &asn_DEF_E2AP_PDU, (void **)&e2apMsg, recvBuf, recvBufLen, 0, 0);
   DU_FREE(recvBuf, (Size)recvBufLen);

   if(rval.code == RC_FAIL || rval.code == RC_WMORE)
   {
      DU_LOG("\nERROR  -->  E2AP : ASN decode failed");
      return;
   }
   printf("\n");
   xer_fprint(stdout, &asn_DEF_E2AP_PDU, e2apMsg);

   switch(e2apMsg->present)
   {
      case E2AP_PDU_PR_unsuccessfulOutcome:
         {
            switch(e2apMsg->choice.unsuccessfulOutcome->value.present)
            {
               case UnsuccessfulOutcomeE2__value_PR_E2setupFailure:
                  {
                     procE2SetupFailure(e2apMsg);
                     break;
                  }
               default:
                  {
                     DU_LOG("\nERROR  -->  E2AP : Invalid type of E2AP_PDU_PR_unsuccessfulOutcome  [%d]",\
                           e2apMsg->choice.unsuccessfulOutcome->value.present);
                     return;
                  }
            }
            break;
         }
      case E2AP_PDU_PR_successfulOutcome:
         {
            switch(e2apMsg->choice.successfulOutcome->value.present)
            {
               case SuccessfulOutcomeE2__value_PR_E2setupResponse:
                  {
                     if(!duCb.e2Status)
                     {
                        procE2SetupRsp(e2apMsg);
                     }
                     break;
                  }
               case SuccessfulOutcomeE2__value_PR_E2nodeConfigurationUpdateAcknowledge:
                  {
                     DU_LOG("\nDEBUG   -->  E2AP : E2 node Config update ack message recevied");
                     break;
                  }
               case SuccessfulOutcomeE2__value_PR_ResetResponseE2:
                  {
                     procResetResponse(e2apMsg);
                     break;
                  }
               default:
                  {
                     DU_LOG("\nERROR  -->  E2AP : Invalid type of E2AP_PDU_PR_successfulOutcome  [%d]",\
                           e2apMsg->choice.successfulOutcome->value.present);
                     return;
                  }
            }/* End of switch(successfulOutcome) */
            free(e2apMsg->choice.successfulOutcome);
            break;
         }

      case E2AP_PDU_PR_initiatingMessage:
         {
            switch(e2apMsg->choice.initiatingMessage->value.present)
            {
               case InitiatingMessageE2__value_PR_RICsubscriptionRequest: 
                  {
                     procRicSubsReq(e2apMsg);
                     break;
                  }
               default:
                  {
                     DU_LOG("\nERROR  -->  E2AP : Invalid type of E2AP_PDU_PR_initiatingMessage [%d]",\
                           e2apMsg->choice.initiatingMessage->value.present);
                     return;
                  }
            }/* End of switch(initiatingMessage) */
            free(e2apMsg->choice.initiatingMessage);
            break;
         }
      default:
	 {
	    DU_LOG("\nERROR  -->  E2AP : Invalid type of e2apMsg->present [%d]",e2apMsg->present);
	    return;
	 }
	 free(e2apMsg);

   }/* End of switch(e2apMsg->present) */

} /* End of E2APMsgHdlr */

/**********************************************************************
  End of file
 **********************************************************************/
