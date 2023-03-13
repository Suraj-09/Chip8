#include "Chip8.h"
#include "Display_Helper.h"
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>


int main(int argc, char** argv) {
	Chip8 chip8;
	Display_Helper display(DISPLAY_WIDTH*10, DISPLAY_HEIGHT * 10);


	char const* romFilename;
	std::string inputPath;

	std::cout << "Please enter path: ";
	std::cin >> inputPath;

	//std::ifstream test(inputPath);
	//while(!test) {
	//	std::cout << "Invalid path! Please enter path again: ";
	//	std::cin >> inputPath;
	//}

	std::cout << inputPath << std::endl;
	romFilename = inputPath.c_str();


	//std::cout << "Please enter path to .ch8 file. Choose method below " << std::endl;
	//boolean validOption = false;
	//std::string option = "";

	//while (!validOption) {
	//	std::cout << "Please enter path to .ch8 file. Choose method below " << std::endl;
	//	std::cout << "[1] Enter complete file path in command line." << std::endl;
	//	std::cout << "[2] Open file directory to open file" << std::endl;
	//	std::cout << "Please enter 1 or 2 to select the option: ";
	//	std::cin >> option;

	//	if (option == "1" || option == "2") {
	//		validOption = true;
	//	}

	//}

	//if (option == "1") {
	//	std::cout << "Please enter path: ";

	//}

	//ShellExecuteA(NULL, "open", "C:\\", NULL, NULL, SW_SHOWDEFAULT);

	//std::cout << "Current path is " << fs::current_path() << '\n'; // (1)

	//const std::filesystem::path correct_path = std::filesystem::u8path("C:/code/cpp/Chip8/Chip8/tests/Tetris.ch8");
	//const std::filesystem::path correct_path = std::filesystem::u8path("C:\\code\\cpp\\Chip8\\Chip8\\tests\\Tetris.ch8");

	//std::cout << correct_path << std::endl;
	// 
	//std::cout << "Current path is " << ${ SolutionDir } << '\n'; // (1)

	/*C:\code\cpp\Chip8\Chip8\tests\Tetris.ch8*/
	//fs::current_path(fs::temp_directory_path()); // (3)
	//std::cout << "Current path is " << fs::current_path() << '\n';

	//char const* romFilename = argv[1];
	//char const* romFilename = "C:/Users/suraj/source/repos/Chip8/Chip8/tests/IBM Logo.ch8";
	// 
	//char const* romFilename = "C:/Users/suraj/source/repos/Chip8/Chip8/tests/Tetris.ch8";

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
