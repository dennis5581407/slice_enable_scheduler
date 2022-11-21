/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "02_Aug/rrc_15_3_asn.asn1"
 * 	`asn1c -D ./Aug02 -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_SN_FieldLengthAM_H_
#define	_SN_FieldLengthAM_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SN_FieldLengthAM {
	SN_FieldLengthAM_size12	= 0,
	SN_FieldLengthAM_size18	= 1
} e_SN_FieldLengthAM;

/* SN-FieldLengthAM */
typedef long	 SN_FieldLengthAM_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_SN_FieldLengthAM_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_SN_FieldLengthAM;
extern const asn_INTEGER_specifics_t asn_SPC_SN_FieldLengthAM_specs_1;
asn_struct_free_f SN_FieldLengthAM_free;
asn_struct_print_f SN_FieldLengthAM_print;
asn_constr_check_f SN_FieldLengthAM_constraint;
ber_type_decoder_f SN_FieldLengthAM_decode_ber;
der_type_encoder_f SN_FieldLengthAM_encode_der;
xer_type_decoder_f SN_FieldLengthAM_decode_xer;
xer_type_encoder_f SN_FieldLengthAM_encode_xer;
oer_type_decoder_f SN_FieldLengthAM_decode_oer;
oer_type_encoder_f SN_FieldLengthAM_encode_oer;
per_type_decoder_f SN_FieldLengthAM_decode_uper;
per_type_encoder_f SN_FieldLengthAM_encode_uper;
per_type_decoder_f SN_FieldLengthAM_decode_aper;
per_type_encoder_f SN_FieldLengthAM_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _SN_FieldLengthAM_H_ */
#include <asn_internal.h>
