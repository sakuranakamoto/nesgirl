#ifndef CART_H
#define CART_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "nes.h"


#define UNSUPPORTED_FORMAT 0
#define iNES_FORMAT 1
#define NES2_FORMAT 2

int LoadROM(char *rom_filename, NES_T *NES);
int DetectROMFormat(FILE *rom_fp);
int LoadiNESHeader(FILE *rom_fp, NES_T *NES);
void PrintiNESInfo(char *rom_filename, iNES_Header_T *iNES_Header);

#endif