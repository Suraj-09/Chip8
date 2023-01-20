// Chip8.cpp : Defines the entry point for the application.
//

#include "Chip8.h"
#include <fstream>
#include <iostream>
#include <typeinfo>

const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;
uint8_t fontset[FONTSET_SIZE] = {
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
	opcode = 0;
	indexReg = 0;
	stackPointer = 0;

	// Clear display
	for (int i = 0; i < 2048; i++) {
		display[i] = 0;
	}

	// Clear stack
	for (int i = 0; i < 16; ++i)
		stack[i] = 0;

	// Clear registers
	for (int i = 0; i < 16; ++i)
		registers[i] = 0;

	// Clear keypad
	for (int i = 0; i < 16; ++i)
		keypad[i] = 0;

	// Clear memory
	for (int i = 0; i < 4096; ++i)
		memory[i] = 0;

	// Load fontset
	for (int i = 0; i < FONTSET_SIZE; ++i) {
		memory[FONTSET_START_ADDRESS + i] = fontset[i];
	}

	// Reset timers
	delayTimer = 0;
	soundTimer = 0;

	// Clear screen once
	drawFlag = true;
}

const unsigned int START_ADDRESS = 0x200;

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
			memory[START_ADDRESS + i] = buffer[i];		
		}

		// Free the buffer
		delete[] buffer;
	}
	else {
		std::cout << "error" << std::endl;
	}
}

void Chip8::Cycle() {
	// Fetch
	opcode = (memory[programCounter] << 8) | memory[programCounter + 1];

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
	case 0x0: {
		uint16_t lsb = get_kk(opcode);

		switch (lsb) {
		case 0xE0:
			OP_00E0();
			break;
		case 0xEE:
			OP_00EE();
			break;
		}
		break;
	}
	case 0x1:
		OP_1nnn();
		break;
	case 0x2:
		OP_2nnn();
		break;
	case 0x3:
		OP_3xkk();
		break;
	case 0x4:
		OP_4xkk();
		break;
	case 0x5:
		OP_5xy0();
		break;
	case 0x6: {
		OP_6xkk();
		break;
	}
	case 0x7: {
		OP_7xkk();
		break;
	}
	case 0x8: {
		uint16_t n = get_lsb_n(opcode);

		switch (n) {
		case 0x0:
			OP_8xy0();
			break;
		case 0x1:
			OP_8xy1();
			break;
		case 0x2:
			OP_8xy2();
			break;
		case 0x3:
			OP_8xy3();
			break;
		case 0x4:
			OP_8xy4();
			break;
		case 0x5:
			OP_8xy5();
			break;
		case 0x6:
			OP_8xy6();
			break;
		case 0x7:
			OP_8xy7();
			break;
		case 0xE:
			OP_8xyE();
			break;
		}
		
		break;
	}
	case 0x9:
		OP_9xy0();
		break;
	case 0xA:
		OP_Annn();
		break;
	case 0xB:
		OP_Bnnn();
		break;
	case 0xC:
		OP_Cxkk();
		break;
	case 0xD: {
		OP_Dxyn();
		break;
	}
	case 0xE: {
		uint16_t lsb = get_kk(opcode);

		switch (lsb) {
		case 0x9E:
			OP_Ex9E();
			break;
		case 0xA1:
			OP_ExA1();
			break;
		}
		break;
	}
	case 0xF: {
		uint16_t lsb = get_kk(opcode);

		switch (lsb) {
		case 0x07:
			OP_Fx07();
			break;
		case 0xA1:
			OP_Fx0A();
			break;
		case 0x15:
			OP_Fx15();
			break;
		case 0x18:
			OP_Fx18();
			break;
		case 0x1E:
			OP_Fx1E();
			break;
		case 0x29:
			OP_Fx29();
			break;
		case 0x33:
			OP_Fx33();
			break;
		case 0x55:
			OP_Fx55();
			break;
		case 0x65:
			OP_Fx65();
			break;
		}
		break;
	}
	default:
		std::cout << "unrecognized opcode";
	}
}

// Clear the display.
void Chip8::OP_00E0(){
	for (int i = 0; i < 2048; ++i)
		display[i] = 0;
	drawFlag = true;
}


void Chip8::OP_00EE(){
	
}

// Jump to location nnn.
void Chip8::OP_1nnn(){
	programCounter = get_nnn(opcode);
}


void Chip8::OP_2nnn(){

}


void Chip8::OP_3xkk(){

}

void Chip8::OP_4xkk(){

}

void Chip8::OP_5xy0(){

}

// 6xkk - LD Vx, byte
void Chip8::OP_6xkk(){
	uint8_t x = get_x(opcode);
	uint8_t kk = get_kk(opcode);
	registers[x] = kk;
}

// 7xkk - ADD Vx, byte
void Chip8::OP_7xkk(){
	uint8_t x = get_x(opcode);
	uint8_t kk = get_kk(opcode);
	registers[x] += kk;
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

// Set I = nnn.
void Chip8::OP_Annn(){
	indexReg = get_nnn(opcode);
}

void Chip8::OP_Bnnn(){

}

void Chip8::OP_Cxkk(){

}

// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
void Chip8::OP_Dxyn() {
	uint8_t x = get_x(opcode);
	uint8_t y = get_y(opcode);
	uint8_t num_bytes = get_lsb_n(opcode);

	uint8_t xPos = registers[x] % 64;
	uint8_t yPos = registers[y] % 32;
	registers[0xF] = 0;

	for (int row = 0; row < num_bytes; row++) {
		uint8_t byte = memory[indexReg + row];

		for (int col = 0; col < 8; col++) {
			uint8_t bit = byte & (0x80 >> col);
			uint16_t position = ((yPos + row) * 64) + (xPos + col);
			uint32_t* displayPixel = &display[position];

			// check if sprite bit is 1
			if (bit) {
				if (*displayPixel) {
					registers[0xF] = 1; // collision
					*displayPixel = 0;
				}
				else {
					*displayPixel = 1;
				}

				/**displayPixel ^= 1;*/
			}
		}
	}

	drawFlag = true;
	//printDisplay();
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
	return (opcode & 0x0FFFu);
}

uint8_t Chip8::get_msb_n(uint16_t opcode) {
	return (uint8_t)((opcode & 0xF000u) >> 12);
}

uint8_t Chip8::get_lsb_n(uint16_t opcode) {
	return (uint8_t)((opcode & 0x000Fu));
}

uint8_t Chip8::get_x(uint16_t opcode) {
	return (uint8_t)((opcode & 0x0F00u) >> 8);
}

uint8_t Chip8::get_y(uint16_t opcode) {
	return (uint8_t)((opcode & 0x00F0u) >> 4);
}

uint8_t Chip8::get_kk(uint16_t opcode) {
	return (uint8_t)(opcode & 0x00FFu);
}


void Chip8::printDisplay() {
	for (int i = 0; i < 66; i++)
		std::cout << (char)254u;
	
	std::cout << std::endl;
	for (int row = 0; row < 32; row++) {
		std::cout << (char)254u;
		for (int col = 0; col < 64; col++) {
			uint16_t pos = (row * 64) + col;
			uint32_t pixel = display[pos];
			char out;

			out = (pixel != 0) ? (char)254u : ' ';

			std::cout << out;

		}
		std::cout << (char)254u << std::endl;
	}

	for (int i = 0; i < 66; i++)
		std::cout << (char)254u;
	std::cout << std::endl;


	drawFlag = false;
}

