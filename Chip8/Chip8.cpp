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

void decToBinary(int n) {
	// array to store binary number
	int binaryNum[32];

	// counter for binary array
	int i = 0;
	while (n > 0) {

		// storing remainder in binary array
		binaryNum[i] = n % 2;
		n = n / 2;
		i++;
	}

	// printing binary array in reverse order
	for (int j = i - 1; j >= 0; j--)
		std::cout << binaryNum[j];
}

void Chip8::LoadROM(char const* filename) {
	// Open the file as a stream of binary and move the file pointer to the end
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open())	{
		// Get size of file and allocate a buffer to hold the contents
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		// Go back to the beginning of the file and fill the buffer
		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		// Load the ROM contents into the Chip8's memory, starting at 0x200
		for (long i = 0; i < size; ++i) {
			//std::cout << i << " ";
			
			memory[START_ADDRESS + i] = buffer[i];

			//std::cout << memory[START_ADDRESS + i] << std::endl;
			//std::cout << START_ADDRESS + i << " : ";
			//u_char_to_bin(memory[START_ADDRESS + i]);
			
		}

		// std::cout << typeid(memory[START_ADDRESS + 1]).name() << std::endl;
		//u_char_to_bin(memory[START_ADDRESS + 1]);

		// Free the buffer
		delete[] buffer;
	}
	else {
		std::cout << "error" << std::endl;
	}
}

void Chip8::Cycle() {
	// Fetch
	opcode = (memory[programCounter] << 8u) | memory[programCounter + 1];

	//std::cout << programCounter << " " << std::hex << opcode << std::dec << std::endl;
	//decToBinary(opcode);
	//std::cout << "\n";
	// Increment the PC before we execute anything
	programCounter += 2;

	// Decrement the delay timer if it's been set
	if (delayTimer > 0) {
		--delayTimer;
	}

	// Decrement the sound timer if it's been set
	if (soundTimer > 0) {
		--soundTimer;
	}
	uint16_t msb = get_msb_n(opcode);

	switch (msb) {
	case 0x0:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0x1:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0x2:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0x3:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0x4:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0x5:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0x6:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0x7:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0x8:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0x9:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0xA:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0xB:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0xC:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0xD:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0xE:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	case 0xF:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
		break;
	default:
		std::cout << "0x0 " << std::hex << opcode << std::endl;
	}
	//std::cout << std::hex << get_msb_n(opcode) << " " << get_nnn(opcode) << std::dec << std::endl;
	//std::cout << programCounter << " " << std::hex << opcode << " " << get_msb_n(opcode) << std::dec << std::endl;
	std::cout << (programCounter-2) << " " << std::hex << opcode << " " << msb << std::dec << std::endl;

	// Decode and Execute
	//((*this).*(table[(opcode & 0xF000u) >> 12u]))();
	//std::cout << programCounter << " " << opcode << std::endl;
}

void Chip8::allMemory() {
	for (int i = 0; i < 4096; i++) {
		std::cout << i << " " << memory[i] << std::endl;
	}
}

void Chip8::OP_00E0(){

}

void Chip8::OP_00EE(){

}

void Chip8::OP_1nnn(){

}

void Chip8::OP_2nnn(){

}

void Chip8::OP_3xkk(){

}

void Chip8::OP_4xkk(){

}

void Chip8::OP_5xy0(){

}

void Chip8::OP_6xkk(){

}

void Chip8::OP_7xkk(){

}

void Chip8::OP_8xy0(){

}

void Chip8::OP_8xy1(){

}

void Chip8::OP_8xy2(){

}

void Chip8::OP_8xy3(){

}

void Chip8::OP_8xy4(){

}

void Chip8::OP_8xy5(){

}

void Chip8::OP_8xy6(){

}

void Chip8::OP_8xy7(){

}

void Chip8::OP_8xyE(){

}

void Chip8::OP_9xy0(){

}

void Chip8::OP_Annn(){

}

void Chip8::OP_8nnn(){

}

void Chip8::OP_Cxkk(){

}

void Chip8::OP_Dxyn(){

}

void Chip8::OP_Ex9E(){

}

void Chip8::OP_ExA1(){

}

void Chip8::OP_Fx07(){

}

void Chip8::OP_Fx0A(){

}

void Chip8::OP_Fx15(){

}

void Chip8::OP_Fx18(){

}

void Chip8::OP_Fx1E(){

}

void Chip8::OP_Fx29(){

}

void Chip8::OP_Fx33(){

}

void Chip8::OP_Fx55(){

}

void Chip8::OP_Fx65(){

}




uint16_t Chip8::get_nnn(uint16_t opcode) {
	return (opcode & 0x0FFF);
}

uint16_t Chip8::get_msb_n(uint16_t opcode) {
	return ((opcode & 0xF000) >> 12);
	//return (opcode >> 12);
}

uint16_t Chip8::get_x(uint16_t opcode) {
	return ((opcode & 0x0F00) >> 8);
}

uint16_t Chip8::get_y(uint16_t opcode) {
	return ((opcode & 0x00F0) >> 4);
}

uint16_t Chip8::get_kk(uint16_t opcode) {
	return (opcode & 0x00FF);
}
