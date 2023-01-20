#include "Chip8.h"

int main(int argc, char** argv) {
	
	Chip8 chip8;

	char const* romFilename = "C:\\code\\cpp\\Chip8\\Chip8\\tests\\chip8-test-rom-master\\test_opcode.ch8";

	chip8.LoadROM(romFilename);

	return 0;
}