#include "Chip8.h"
#include <iostream>
#include <stdlib.h>
#include <filesystem>
namespace fs = std::filesystem;
int main(int argc, char** argv) {


	
	Chip8 chip8;
	// C:\code\cpp\Chip8\Chip8\tests\Tetris.ch8
	// C:\code\cpp\Chip8\Chip8\Main.cpp
	//char const* romFilename = "C:\\code\\cpp\\Chip8\\Chip8\\tests\\chip8-test-rom-master\\test_opcode.ch8";
	//char const* romFilename = "C:\\Users\\suraj\\source\\repos\\Chip8\\tests\\chip8-test-rom-master\\test_opcode.ch8";
	//char const* romFilename = "C:/Users/suraj/source/repos/Chip8/Chip8/tests/chip8-test-rom-master/test_opcode.ch8";
	//char const* romFilename = "C:/Users/suraj/source/repos/Chip8/Chip8/tests/tetris.ch8";
	//std::string romFilename = "C:\\Users\\suraj\\source\\repos\\Chip8\\Chip8\\tests\\test_opcode.ch8";
	
	//char const* romFilename = "./tests/tetris.ch8";
	char const* romFilename = "C:/code/cpp/Chip8/Chip8/tests/Tetris.ch8";

	//char full[_MAX_PATH];
	//if (_fullpath(full, romFilename, _MAX_PATH) != NULL)
	//	printf("Full path is: %s\n", full);

	//std::cout << "Current path is " << fs::current_path() << '\n'; // (1)
	//fs::current_path(fs::temp_directory_path()); // (3)
	//std::cout << "Current path is " << fs::current_path() << '\n';


	chip8.LoadROM(romFilename);
	////chip8.load_rom(romFilename);
	////std::cout << "hello final";


	for (int i = 0; i < 50; i++) {
		chip8.Cycle();
		std::cout << "------\n";
	}
	
	/*chip8.Cycle();
	chip8.Cycle();
	chip8.Cycle();
	chip8.Cycle();*/
	//chip8.allMemory();

	return 0;
}