#ifndef NES_H
#define NES_H
#include <stdint.h>

struct iNES_Header_T {
	uint8_t signature[4];
	uint8_t PRG_ROM_bank_num;
	uint8_t CHR_ROM_bank_num;
	uint8_t flags6;
	uint8_t flags7;
	uint8_t flags8;
	uint8_t reserved[7];
};

struct CPU_T {
	uint8_t A;
	uint8_t X;
	uint8_t Y;
	uint8_t PC;
	uint8_t S;
	uint8_t P;
};

struct NES_T {
	struct iNES_Header_T iNES_Header;
	struct CPU_T CPU;
	uint8_t *mem;
};

#endif