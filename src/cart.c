#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cart.h"
#include "error.h"
#include "memory.h"
#include "nes.h"
#include "debug.h"

enum CartridgeFormat DetectROMFormat(FILE *rom_fp) {
	uint8_t header_buffer[16];
	uint8_t ines_signature[] = "NES\x1A";

	rewind(rom_fp);

	if (fread(header_buffer, iNESHeaderSize, 1, rom_fp) != 1) {
		LOG(Error,stderr,"Unable to read ROM header");
		return ErrorFormat;
	}

	if (!memcmp(header_buffer, ines_signature, iNESSignatureSize)) {
		if ((header_buffer[7] & 0b00001100) == 0b00001000) {
			return Nes2Format;
		}
		return iNesFormat;
	}

	LOG(Error,stderr,"Unsupported file format");
	return UnsupportedFormat;
}

enum SuccessFail LoadiNES(FILE *rom_fp, struct NES_T *NES) {
	rewind(rom_fp);

	if (fread(&NES->iNES_Header, iNESHeaderSize, 1, rom_fp) != 1) {
		LOG(Error,stderr," Unable to read ROM header");
		return Fail;
	}

	if (fread(&NES->mem[PRGROMBank0],
		  NES->iNES_Header.PRG_ROM_bank_num * PRGROMBankSize, 1,
		  rom_fp) != 1) {
		LOG(Error,stderr,"Unable to read PRG ROM into mem");
		return Fail;
	}

	if (NES->iNES_Header.PRG_ROM_bank_num == 1) {
		memcpy(&NES->mem[PRGROMBank1], &NES->mem[PRGROMBank0],
		       NES->iNES_Header.PRG_ROM_bank_num * PRGROMBankSize);
	}
	return Success;
}

enum SuccessFail LoadROM(char *rom_filename, struct NES_T *NES) {
	FILE *rom_fp = fopen(rom_filename, "rb");

	if (rom_fp == NULL) {
		LOG(Error,stderr,"Unable to open ROM");
		return Fail;
	}

	enum CartridgeFormat rom_format = DetectROMFormat(rom_fp);

	enum SuccessFail load_result = Fail;

	switch (rom_format) {
	case iNesFormat:
		LOG(Info,stderr,"Detected iNES format\n");
		load_result = LoadiNES(rom_fp, NES);
		PrintiNESInfo(rom_filename, &NES->iNES_Header);
		break;
	case Nes2Format:
		LOG(Info,stderr,"Detected NES2.0 format - Currently unsupported");
		break;
	case ErrorFormat:
		LOG(Error, stderr, "Error reading ROM");
		break;
	case UnsupportedFormat:
		LOG(Error, stderr,"Unsupported format for ROM");
		break;
	}
	return load_result;
}
