#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cart.h"
#include "error.h"
#include "memory.h"
#include "nes.h"
#include "debug.h"

int DetectROMFormat(FILE *rom_fp) {
	uint8_t header_buffer[16];
	uint8_t ines_signature[] = "NES\x1A";

	rewind(rom_fp);

	if (fread(header_buffer, 1, sizeof(header_buffer), rom_fp) !=
	    sizeof(header_buffer)) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Unable to read ROM header");
		return ERROR_READ;
	}

	if (!memcmp(header_buffer, ines_signature, 4)) {
		if ((header_buffer[7] & 0b00001100) == 0b00001000) {
			return NES2_FORMAT;
		}
		return iNES_FORMAT;
	}

	PrintError((const char *)__PRETTY_FUNCTION__, __FILE__, __LINE__,
		   "[-] Unsupported file format");
	return UNSUPPORTED_FORMAT;
}

int LoadiNESHeader(FILE *rom_fp, NES_T *NES) {
	rewind(rom_fp);

	if (fread(&NES->iNES_Header, sizeof(iNES_Header_T), 1, rom_fp) != 1) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Unable to read ROM header");
		return FAIL;
	}

	if (fread(&NES->mem[PRG_ROM_BANK_0],
		  sizeof(NES->iNES_Header.PRG_ROM_bank_num * PRG_ROM_BANK_SIZE),
		  1, rom_fp) != 1) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Unable to read PRG ROM into mem");
		return FAIL;
	}

	if (NES->iNES_Header.PRG_ROM_bank_num == 1) {
		memcpy(&NES->mem[PRG_ROM_BANK_1], &NES->mem[PRG_ROM_BANK_0],
		       sizeof(NES->iNES_Header.PRG_ROM_bank_num * 0x4000));
	}

	return SUCCESS;
}


int LoadROM(char *rom_filename, NES_T *NES) {
	FILE *rom_fp = fopen(rom_filename, "rb");
	int rom_format, load_result;

	if (rom_fp == NULL) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Unable to open ROM");
		return FAIL;
	}

	rom_format = DetectROMFormat(rom_fp);

	if (rom_format == ERROR_READ) {
		fclose(rom_fp);
		return FAIL;
	}

	if (rom_format == UNSUPPORTED_FORMAT) {
		fclose(rom_fp);
		return FAIL;
	}

	switch (rom_format) {
	case iNES_FORMAT:
		printf("[+] Detected iNES format\n");
		load_result = LoadiNESHeader(rom_fp, NES);
		PrintiNESInfo(rom_filename, &NES->iNES_Header);
		//Print Memory map
		break;
	case NES2_FORMAT:
		printf("[+] Detected NES2.0 format\n");
		// load_result = LoadiNESHeader2();
		break;
	case UNSUPPORTED_FORMAT:
		fprintf(stderr, "[-] Unsupported file format for %s\n",
			rom_filename);
		fclose(rom_fp);
		return FAIL;
	}

	return SUCCESS;
}
