#include <iostream>
#include <SDL.h>
#include <thread>
#include <SDL_keycode.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define DRAW_WIDTH 800
#define DRAW_HEIGHT 600

/*
   TODO:
	- draw line function
	- draw triangle function
	- disable High DPI scaling (screen surface is 1536x864 not 1920x1080)
	- optimize scaleSurface() function
   DONE:
	- draw square function with position
	- draw out of bounds safety
*/

/* Function declarations */
void scaleSurface(SDL_Surface* source, SDL_Surface* destination, int ratio);

void fill(Uint32* pixels, int width, int height, Uint32 color);

//void drawSquare_old(Uint32* pixels, int width, int height, int squareSize, Uint32 color);
void drawSquare(Uint32* pixels, int width, int height, int squareSize, int squareX, int squareY, Uint32 color);

/* Main function */
int main(int argc, char* argv[]) {
	/* SDL setup */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Unable to initialize SDL: " << SDL_GetError();
		return 1;
	}
	SDL_Window* window = SDL_CreateWindow("SDL Playground - 2D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

	/* Game setup */
	SDL_Event event;
	bool running = true;
	int screen_width = 0;
	int screen_height = 0;
	int draw_width = DRAW_WIDTH;
	int draw_height = DRAW_HEIGHT;
	SDL_GetWindowSize(window, &screen_width, &screen_height);
	SDL_Surface* drawingSurface = SDL_CreateRGBSurfaceWithFormat(0, draw_width, draw_height, 32, SDL_PIXELFORMAT_ARGB8888);   // not RGBA bc windowSurface is in ARGB
	Uint32* pixels = (Uint32*)drawingSurface->pixels;

	/* Colors */
	Uint32 black = SDL_MapRGB(drawingSurface->format, 0, 0, 0);
	Uint32 white = SDL_MapRGB(drawingSurface->format, 255, 255, 255);
	Uint32 red = SDL_MapRGB(drawingSurface->format, 255, 0, 0);
	Uint32 green = SDL_MapRGB(drawingSurface->format, 0, 255, 0);
	Uint32 blue = SDL_MapRGB(drawingSurface->format, 0, 0, 255);

	/* Game loop */
	while (running) {
		/* Sleep in case of memory leaks lol */
		std::this_thread::sleep_for(std::chrono::seconds(1));

		/* Event handling */
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					running = false;
				}
			}
			else if (event.type == SDL_WINDOWEVENT) {   /* Set windowSurface again if window was resized */
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					windowSurface = SDL_GetWindowSurface(window);
					SDL_GetWindowSize(window, &screen_width, &screen_height);
					/*SDL_FreeSurface(drawingSurface);
					drawingSurface = SDL_CreateRGBSurfaceWithFormat(0, screen_width, screen_height, 32, SDL_PIXELFORMAT_RGBA8888);
					pixels = (Uint32*)drawingSurface->pixels;*/
				}
			}
			else if (event.type == SDL_QUIT) {   /* Stop game loop if window was quited */
				running = false;
			}
		}

		/* Drawing start */
		SDL_LockSurface(drawingSurface);
		pixels = (Uint32*)(drawingSurface->pixels);
		
		// Drawing functions
		//	(if ever draws incorrectly, the reason might be using width instead of pitch)
		fill(pixels, draw_width, draw_height, blue);
		//drawSquare_old(pixels, draw_width, draw_height, 100, red);
		drawSquare(pixels, draw_width, draw_height, 200, 400, 300, white);

		SDL_UnlockSurface(drawingSurface);
		/* Drawing end */

		/* Swapping buffers */
		scaleSurface(drawingSurface, windowSurface, 0);
		SDL_UpdateWindowSurface(window);
	}

	/* Cleaning */
	SDL_FreeSurface(drawingSurface);
	SDL_FreeSurface(windowSurface);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
