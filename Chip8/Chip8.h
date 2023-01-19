// Chip8.h : Include file for standard system include files,

#pragma once

#include <cstdint>

class Chip8 {
public:
	uint8_t memory[4096];
	uint8_t registers[16];
	uint16_t indexReg;
	uint16_t programCounter;
	uint16_t stack[16];
	uint8_t stackPointer;
	uint8_t delayTimer;
	uint8_t soundTimer;
	uint32_t display[64];
	uint8_t keypad[16];
	uint16_t opcode;
	
	Chip8();
	void LoadROM(char const* filename);

};