
#include "Display_Helper.h"
#include <stdio.h>
#include <string>
#include <cmath>

Display_Helper::Display_Helper(int windowWidth, int windowHeight) {

	gWindow = NULL;
	gRenderer = NULL;

	//Start up SDL and create window
	if (!init(windowWidth, windowHeight)) {
		printf("Failed to initialize!\n");
	} else {}
}

bool Display_Helper::init(int windowWidth, int windowHeight) {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}
void Display_Helper::Display_Update(uint32_t display[]) {
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	for (int row = 0; row < 32; row++) {
		for (int col = 0; col < 64; col++) {
			uint16_t pos = (row * 64) + col;
			uint32_t pixel = display[pos];
			uint8_t color = (pixel) ? 0xFF : 0x00;

			SDL_Rect fillRect = { col * 10, row * 10, 10, 10 };
			SDL_SetRenderDrawColor(gRenderer, color, color, color, color);
			SDL_RenderFillRect(gRenderer, &fillRect);
		}
	}

	//Update screen
	SDL_RenderPresent(gRenderer);
}

Display_Helper::~Display_Helper() {
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
