#ifndef NES_H
#define NES_H
#include <stdint.h>

typedef struct iNES_Header_T {
	uint8_t signature[4];
	uint8_t PRG_ROM_bank_num;
	uint8_t CHR_ROM_bank_num;
	uint8_t flags6;
	uint8_t flags7;
	uint8_t flags8;
	uint8_t reserved[7];
} iNES_Header_T;

// typedef struct CPU_T {

// } CPU_T;

typedef struct NES_T {
	iNES_Header_T iNES_Header;
	uint8_t *mem;
} NES_T;

#endif