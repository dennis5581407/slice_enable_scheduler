/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-InterNodeDefinitions"
 * 	found in "02_Aug/rrc_15_3_asn.asn1"
 * 	`asn1c -D ./Aug02 -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_AS_Context_H_
#define	_AS_Context_H_


#include <asn_application.h>

/* Including external dependencies */
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ReestablishmentInfo;
struct ConfigRestrictInfoSCG;
struct RAN_NotificationAreaInfo;

/* AS-Context */
typedef struct AS_Context {
	struct ReestablishmentInfo	*reestablishmentInfo;	/* OPTIONAL */
	struct ConfigRestrictInfoSCG	*configRestrictInfo;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	struct AS_Context__ext1 {
		struct RAN_NotificationAreaInfo	*ran_NotificationAreaInfo;	/* OPTIONAL */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *ext1;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AS_Context_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AS_Context;
extern asn_SEQUENCE_specifics_t asn_SPC_AS_Context_specs_1;
extern asn_TYPE_member_t asn_MBR_AS_Context_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _AS_Context_H_ */
#include <asn_internal.h>
