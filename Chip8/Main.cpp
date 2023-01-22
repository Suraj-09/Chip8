#include "Chip8.h"
#include "Display_Helper.h"
#include <iostream>
#include <stdlib.h>

int main(int argc, char** argv) {
	Chip8 chip8;
	Display_Helper display(DISPLAY_WIDTH*10, DISPLAY_HEIGHT * 10);

	//char const* romFilename = argv[1];
	//char const* romFilename = "C:/Users/suraj/source/repos/Chip8/Chip8/tests/IBM Logo.ch8";
	char const* romFilename = "C:/Users/suraj/source/repos/Chip8/Chip8/tests/Tetris.ch8";

	chip8.LoadROM(romFilename);

	bool quit = false;

	while (!quit) {
		quit = display.keypadInputs(chip8.keypad);

		chip8.Cycle();

		if (chip8.drawFlag)
			//chip8.printDisplay();
			display.Display_Update(chip8.display);
	}

	return 0;
}