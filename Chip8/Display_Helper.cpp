
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

bool Display_Helper::keypadInputs(uint8_t* keypad) {
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Handle events on queue
	while (SDL_PollEvent(&e) != 0) {

		//User requests quit
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
			quit = true;
		}
		//User presses a key
		else if (e.type == SDL_KEYDOWN) {
			//Select surfaces based on key press
			switch (e.key.keysym.sym) {
			case SDLK_x:
				keypad[0] = 1;
				break;
			case SDLK_1:
				keypad[1] = 1;
				break;
			case SDLK_2:
				keypad[2] = 1;
				break;
			case SDLK_3:
				keypad[3] = 1;
				break;
			case SDLK_q:
				keypad[4] = 1;
				break;
			case SDLK_w:
				keypad[5] = 1;
				break;
			case SDLK_e:
				keypad[6] = 1;
				break;
			case SDLK_a:
				keypad[7] = 1;
				break;
			case SDLK_s:
				keypad[8] = 1;
				break;
			case SDLK_d:
				keypad[9] = 1;
				break;
			case SDLK_z:
				keypad[0xA] = 1;
				break;
			case SDLK_c:
				keypad[0xB] = 1;
				break;
			case SDLK_4:
				keypad[0xC] = 1;
				break;
			case SDLK_r:
				keypad[0xD] = 1;
				break;
			case SDLK_f:
				keypad[0xE] = 1;
				break;
			case SDLK_v:
				keypad[0xF] = 1;
				break;
			default:
				break;
			}
		} else if (e.type == SDL_KEYUP) {
			//Select surfaces based on key press
			switch (e.key.keysym.sym) {
			case SDLK_x:
				keypad[0] = 0;
				break;
			case SDLK_1:
				keypad[1] = 0;
				break;
			case SDLK_2:
				keypad[2] = 0;
				break;
			case SDLK_3:
				keypad[3] = 0;
				break;
			case SDLK_q:
				keypad[4] = 0;
				break;
			case SDLK_w:
				keypad[5] = 0;
				break;
			case SDLK_e:
				keypad[6] = 0;
				break;
			case SDLK_a:
				keypad[7] = 0;
				break;
			case SDLK_s:
				keypad[8] = 0;
				break;
			case SDLK_d:
				keypad[9] = 0;
				break;
			case SDLK_z:
				keypad[0xA] = 0;
				break;
			case SDLK_c:
				keypad[0xB] = 0;
				break;
			case SDLK_4:
				keypad[0xC] = 0;
				break;
			case SDLK_r:
				keypad[0xD] = 0;
				break;
			case SDLK_f:
				keypad[0xE] = 0;
				break;
			case SDLK_v:
				keypad[0xF] = 0;
				break;
			default:
				break;
			}
		}


	}

	return quit;
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
