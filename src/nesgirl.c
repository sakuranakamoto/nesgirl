#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cart.h"
#include "error.h"

int main(int argc, char *argv[]) {
	NES_T NES;
	int option;
	int fflag = 0;
	char *rom_filename;
	static const char *usage = "usage:";
	static const char *start_message = "[+] Started up nesgirl\n\n";

	while ((option = getopt(argc, argv, "f:")) != -1) {
		switch (option) {
		case 'f':
			fflag = 1;
			rom_filename = optarg;
			break;
		default:
			break;
		}
	}

	if (!fflag) {
		printf("%s", usage);
		return FAIL;
	}

	printf("%s", start_message);

	if (LoadROM(rom_filename, &NES)) {
		return FAIL;
	}
	return SUCCESS;
}
