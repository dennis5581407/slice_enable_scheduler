/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "../../ASN1_Input/E2SM_KPM_V_3_0.asn1"
 * 	`asn1c -D ./../../E2_output/E2SM_KPM_v3.0_output -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#include "UEID-ENB.h"

#include "GlobalENB-ID.h"
asn_TYPE_member_t asn_MBR_UEID_ENB_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UEID_ENB, mME_UE_S1AP_ID),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MME_UE_S1AP_ID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"mME-UE-S1AP-ID"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UEID_ENB, gUMMEI),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GUMMEI,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gUMMEI"
		},
	{ ATF_POINTER, 3, offsetof(struct UEID_ENB, m_eNB_UE_X2AP_ID),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ENB_UE_X2AP_ID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"m-eNB-UE-X2AP-ID"
		},
	{ ATF_POINTER, 2, offsetof(struct UEID_ENB, m_eNB_UE_X2AP_ID_Extension),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ENB_UE_X2AP_ID_Extension,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"m-eNB-UE-X2AP-ID-Extension"
		},
	{ ATF_POINTER, 1, offsetof(struct UEID_ENB, globalENB_ID),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GlobalENB_ID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"globalENB-ID"
		},
};
static const int asn_MAP_UEID_ENB_oms_1[] = { 2, 3, 4 };
static const ber_tlv_tag_t asn_DEF_UEID_ENB_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_UEID_ENB_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* mME-UE-S1AP-ID */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* gUMMEI */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* m-eNB-UE-X2AP-ID */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* m-eNB-UE-X2AP-ID-Extension */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 } /* globalENB-ID */
};
asn_SEQUENCE_specifics_t asn_SPC_UEID_ENB_specs_1 = {
	sizeof(struct UEID_ENB),
	offsetof(struct UEID_ENB, _asn_ctx),
	asn_MAP_UEID_ENB_tag2el_1,
	5,	/* Count of tags in the map */
	asn_MAP_UEID_ENB_oms_1,	/* Optional members */
	3, 0,	/* Root/Additions */
	5,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_UEID_ENB = {
	"UEID-ENB",
	"UEID-ENB",
	&asn_OP_SEQUENCE,
	asn_DEF_UEID_ENB_tags_1,
	sizeof(asn_DEF_UEID_ENB_tags_1)
		/sizeof(asn_DEF_UEID_ENB_tags_1[0]), /* 1 */
	asn_DEF_UEID_ENB_tags_1,	/* Same as above */
	sizeof(asn_DEF_UEID_ENB_tags_1)
		/sizeof(asn_DEF_UEID_ENB_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_UEID_ENB_1,
	5,	/* Elements count */
	&asn_SPC_UEID_ENB_specs_1	/* Additional specs */
};
