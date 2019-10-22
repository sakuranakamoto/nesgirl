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

typedef struct CPU_T {
	uint8_t A;
	uint8_t X;
	uint8_t Y;
	uint8_t PC;
	uint8_t S;
	uint8_t P;
} CPU_T;

typedef struct NES_T {
	iNES_Header_T iNES_Header;
	CPU_T CPU;
	uint8_t *mem;
} NES_T;

#endif