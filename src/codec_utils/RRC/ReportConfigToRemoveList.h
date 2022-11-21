/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "02_Aug/rrc_15_3_asn.asn1"
 * 	`asn1c -D ./Aug02 -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_ReportConfigToRemoveList_H_
#define	_ReportConfigToRemoveList_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ReportConfigId.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ReportConfigToRemoveList */
typedef struct ReportConfigToRemoveList {
	A_SEQUENCE_OF(ReportConfigId_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ReportConfigToRemoveList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ReportConfigToRemoveList;
extern asn_SET_OF_specifics_t asn_SPC_ReportConfigToRemoveList_specs_1;
extern asn_TYPE_member_t asn_MBR_ReportConfigToRemoveList_1[1];
extern asn_per_constraints_t asn_PER_type_ReportConfigToRemoveList_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _ReportConfigToRemoveList_H_ */
#include <asn_internal.h>
