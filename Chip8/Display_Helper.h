#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Display_Helper {
private:
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	bool init(int windowWidth, int windowHeight);

public:
	Display_Helper(int windowWidth, int windowHeight);
	void Display_Update(uint32_t display[]);
	bool keypadInputs(uint8_t keypad[]);
	~Display_Helper();

};