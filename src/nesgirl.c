#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cart.h"
#include "error.h"
#include "memory.h"

int main(int argc, char *argv[]) {
	struct NES_T NES;
	int option;
	int fflag = 0;
	char *rom_filename;
	static const char *usage = "usage:";
	static const char *start_message = "[+] Started up nesgirl >..<\n";

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
		return Fail;
	}

	printf("%s", start_message);

	if (InitMem(&NES)) {
		return Fail;
	}

	if (LoadROM(rom_filename, &NES)) {
		FreeMem(NES.mem);
		return Fail;
	}

	FreeMem(NES.mem);
	return Success;
}
