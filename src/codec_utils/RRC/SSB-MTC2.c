/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "02_Aug/rrc_15_3_asn.asn1"
 * 	`asn1c -D ./Aug02 -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#include "SSB-MTC2.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static int
memb_pci_List_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size >= 1 && size <= 64)) {
		/* Perform validation of the inner elements */
		return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_type_pci_List_constr_2 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..64)) */};
static asn_per_constraints_t asn_PER_type_pci_List_constr_2 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 6,  6,  1,  64 }	/* (SIZE(1..64)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_periodicity_constr_4 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_periodicity_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_pci_List_constr_2 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..64)) */};
static asn_per_constraints_t asn_PER_memb_pci_List_constr_2 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 6,  6,  1,  64 }	/* (SIZE(1..64)) */,
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_pci_List_2[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_PhysCellId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_pci_List_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_pci_List_specs_2 = {
	sizeof(struct SSB_MTC2__pci_List),
	offsetof(struct SSB_MTC2__pci_List, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_pci_List_2 = {
	"pci-List",
	"pci-List",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_pci_List_tags_2,
	sizeof(asn_DEF_pci_List_tags_2)
		/sizeof(asn_DEF_pci_List_tags_2[0]) - 1, /* 1 */
	asn_DEF_pci_List_tags_2,	/* Same as above */
	sizeof(asn_DEF_pci_List_tags_2)
		/sizeof(asn_DEF_pci_List_tags_2[0]), /* 2 */
	{ &asn_OER_type_pci_List_constr_2, &asn_PER_type_pci_List_constr_2, SEQUENCE_OF_constraint },
	asn_MBR_pci_List_2,
	1,	/* Single element */
	&asn_SPC_pci_List_specs_2	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_periodicity_value2enum_4[] = {
	{ 0,	3,	"sf5" },
	{ 1,	4,	"sf10" },
	{ 2,	4,	"sf20" },
	{ 3,	4,	"sf40" },
	{ 4,	4,	"sf80" },
	{ 5,	6,	"spare3" },
	{ 6,	6,	"spare2" },
	{ 7,	6,	"spare1" }
};
static const unsigned int asn_MAP_periodicity_enum2value_4[] = {
	1,	/* sf10(1) */
	2,	/* sf20(2) */
	3,	/* sf40(3) */
	0,	/* sf5(0) */
	4,	/* sf80(4) */
	7,	/* spare1(7) */
	6,	/* spare2(6) */
	5	/* spare3(5) */
};
static const asn_INTEGER_specifics_t asn_SPC_periodicity_specs_4 = {
	asn_MAP_periodicity_value2enum_4,	/* "tag" => N; sorted by tag */
	asn_MAP_periodicity_enum2value_4,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_periodicity_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_periodicity_4 = {
	"periodicity",
	"periodicity",
	&asn_OP_NativeEnumerated,
	asn_DEF_periodicity_tags_4,
	sizeof(asn_DEF_periodicity_tags_4)
		/sizeof(asn_DEF_periodicity_tags_4[0]) - 1, /* 1 */
	asn_DEF_periodicity_tags_4,	/* Same as above */
	sizeof(asn_DEF_periodicity_tags_4)
		/sizeof(asn_DEF_periodicity_tags_4[0]), /* 2 */
	{ &asn_OER_type_periodicity_constr_4, &asn_PER_type_periodicity_constr_4, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_periodicity_specs_4	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_SSB_MTC2_1[] = {
	{ ATF_POINTER, 1, offsetof(struct SSB_MTC2, pci_List),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_pci_List_2,
		0,
		{ &asn_OER_memb_pci_List_constr_2, &asn_PER_memb_pci_List_constr_2,  memb_pci_List_constraint_1 },
		0, 0, /* No default value */
		"pci-List"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SSB_MTC2, periodicity),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_periodicity_4,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"periodicity"
		},
};
static const int asn_MAP_SSB_MTC2_oms_1[] = { 0 };
static const ber_tlv_tag_t asn_DEF_SSB_MTC2_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SSB_MTC2_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pci-List */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* periodicity */
};
asn_SEQUENCE_specifics_t asn_SPC_SSB_MTC2_specs_1 = {
	sizeof(struct SSB_MTC2),
	offsetof(struct SSB_MTC2, _asn_ctx),
	asn_MAP_SSB_MTC2_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_SSB_MTC2_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_SSB_MTC2 = {
	"SSB-MTC2",
	"SSB-MTC2",
	&asn_OP_SEQUENCE,
	asn_DEF_SSB_MTC2_tags_1,
	sizeof(asn_DEF_SSB_MTC2_tags_1)
		/sizeof(asn_DEF_SSB_MTC2_tags_1[0]), /* 1 */
	asn_DEF_SSB_MTC2_tags_1,	/* Same as above */
	sizeof(asn_DEF_SSB_MTC2_tags_1)
		/sizeof(asn_DEF_SSB_MTC2_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_SSB_MTC2_1,
	2,	/* Elements count */
	&asn_SPC_SSB_MTC2_specs_1	/* Additional specs */
};

