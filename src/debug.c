#include "cart.h"

void PrintiNESInfo(char *rom_filename, struct iNES_Header_T *iNES_Header) {
	printf("[+] Printing iNES ROM info for %s:\n", rom_filename);

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
	if (iNES_Header->flags6 & FourScreenMirror) {
		printf("4 screens\n");
	} else {
		if (iNES_Header->flags6 & VerticleMirror) {
			printf("Verticle\n");
		} else {
			printf("Horizontal\n");
		}
	}

	printf("\tBattery:\t");
	if (iNES_Header->flags6 & Battery) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}

	printf("\tTrainer:\t");
	if (iNES_Header->flags6 & Trainer) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}

	printf("\tMapper:\t\t%d\n", (iNES_Header->flags6 & 0b11110000) >> 4);

	printf("\tVS Unisystem:\t");
	if (iNES_Header->flags7 & VSUnisystem) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}

	printf("\tPlaychoice-10:\t");
	if (iNES_Header->flags7 & PlayChoice10) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
}

void PrintCPURegs (struct CPU_T *CPU) {
	printf("[+] CPU regs\n");
    printf("\tCPU reg A: \t0x%x\n",CPU->A);
    printf("\tCPU reg X: \t0x%x\n",CPU->X);
    printf("\tCPU reg Y: \t0x%x\n",CPU->Y);
    printf("\tCPU reg PC: \t0x%x\n",CPU->PC);
}
