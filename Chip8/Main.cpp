#include "Chip8.h"
#include "Display_Helper.h"
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include <string>


int main(int argc, char** argv) {
	Chip8 chip8;
	Display_Helper display(DISPLAY_WIDTH*10, DISPLAY_HEIGHT * 10);

	
	std::string inputRom;
	char const* romFilename;

	std::string inputDelay;
	int delay;

	if (argc != 3) {
		std::cout << "Please enter rom file: ";
		std::cin >> inputRom;
		romFilename = inputRom.c_str();

		std::cout << "Please enter delay: ";
		std::cin >> inputDelay;
		delay = std::stoi(inputDelay);

	} else {
		romFilename = argv[1];
		delay = std::stoi(argv[2]);
	}	 

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
