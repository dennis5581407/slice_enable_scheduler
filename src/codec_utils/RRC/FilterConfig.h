/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "02_Aug/rrc_15_3_asn.asn1"
 * 	`asn1c -D ./Aug02 -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_FilterConfig_H_
#define	_FilterConfig_H_


#include <asn_application.h>

/* Including external dependencies */
#include "FilterCoefficient.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* FilterConfig */
typedef struct FilterConfig {
	FilterCoefficient_t	*filterCoefficientRSRP;	/* DEFAULT 4 */
	FilterCoefficient_t	*filterCoefficientRSRQ;	/* DEFAULT 4 */
	FilterCoefficient_t	*filterCoefficientRS_SINR;	/* DEFAULT 4 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} FilterConfig_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_FilterConfig;
extern asn_SEQUENCE_specifics_t asn_SPC_FilterConfig_specs_1;
extern asn_TYPE_member_t asn_MBR_FilterConfig_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _FilterConfig_H_ */
#include <asn_internal.h>
