/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "02_Aug/rrc_15_3_asn.asn1"
 * 	`asn1c -D ./Aug02 -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#include "FrequencyInfoUL.h"

#include "MultiFrequencyBandListNR.h"
#include "SCS-SpecificCarrier.h"
/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static int
memb_scs_SpecificCarrierList_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	/* Determine the number of elements */
	size = _A_CSEQUENCE_FROM_VOID(sptr)->count;
	
	if((size >= 1 && size <= 5)) {
		/* Perform validation of the inner elements */
		return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_type_scs_SpecificCarrierList_constr_4 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..5)) */};
static asn_per_constraints_t asn_PER_type_scs_SpecificCarrierList_constr_4 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  5 }	/* (SIZE(1..5)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_frequencyShift7p5khz_constr_8 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_frequencyShift7p5khz_constr_8 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 0,  0,  0,  0 }	/* (0..0) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_scs_SpecificCarrierList_constr_4 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..5)) */};
static asn_per_constraints_t asn_PER_memb_scs_SpecificCarrierList_constr_4 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 3,  3,  1,  5 }	/* (SIZE(1..5)) */,
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_scs_SpecificCarrierList_4[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_SCS_SpecificCarrier,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_scs_SpecificCarrierList_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_scs_SpecificCarrierList_specs_4 = {
	sizeof(struct FrequencyInfoUL__scs_SpecificCarrierList),
	offsetof(struct FrequencyInfoUL__scs_SpecificCarrierList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_scs_SpecificCarrierList_4 = {
	"scs-SpecificCarrierList",
	"scs-SpecificCarrierList",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_scs_SpecificCarrierList_tags_4,
	sizeof(asn_DEF_scs_SpecificCarrierList_tags_4)
		/sizeof(asn_DEF_scs_SpecificCarrierList_tags_4[0]) - 1, /* 1 */
	asn_DEF_scs_SpecificCarrierList_tags_4,	/* Same as above */
	sizeof(asn_DEF_scs_SpecificCarrierList_tags_4)
		/sizeof(asn_DEF_scs_SpecificCarrierList_tags_4[0]), /* 2 */
	{ &asn_OER_type_scs_SpecificCarrierList_constr_4, &asn_PER_type_scs_SpecificCarrierList_constr_4, SEQUENCE_OF_constraint },
	asn_MBR_scs_SpecificCarrierList_4,
	1,	/* Single element */
	&asn_SPC_scs_SpecificCarrierList_specs_4	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_frequencyShift7p5khz_value2enum_8[] = {
	{ 0,	4,	"true" }
};
static const unsigned int asn_MAP_frequencyShift7p5khz_enum2value_8[] = {
	0	/* true(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_frequencyShift7p5khz_specs_8 = {
	asn_MAP_frequencyShift7p5khz_value2enum_8,	/* "tag" => N; sorted by tag */
	asn_MAP_frequencyShift7p5khz_enum2value_8,	/* N => "tag"; sorted by N */
	1,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_frequencyShift7p5khz_tags_8[] = {
	(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_frequencyShift7p5khz_8 = {
	"frequencyShift7p5khz",
	"frequencyShift7p5khz",
	&asn_OP_NativeEnumerated,
	asn_DEF_frequencyShift7p5khz_tags_8,
	sizeof(asn_DEF_frequencyShift7p5khz_tags_8)
		/sizeof(asn_DEF_frequencyShift7p5khz_tags_8[0]) - 1, /* 1 */
	asn_DEF_frequencyShift7p5khz_tags_8,	/* Same as above */
	sizeof(asn_DEF_frequencyShift7p5khz_tags_8)
		/sizeof(asn_DEF_frequencyShift7p5khz_tags_8[0]), /* 2 */
	{ &asn_OER_type_frequencyShift7p5khz_constr_8, &asn_PER_type_frequencyShift7p5khz_constr_8, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_frequencyShift7p5khz_specs_8	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_FrequencyInfoUL_1[] = {
	{ ATF_POINTER, 2, offsetof(struct FrequencyInfoUL, frequencyBandList),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MultiFrequencyBandListNR,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"frequencyBandList"
		},
	{ ATF_POINTER, 1, offsetof(struct FrequencyInfoUL, absoluteFrequencyPointA),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ARFCN_ValueNR,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"absoluteFrequencyPointA"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FrequencyInfoUL, scs_SpecificCarrierList),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		0,
		&asn_DEF_scs_SpecificCarrierList_4,
		0,
		{ &asn_OER_memb_scs_SpecificCarrierList_constr_4, &asn_PER_memb_scs_SpecificCarrierList_constr_4,  memb_scs_SpecificCarrierList_constraint_1 },
		0, 0, /* No default value */
		"scs-SpecificCarrierList"
		},
	{ ATF_POINTER, 3, offsetof(struct FrequencyInfoUL, additionalSpectrumEmission),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AdditionalSpectrumEmission,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"additionalSpectrumEmission"
		},
	{ ATF_POINTER, 2, offsetof(struct FrequencyInfoUL, p_Max),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_P_Max,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"p-Max"
		},
	{ ATF_POINTER, 1, offsetof(struct FrequencyInfoUL, frequencyShift7p5khz),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_frequencyShift7p5khz_8,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"frequencyShift7p5khz"
		},
};
static const int asn_MAP_FrequencyInfoUL_oms_1[] = { 0, 1, 3, 4, 5 };
static const ber_tlv_tag_t asn_DEF_FrequencyInfoUL_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_FrequencyInfoUL_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* frequencyBandList */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* absoluteFrequencyPointA */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* scs-SpecificCarrierList */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* additionalSpectrumEmission */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* p-Max */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 } /* frequencyShift7p5khz */
};
asn_SEQUENCE_specifics_t asn_SPC_FrequencyInfoUL_specs_1 = {
	sizeof(struct FrequencyInfoUL),
	offsetof(struct FrequencyInfoUL, _asn_ctx),
	asn_MAP_FrequencyInfoUL_tag2el_1,
	6,	/* Count of tags in the map */
	asn_MAP_FrequencyInfoUL_oms_1,	/* Optional members */
	5, 0,	/* Root/Additions */
	6,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_FrequencyInfoUL = {
	"FrequencyInfoUL",
	"FrequencyInfoUL",
	&asn_OP_SEQUENCE,
	asn_DEF_FrequencyInfoUL_tags_1,
	sizeof(asn_DEF_FrequencyInfoUL_tags_1)
		/sizeof(asn_DEF_FrequencyInfoUL_tags_1[0]), /* 1 */
	asn_DEF_FrequencyInfoUL_tags_1,	/* Same as above */
	sizeof(asn_DEF_FrequencyInfoUL_tags_1)
		/sizeof(asn_DEF_FrequencyInfoUL_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_FrequencyInfoUL_1,
	6,	/* Elements count */
	&asn_SPC_FrequencyInfoUL_specs_1	/* Additional specs */
};

