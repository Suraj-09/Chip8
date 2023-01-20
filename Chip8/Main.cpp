#include "Chip8.h"
#include <iostream>

int main(int argc, char** argv) {
	
	Chip8 chip8;

	//char const* romFilename = "C:\\code\\cpp\\Chip8\\Chip8\\tests\\chip8-test-rom-master\\test_opcode.ch8";
	//char const* romFilename = "C:\\Users\\suraj\\source\\repos\\Chip8\\tests\\chip8-test-rom-master\\test_opcode.ch8";
	//char const* romFilename = "C:/Users/suraj/source/repos/Chip8/Chip8/tests/chip8-test-rom-master/test_opcode.ch8";
	char const* romFilename = "C:/Users/suraj/source/repos/Chip8/Chip8/tests/tetris.ch8";
	//std::string romFilename = "C:\\Users\\suraj\\source\\repos\\Chip8\\Chip8\\tests\\test_opcode.ch8";

	chip8.LoadROM(romFilename);
	//chip8.load_rom(romFilename);
	//std::cout << "hello final";


	for (int i = 0; i < 50; i++) {
		chip8.Cycle();
	}
	
	chip8.Cycle();/*
	chip8.Cycle();
	chip8.Cycle();
	chip8.Cycle();*/
	//chip8.allMemory();

	return 0;
}