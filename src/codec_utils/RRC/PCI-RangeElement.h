/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	found in "02_Aug/rrc_15_3_asn.asn1"
 * 	`asn1c -D ./Aug02 -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_PCI_RangeElement_H_
#define	_PCI_RangeElement_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PCI-RangeIndex.h"
#include "PCI-Range.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PCI-RangeElement */
typedef struct PCI_RangeElement {
	PCI_RangeIndex_t	 pci_RangeIndex;
	PCI_Range_t	 pci_Range;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PCI_RangeElement_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PCI_RangeElement;
extern asn_SEQUENCE_specifics_t asn_SPC_PCI_RangeElement_specs_1;
extern asn_TYPE_member_t asn_MBR_PCI_RangeElement_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _PCI_RangeElement_H_ */
#include <asn_internal.h>
