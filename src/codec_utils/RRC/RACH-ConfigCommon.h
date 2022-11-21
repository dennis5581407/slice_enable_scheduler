/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "02_Aug/rrc_15_3_asn.asn1"
 * 	`asn1c -D ./Aug02 -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_RACH_ConfigCommon_H_
#define	_RACH_ConfigCommon_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RACH-ConfigGeneric.h"
#include <NativeInteger.h>
#include <NativeEnumerated.h>
#include "RSRP-Range.h"
#include "SubcarrierSpacing.h"
#include <constr_CHOICE.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR {
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_NOTHING,	/* No components present */
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_oneEighth,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_oneFourth,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_oneHalf,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_one,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_two,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_four,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_eight,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_sixteen
} RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR;
typedef enum RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth {
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n4	= 0,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n8	= 1,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n12	= 2,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n16	= 3,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n20	= 4,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n24	= 5,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n28	= 6,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n32	= 7,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n36	= 8,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n40	= 9,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n44	= 10,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n48	= 11,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n52	= 12,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n56	= 13,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n60	= 14,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth_n64	= 15
} e_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneEighth;
typedef enum RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth {
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n4	= 0,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n8	= 1,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n12	= 2,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n16	= 3,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n20	= 4,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n24	= 5,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n28	= 6,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n32	= 7,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n36	= 8,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n40	= 9,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n44	= 10,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n48	= 11,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n52	= 12,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n56	= 13,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n60	= 14,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth_n64	= 15
} e_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneFourth;
typedef enum RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf {
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n4	= 0,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n8	= 1,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n12	= 2,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n16	= 3,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n20	= 4,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n24	= 5,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n28	= 6,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n32	= 7,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n36	= 8,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n40	= 9,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n44	= 10,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n48	= 11,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n52	= 12,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n56	= 13,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n60	= 14,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf_n64	= 15
} e_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__oneHalf;
typedef enum RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one {
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n4	= 0,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n8	= 1,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n12	= 2,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n16	= 3,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n20	= 4,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n24	= 5,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n28	= 6,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n32	= 7,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n36	= 8,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n40	= 9,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n44	= 10,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n48	= 11,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n52	= 12,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n56	= 13,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n60	= 14,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one_n64	= 15
} e_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__one;
typedef enum RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two {
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n4	= 0,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n8	= 1,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n12	= 2,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n16	= 3,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n20	= 4,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n24	= 5,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n28	= 6,
	RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two_n32	= 7
} e_RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB__two;
typedef enum RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA {
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b56	= 0,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b144	= 1,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b208	= 2,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b256	= 3,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b282	= 4,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b480	= 5,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b640	= 6,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b800	= 7,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b1000	= 8,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_b72	= 9,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare6	= 10,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare5	= 11,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare4	= 12,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare3	= 13,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare2	= 14,
	RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA_spare1	= 15
} e_RACH_ConfigCommon__groupBconfigured__ra_Msg3SizeGroupA;
typedef enum RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB {
	RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_minusinfinity	= 0,
	RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB0	= 1,
	RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB5	= 2,
	RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB8	= 3,
	RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB10	= 4,
	RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB12	= 5,
	RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB15	= 6,
	RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB_dB18	= 7
} e_RACH_ConfigCommon__groupBconfigured__messagePowerOffsetGroupB;
typedef enum RACH_ConfigCommon__ra_ContentionResolutionTimer {
	RACH_ConfigCommon__ra_ContentionResolutionTimer_sf8	= 0,
	RACH_ConfigCommon__ra_ContentionResolutionTimer_sf16	= 1,
	RACH_ConfigCommon__ra_ContentionResolutionTimer_sf24	= 2,
	RACH_ConfigCommon__ra_ContentionResolutionTimer_sf32	= 3,
	RACH_ConfigCommon__ra_ContentionResolutionTimer_sf40	= 4,
	RACH_ConfigCommon__ra_ContentionResolutionTimer_sf48	= 5,
	RACH_ConfigCommon__ra_ContentionResolutionTimer_sf56	= 6,
	RACH_ConfigCommon__ra_ContentionResolutionTimer_sf64	= 7
} e_RACH_ConfigCommon__ra_ContentionResolutionTimer;
typedef enum RACH_ConfigCommon__prach_RootSequenceIndex_PR {
	RACH_ConfigCommon__prach_RootSequenceIndex_PR_NOTHING,	/* No components present */
	RACH_ConfigCommon__prach_RootSequenceIndex_PR_l839,
	RACH_ConfigCommon__prach_RootSequenceIndex_PR_l139
} RACH_ConfigCommon__prach_RootSequenceIndex_PR;
typedef enum RACH_ConfigCommon__restrictedSetConfig {
	RACH_ConfigCommon__restrictedSetConfig_unrestrictedSet	= 0,
	RACH_ConfigCommon__restrictedSetConfig_restrictedSetTypeA	= 1,
	RACH_ConfigCommon__restrictedSetConfig_restrictedSetTypeB	= 2
} e_RACH_ConfigCommon__restrictedSetConfig;
typedef enum RACH_ConfigCommon__msg3_transformPrecoder {
	RACH_ConfigCommon__msg3_transformPrecoder_enabled	= 0
} e_RACH_ConfigCommon__msg3_transformPrecoder;

/* RACH-ConfigCommon */
typedef struct RACH_ConfigCommon {
	RACH_ConfigGeneric_t	 rach_ConfigGeneric;
	long	*totalNumberOfRA_Preambles;	/* OPTIONAL */
	struct RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB {
		RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR present;
		union RACH_ConfigCommon__ssb_perRACH_OccasionAndCB_PreamblesPerSSB_u {
			long	 oneEighth;
			long	 oneFourth;
			long	 oneHalf;
			long	 one;
			long	 two;
			long	 four;
			long	 eight;
			long	 sixteen;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ssb_perRACH_OccasionAndCB_PreamblesPerSSB;
	struct RACH_ConfigCommon__groupBconfigured {
		long	 ra_Msg3SizeGroupA;
		long	 messagePowerOffsetGroupB;
		long	 numberOfRA_PreamblesGroupA;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *groupBconfigured;
	long	 ra_ContentionResolutionTimer;
	RSRP_Range_t	*rsrp_ThresholdSSB;	/* OPTIONAL */
	RSRP_Range_t	*rsrp_ThresholdSSB_SUL;	/* OPTIONAL */
	struct RACH_ConfigCommon__prach_RootSequenceIndex {
		RACH_ConfigCommon__prach_RootSequenceIndex_PR present;
		union RACH_ConfigCommon__prach_RootSequenceIndex_u {
			long	 l839;
			long	 l139;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} prach_RootSequenceIndex;
	SubcarrierSpacing_t	*msg1_SubcarrierSpacing;	/* OPTIONAL */
	long	 restrictedSetConfig;
	long	*msg3_transformPrecoder;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RACH_ConfigCommon_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_oneEighth_5;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_oneFourth_22;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_oneHalf_39;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_one_56;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_two_73;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_ra_Msg3SizeGroupA_86;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_messagePowerOffsetGroupB_103;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_ra_ContentionResolutionTimer_113;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_restrictedSetConfig_128;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_msg3_transformPrecoder_132;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_RACH_ConfigCommon;
extern asn_SEQUENCE_specifics_t asn_SPC_RACH_ConfigCommon_specs_1;
extern asn_TYPE_member_t asn_MBR_RACH_ConfigCommon_1[11];

#ifdef __cplusplus
}
#endif

#endif	/* _RACH_ConfigCommon_H_ */
#include <asn_internal.h>
