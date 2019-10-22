#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cart.h"
#include "error.h"
#include "memory.h"

int main(int argc, char *argv[]) {

	enum flags {
		Unset,
		Set
	};

	struct NES_T NES;
	int option;
	int f_flag = Unset;
	char *rom_filename;
	static const char *usage = "usage:";
	static const char *start_message = "[+] Started up nesgirl >..<\n";

	while ((option = getopt(argc, argv, "f:")) != Fail) {
		switch (option) {
		case 'f':
			f_flag = Set;
			rom_filename = optarg;
			break;
		default:
			break;
		}
	}

	if (f_flag == Unset) {
		printf("%s", usage);
		return Fail;
	}

	printf("%s", start_message);

	if (InitMem(&NES) == Fail) {
		return Fail;
	}

	printf("[+] Successfully allocated 0x%x of mem\n",MemSize);

	if (LoadROM(rom_filename, &NES) == Fail) {
		FreeMem(NES.mem);
		return Fail;
	}

	FreeMem(NES.mem);
	return Success;
}
