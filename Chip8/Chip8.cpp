// Chip8.cpp : Defines the entry point for the application.
//

#include "Chip8.h"
#include <fstream>
#include <iostream>
#include <typeinfo>


uint8_t font[80] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8() {
	programCounter = 0x200;
}

const unsigned int START_ADDRESS = 0x200;

void u_char_to_bin(unsigned char letter) {
	int binary[8];
	for (int n = 0; n < 8; n++)
		binary[7 - n] = (letter >> n) & 1;
	/* print result */
	for (int n = 0; n < 8; n++)
		printf("%d", binary[n]);
	printf("\n");
}

void Chip8::LoadROM(char const* filename)
{
	// Open the file as a stream of binary and move the file pointer to the end
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		// Get size of file and allocate a buffer to hold the contents
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		// Go back to the beginning of the file and fill the buffer
		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		// Load the ROM contents into the Chip8's memory, starting at 0x200
		for (long i = 0; i < size; ++i)
		{
			
			memory[START_ADDRESS + i] = buffer[i];
			//std::cout << memory[START_ADDRESS + i] << std::endl;
			std::cout << START_ADDRESS + i << " : ";
			u_char_to_bin(memory[START_ADDRESS + i]);
			
		}

		// std::cout << typeid(memory[START_ADDRESS + 1]).name() << std::endl;
		//u_char_to_bin(memory[START_ADDRESS + 1]);

		// Free the buffer
		delete[] buffer;
	}
}