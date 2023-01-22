#include "Chip8.h"
#include "Display_Helper.h"
#include <iostream>
#include <stdlib.h>

int main(int argc, char** argv) {
	Chip8 chip8;
	Display_Helper display(DISPLAY_WIDTH*10, DISPLAY_HEIGHT * 10);

	char const* romFilename = argv[1];

	chip8.LoadROM(romFilename);

	for (int i = 0; i < 20; i++) {
		chip8.Cycle();
	}

	while (true) {
		chip8.Cycle();
		if (chip8.drawFlag)
			/*chip8.printDisplay();*/
			display.Display_Update(chip8.display);

		chip8.pollKeys();
	}

	return 0;
}