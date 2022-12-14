/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "../ASN1_Input/rrc_15_3_asn.asn1"
 * 	`asn1c -D ../RRC_output_14Nov/ -fcompound-names -fno-include-deps -findirect-choice -gen-PER`
 */

#include "PUCCH-ResourceSet.h"

static int
memb_resourceList_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size >= 1 && size <= 32)) {
		/* Perform validation of the inner elements */
		return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_maxPayloadMinus1_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 4 && value <= 256)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_type_resourceList_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..32)) */};
static asn_per_constraints_t asn_PER_type_resourceList_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_resourceList_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..32)) */};
static asn_per_constraints_t asn_PER_memb_resourceList_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_maxPayloadMinus1_constr_5 CC_NOTUSED = {
	{ 2, 1 }	/* (4..256) */,
	-1};
static asn_per_constraints_t asn_PER_memb_maxPayloadMinus1_constr_5 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 8,  8,  4,  256 }	/* (4..256) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_resourceList_3[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_PUCCH_ResourceId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_resourceList_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_resourceList_specs_3 = {
	sizeof(struct PUCCH_ResourceSet__resourceList),
	offsetof(struct PUCCH_ResourceSet__resourceList, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_resourceList_3 = {
	"resourceList",
	"resourceList",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_resourceList_tags_3,
	sizeof(asn_DEF_resourceList_tags_3)
		/sizeof(asn_DEF_resourceList_tags_3[0]) - 1, /* 1 */
	asn_DEF_resourceList_tags_3,	/* Same as above */
	sizeof(asn_DEF_resourceList_tags_3)
		/sizeof(asn_DEF_resourceList_tags_3[0]), /* 2 */
	{ &asn_OER_type_resourceList_constr_3, &asn_PER_type_resourceList_constr_3, SEQUENCE_OF_constraint },
	asn_MBR_resourceList_3,
	1,	/* Single element */
	&asn_SPC_resourceList_specs_3	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_PUCCH_ResourceSet_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PUCCH_ResourceSet, pucch_ResourceSetId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PUCCH_ResourceSetId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pucch-ResourceSetId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PUCCH_ResourceSet, resourceList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_resourceList_3,
		0,
		{ &asn_OER_memb_resourceList_constr_3, &asn_PER_memb_resourceList_constr_3,  memb_resourceList_constraint_1 },
		0, 0, /* No default value */
		"resourceList"
		},
	{ ATF_POINTER, 1, offsetof(struct PUCCH_ResourceSet, maxPayloadMinus1),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_maxPayloadMinus1_constr_5, &asn_PER_memb_maxPayloadMinus1_constr_5,  memb_maxPayloadMinus1_constraint_1 },
		0, 0, /* No default value */
		"maxPayloadMinus1"
		},
};
static const int asn_MAP_PUCCH_ResourceSet_oms_1[] = { 2 };
static const ber_tlv_tag_t asn_DEF_PUCCH_ResourceSet_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_PUCCH_ResourceSet_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pucch-ResourceSetId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* resourceList */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* maxPayloadMinus1 */
};
asn_SEQUENCE_specifics_t asn_SPC_PUCCH_ResourceSet_specs_1 = {
	sizeof(struct PUCCH_ResourceSet),
	offsetof(struct PUCCH_ResourceSet, _asn_ctx),
	asn_MAP_PUCCH_ResourceSet_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_PUCCH_ResourceSet_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_PUCCH_ResourceSet = {
	"PUCCH-ResourceSet",
	"PUCCH-ResourceSet",
	&asn_OP_SEQUENCE,
	asn_DEF_PUCCH_ResourceSet_tags_1,
	sizeof(asn_DEF_PUCCH_ResourceSet_tags_1)
		/sizeof(asn_DEF_PUCCH_ResourceSet_tags_1[0]), /* 1 */
	asn_DEF_PUCCH_ResourceSet_tags_1,	/* Same as above */
	sizeof(asn_DEF_PUCCH_ResourceSet_tags_1)
		/sizeof(asn_DEF_PUCCH_ResourceSet_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_PUCCH_ResourceSet_1,
	3,	/* Elements count */
	&asn_SPC_PUCCH_ResourceSet_specs_1	/* Additional specs */
};

