#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cart.h"
#include "error.h"

int DetectROMFormat(FILE *rom_fp) {
	uint8_t header_buffer[16];
	uint8_t ines_signature[] = "NES\x1A";

	if (fread(header_buffer, 1, sizeof(header_buffer), rom_fp) !=
	    sizeof(header_buffer)) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Unable to read ROM header");
		return ERROR_READ;
	}

	rewind(rom_fp);

	if (!memcmp(header_buffer, ines_signature, 4)) {
		if ((header_buffer[7] & 0b00001100) == 0b00001000) {
			return NES2_FORMAT;
		}
		return iNES_FORMAT;
	}

	return UNSUPPORTED_FORMAT;
}

int LoadiNES(FILE *rom_fp, NES_T *NES) {
	if (fread(&NES->iNES_Header, 1, sizeof(&NES->iNES_Header), rom_fp) !=
	    sizeof(&NES->iNES_Header)) {
		PrintError((const char *)__PRETTY_FUNCTION__, __FILE__,
			   __LINE__, "[-] Unable to read ROM header");
		return FAIL;
	}

	return SUCCESS;
}

void PrintiNESInfo(iNES_Header_T *iNES_Header) {
	printf("[=] Printing ROM info:\n");

	printf("\tROM signature:\t%.*s\n", (int)sizeof(iNES_Header->signature),
	       iNES_Header->signature);

	printf("\tPRG ROM size:\t%d KB\n",
	       0x10 * iNES_Header->PRG_ROM_bank_num);

	printf("\tPRG RAM size:\t");
	if (!iNES_Header->flags8) {
		printf("8 KB\n");
	} else {
		printf("%d KB\n", iNES_Header->flags8 * 0x08);
	}

	printf("\tCHR ROM size:\t%d KB\n", 0x8 * iNES_Header->CHR_ROM_bank_num);

	printf("\tMirror type:\t");
	if (iNES_Header->flags6 & 0b00001000) {
		printf("4 screens\n");
	} else {
		if (iNES_Header->flags6 & 0b00000001) {
			printf("Verticle\n");
		} else {
			printf("Horizontal\n");
		}
	}

	printf("\tBattery:\t");
	if (iNES_Header->flags6 & 0b00000010) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}

	printf("\tMapper:\t\t%d\n", (iNES_Header->flags6 & 0b11110000) >> 4);

	printf("\tVS Unisystem:\t");
	if (iNES_Header->flags7 & 0b00000001) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}

	printf("\tPlaychoice-10:\t");
	if (iNES_Header->flags7 & 0b00000010) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
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
		fprintf(stderr, "[-] Unsupported file format for %s\n",
			rom_filename);
		fclose(rom_fp);
		return FAIL;
	}

	switch (rom_format) {
	case iNES_FORMAT:
		printf("[+] Detected iNES format\n");
		load_result = LoadiNES(rom_fp, NES);
		break;
	case NES2_FORMAT:
		printf("[+] Detected NES2.0 format\n");
		// load_result = LoadiNES2();
		break;
	case UNSUPPORTED_FORMAT:
		fprintf(stderr, "[-] Unsupported file format for %s\n",
			rom_filename);
		fclose(rom_fp);
		return FAIL;
	}

	return SUCCESS;
}
