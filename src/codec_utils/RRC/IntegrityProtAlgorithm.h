/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "02_Aug/rrc_15_3_asn.asn1"
 * 	`asn1c -D ./Aug02 -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_IntegrityProtAlgorithm_H_
#define	_IntegrityProtAlgorithm_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum IntegrityProtAlgorithm {
	IntegrityProtAlgorithm_nia0	= 0,
	IntegrityProtAlgorithm_nia1	= 1,
	IntegrityProtAlgorithm_nia2	= 2,
	IntegrityProtAlgorithm_nia3	= 3,
	IntegrityProtAlgorithm_spare4	= 4,
	IntegrityProtAlgorithm_spare3	= 5,
	IntegrityProtAlgorithm_spare2	= 6,
	IntegrityProtAlgorithm_spare1	= 7
	/*
	 * Enumeration is extensible
	 */
} e_IntegrityProtAlgorithm;

/* IntegrityProtAlgorithm */
typedef long	 IntegrityProtAlgorithm_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_IntegrityProtAlgorithm_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_IntegrityProtAlgorithm;
extern const asn_INTEGER_specifics_t asn_SPC_IntegrityProtAlgorithm_specs_1;
asn_struct_free_f IntegrityProtAlgorithm_free;
asn_struct_print_f IntegrityProtAlgorithm_print;
asn_constr_check_f IntegrityProtAlgorithm_constraint;
ber_type_decoder_f IntegrityProtAlgorithm_decode_ber;
der_type_encoder_f IntegrityProtAlgorithm_encode_der;
xer_type_decoder_f IntegrityProtAlgorithm_decode_xer;
xer_type_encoder_f IntegrityProtAlgorithm_encode_xer;
oer_type_decoder_f IntegrityProtAlgorithm_decode_oer;
oer_type_encoder_f IntegrityProtAlgorithm_encode_oer;
per_type_decoder_f IntegrityProtAlgorithm_decode_uper;
per_type_encoder_f IntegrityProtAlgorithm_encode_uper;
per_type_decoder_f IntegrityProtAlgorithm_decode_aper;
per_type_encoder_f IntegrityProtAlgorithm_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _IntegrityProtAlgorithm_H_ */
#include <asn_internal.h>
