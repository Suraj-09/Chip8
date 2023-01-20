﻿// Chip8.h : Include file for standard system include files,

#pragma once

#include <cstdint>
#include <fstream>

class Chip8 {
private:
	uint8_t memory[4096];
	uint8_t registers[16];
	uint16_t indexReg;
	uint16_t programCounter;
	uint16_t stack[16];
	uint8_t stackPointer;
	uint8_t delayTimer;
	uint8_t soundTimer;
	uint32_t display[64*32];
	uint8_t keypad[16];
	uint16_t opcode;


	uint16_t get_nnn(uint16_t opcode);
	uint8_t get_msb_n(uint16_t opcode);
	uint8_t get_lsb_n(uint16_t opcode);
	uint8_t get_x(uint16_t opcode);
	uint8_t get_y(uint16_t opcode);
	uint8_t get_kk(uint16_t opcode);



	void allMemory();

	void OP_00E0();
	void OP_00EE();
	void OP_1nnn();
	void OP_2nnn();
	void OP_3xkk();
	void OP_4xkk();
	void OP_5xy0();
	void OP_6xkk();
	void OP_7xkk();
	void OP_8xy0();
	void OP_8xy1();
	void OP_8xy2();
	void OP_8xy3();
	void OP_8xy4();
	void OP_8xy5();
	void OP_8xy6();
	void OP_8xy7();
	void OP_8xyE();
	void OP_9xy0();
	void OP_Annn();
	void OP_Bnnn();
	void OP_Cxkk();
	void OP_Dxyn();
	void OP_Ex9E();
	void OP_ExA1();
	void OP_Fx07();
	void OP_Fx0A();
	void OP_Fx15();
	void OP_Fx18();
	void OP_Fx1E();
	void OP_Fx29();
	void OP_Fx33();
	void OP_Fx55();
	void OP_Fx65();
public:
	Chip8();
	void LoadROM(char const* filename);
	void Cycle();
	bool drawFlag;
	void printDisplay();
};