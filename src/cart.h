#ifndef CART_H
#define CART_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// #include "nes.h"

#define UNSUPPORTED_FORMAT 0
#define iNES_FORMAT 1
#define NES2_FORMAT 2

typedef struct iNES_Header_T {
	uint8_t signature[4];
	uint8_t PRG_ROM_bank_num;
	uint8_t CHR_ROM_bank_num;
	uint8_t flags6;
	uint8_t flags7;
	uint8_t flags8;
	uint8_t reserved[7];
} iNES_Header_T;

typedef struct NES_T {
	iNES_Header_T iNES_Header;
} NES_T;

int LoadROM(char *rom_filename, NES_T *NES);
int DetectROMFormat(FILE *rom_fp);
int LoadiNES(FILE *rom_fp, NES_T *NES);
void PrintiNESInfo(iNES_Header_T *iNES_Header);

#endif