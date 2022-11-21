/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-InterNodeDefinitions"
 * 	found in "02_Aug/rrc_15_3_asn.asn1"
 * 	`asn1c -D ./Aug02 -fcompound-names -fno-include-deps -findirect-choice -gen-PER -no-gen-example`
 */

#ifndef	_DRX_Info_H_
#define	_DRX_Info_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_CHOICE.h>
#include <NativeEnumerated.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum DRX_Info__drx_LongCycleStartOffset_PR {
	DRX_Info__drx_LongCycleStartOffset_PR_NOTHING,	/* No components present */
	DRX_Info__drx_LongCycleStartOffset_PR_ms10,
	DRX_Info__drx_LongCycleStartOffset_PR_ms20,
	DRX_Info__drx_LongCycleStartOffset_PR_ms32,
	DRX_Info__drx_LongCycleStartOffset_PR_ms40,
	DRX_Info__drx_LongCycleStartOffset_PR_ms60,
	DRX_Info__drx_LongCycleStartOffset_PR_ms64,
	DRX_Info__drx_LongCycleStartOffset_PR_ms70,
	DRX_Info__drx_LongCycleStartOffset_PR_ms80,
	DRX_Info__drx_LongCycleStartOffset_PR_ms128,
	DRX_Info__drx_LongCycleStartOffset_PR_ms160,
	DRX_Info__drx_LongCycleStartOffset_PR_ms256,
	DRX_Info__drx_LongCycleStartOffset_PR_ms320,
	DRX_Info__drx_LongCycleStartOffset_PR_ms512,
	DRX_Info__drx_LongCycleStartOffset_PR_ms640,
	DRX_Info__drx_LongCycleStartOffset_PR_ms1024,
	DRX_Info__drx_LongCycleStartOffset_PR_ms1280,
	DRX_Info__drx_LongCycleStartOffset_PR_ms2048,
	DRX_Info__drx_LongCycleStartOffset_PR_ms2560,
	DRX_Info__drx_LongCycleStartOffset_PR_ms5120,
	DRX_Info__drx_LongCycleStartOffset_PR_ms10240
} DRX_Info__drx_LongCycleStartOffset_PR;
typedef enum DRX_Info__shortDRX__drx_ShortCycle {
	DRX_Info__shortDRX__drx_ShortCycle_ms2	= 0,
	DRX_Info__shortDRX__drx_ShortCycle_ms3	= 1,
	DRX_Info__shortDRX__drx_ShortCycle_ms4	= 2,
	DRX_Info__shortDRX__drx_ShortCycle_ms5	= 3,
	DRX_Info__shortDRX__drx_ShortCycle_ms6	= 4,
	DRX_Info__shortDRX__drx_ShortCycle_ms7	= 5,
	DRX_Info__shortDRX__drx_ShortCycle_ms8	= 6,
	DRX_Info__shortDRX__drx_ShortCycle_ms10	= 7,
	DRX_Info__shortDRX__drx_ShortCycle_ms14	= 8,
	DRX_Info__shortDRX__drx_ShortCycle_ms16	= 9,
	DRX_Info__shortDRX__drx_ShortCycle_ms20	= 10,
	DRX_Info__shortDRX__drx_ShortCycle_ms30	= 11,
	DRX_Info__shortDRX__drx_ShortCycle_ms32	= 12,
	DRX_Info__shortDRX__drx_ShortCycle_ms35	= 13,
	DRX_Info__shortDRX__drx_ShortCycle_ms40	= 14,
	DRX_Info__shortDRX__drx_ShortCycle_ms64	= 15,
	DRX_Info__shortDRX__drx_ShortCycle_ms80	= 16,
	DRX_Info__shortDRX__drx_ShortCycle_ms128	= 17,
	DRX_Info__shortDRX__drx_ShortCycle_ms160	= 18,
	DRX_Info__shortDRX__drx_ShortCycle_ms256	= 19,
	DRX_Info__shortDRX__drx_ShortCycle_ms320	= 20,
	DRX_Info__shortDRX__drx_ShortCycle_ms512	= 21,
	DRX_Info__shortDRX__drx_ShortCycle_ms640	= 22,
	DRX_Info__shortDRX__drx_ShortCycle_spare9	= 23,
	DRX_Info__shortDRX__drx_ShortCycle_spare8	= 24,
	DRX_Info__shortDRX__drx_ShortCycle_spare7	= 25,
	DRX_Info__shortDRX__drx_ShortCycle_spare6	= 26,
	DRX_Info__shortDRX__drx_ShortCycle_spare5	= 27,
	DRX_Info__shortDRX__drx_ShortCycle_spare4	= 28,
	DRX_Info__shortDRX__drx_ShortCycle_spare3	= 29,
	DRX_Info__shortDRX__drx_ShortCycle_spare2	= 30,
	DRX_Info__shortDRX__drx_ShortCycle_spare1	= 31
} e_DRX_Info__shortDRX__drx_ShortCycle;

/* DRX-Info */
typedef struct DRX_Info {
	struct DRX_Info__drx_LongCycleStartOffset {
		DRX_Info__drx_LongCycleStartOffset_PR present;
		union DRX_Info__drx_LongCycleStartOffset_u {
			long	 ms10;
			long	 ms20;
			long	 ms32;
			long	 ms40;
			long	 ms60;
			long	 ms64;
			long	 ms70;
			long	 ms80;
			long	 ms128;
			long	 ms160;
			long	 ms256;
			long	 ms320;
			long	 ms512;
			long	 ms640;
			long	 ms1024;
			long	 ms1280;
			long	 ms2048;
			long	 ms2560;
			long	 ms5120;
			long	 ms10240;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} drx_LongCycleStartOffset;
	struct DRX_Info__shortDRX {
		long	 drx_ShortCycle;
		long	 drx_ShortCycleTimer;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *shortDRX;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DRX_Info_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_drx_ShortCycle_24;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_DRX_Info;
extern asn_SEQUENCE_specifics_t asn_SPC_DRX_Info_specs_1;
extern asn_TYPE_member_t asn_MBR_DRX_Info_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _DRX_Info_H_ */
#include <asn_internal.h>
