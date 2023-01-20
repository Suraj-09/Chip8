#include "Chip8.h"
#include <iostream>
#include <stdlib.h>

int main(int argc, char** argv) {
	Chip8 chip8;

	char const* romFilename = argv[1];

	chip8.LoadROM(romFilename);

	for (int i = 0; i < 20; i++) {
		chip8.Cycle();
	}

	while (true) {
		chip8.Cycle();
		if (chip8.drawFlag)
			chip8.printDisplay();
	}

	return 0;
}