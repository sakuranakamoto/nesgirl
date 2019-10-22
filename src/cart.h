#ifndef CART_H
#define CART_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "nes.h"

enum iNESHeaderMasks {
	FourScreenMirror = 0b00001000,
	VerticleMirror = 0b00000001,
	Battery = 0b00000010,
	Trainer = 0b00000100,
	VSUnisystem = 0b00000001,
	PlayChoice10 = 0b00000010
};

enum CartridgeFormat { UnsupportedFormat, iNesFormat, Nes2Format };

int LoadROM(char *rom_filename, NES_T *NES);
int DetectROMFormat(FILE *rom_fp);
int LoadiNESHeader(FILE *rom_fp, NES_T *NES);
void PrintiNESInfo(char *rom_filename, iNES_Header_T *iNES_Header);

#endif