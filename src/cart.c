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

	if (fread(header_buffer, HeaderSize, 1, rom_fp) !=
	    1) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Unable to read ROM header");
		return ErrorFormat;
	}

	if (!memcmp(header_buffer, ines_signature, 4)) {
		if ((header_buffer[7] & 0b00001100) == 0b00001000) {
			return Nes2Format;
		}
		return iNesFormat;
	}

	PrintError((const char *)__PRETTY_FUNCTION__, __FILE__, __LINE__,
		   "[-] Unsupported file format");
	return UnsupportedFormat;
}

enum SuccessFail LoadiNESHeader(FILE *rom_fp, struct NES_T *NES) {
	rewind(rom_fp);

	if (fread(&NES->iNES_Header, sizeof(struct iNES_Header_T), 1, rom_fp) != 1) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Unable to read ROM header");
		return Fail;
	}

	if (fread(&NES->mem[PRGROMBank0],
		  sizeof(NES->iNES_Header.PRG_ROM_bank_num * PRGROMBankSize), 1,
		  rom_fp) != 1) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Unable to read PRG ROM into mem");
		return Fail;
	}

	if (NES->iNES_Header.PRG_ROM_bank_num == 1) {
		memcpy(&NES->mem[PRGROMBank1], &NES->mem[PRGROMBank0],
		       sizeof(NES->iNES_Header.PRG_ROM_bank_num * PRGROMBankSize));
	}

	return Success;
}

enum SuccessFail LoadROM(char *rom_filename, struct NES_T *NES) {
	FILE *rom_fp = fopen(rom_filename, "rb");
	int rom_format, load_result;

	if (rom_fp == NULL) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Unable to open ROM");
		return Fail;
	}

	rom_format = DetectROMFormat(rom_fp);

	if (rom_format == ErrorFormat) {
		fclose(rom_fp);
		return Fail;
	}

	if (rom_format == UnsupportedFormat) {
		fclose(rom_fp);
		return Fail;
	}

	switch (rom_format) {
	case iNesFormat:
		printf("[+] Detected iNES format\n");
		load_result = LoadiNESHeader(rom_fp, NES);
		PrintiNESInfo(rom_filename, &NES->iNES_Header);
		//Print Memory map
		break;
	case Nes2Format:
		printf("[+] Detected NES2.0 format\n");
		// load_result = LoadiNESHeader2();
		break;
	case UnsupportedFormat:
		fprintf(stderr, "[-] Unsupported file format for %s\n",
			rom_filename);
		fclose(rom_fp);
		return Fail;
	}
	return Success;
}
