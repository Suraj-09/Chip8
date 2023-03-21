#include "Chip8.h"
#include "Display_Helper.h"
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <chrono>


int main(int argc, char** argv) {
	Chip8 chip8;
	
	std::string inputRom;
	char const* romFilename;

	std::string inputDelay;
	int delay;

	if (argc != 3) {
		std::cout << "Please enter rom file: ";
		std::cin >> inputRom;
		romFilename = inputRom.c_str();

		std::cout << "Please enter delay (test ms delay of 3 or 4, then asjust): ";
		std::cin >> inputDelay;
		delay = std::stoi(inputDelay);

	} else {
		romFilename = argv[1];
		delay = std::stoi(argv[2]);
	}	 

	chip8.LoadROM(romFilename);
	
	// load display
	Display_Helper display(DISPLAY_WIDTH * 10, DISPLAY_HEIGHT * 10);

	bool quit = false;

	auto oldTime = std::chrono::system_clock::now();

	while (!quit) {
		quit = display.keypadInputs(chip8.keypad);

		auto currentTime = std::chrono::system_clock::now();

		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - oldTime);
		
		auto ms = milliseconds.count();

		if (ms > delay) {
			oldTime = currentTime;
			chip8.Cycle();
			display.Display_Update(chip8.display);
		}
			
	}

	return 0;
}
