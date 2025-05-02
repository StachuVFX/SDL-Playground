#include <iostream>
#include <SDL.h>
#include <thread>
#include <SDL_keycode.h>

/*
   TODO:
	- scale function
   DONE:
	- fill function
	- draw square function
*/

/* Function declarations */
void scaleSurface(SDL_Surface* surfaceA, SDL_Surface* surfaceB, int ratio);

void fill(Uint32* pixels, int width, int height, Uint32 color);

void drawSquare(Uint32* pixels, int width, int height, int squareSize, Uint32 color);

int main(int argc, char* argv[]) {
	/* SDL setup */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Unable to initialize SDL: " << SDL_GetError();
		return 1;
	}
	SDL_Window* window = SDL_CreateWindow("SDL Playground - 2D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
	SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

	/* Game setup */
	SDL_Event event;
	bool running = true;
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(window, &width, &height);
	SDL_Surface* drawingSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA8888);
	Uint32* pixels = (Uint32*)drawingSurface->pixels;

	/* Colors */
	Uint32 black = SDL_MapRGBA(drawingSurface->format, 0, 0, 0, 255);
	Uint32 white = SDL_MapRGBA(drawingSurface->format, 255, 255, 255, 255);
	Uint32 red = SDL_MapRGBA(drawingSurface->format, 255, 0, 0, 255);
	Uint32 green = SDL_MapRGBA(drawingSurface->format, 0, 255, 0, 255);
	Uint32 blue = SDL_MapRGBA(drawingSurface->format, 0, 0, 255, 255);

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
					SDL_GetWindowSize(window, &width, &height);
					SDL_FreeSurface(drawingSurface);
					drawingSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA8888);
					pixels = (Uint32*)drawingSurface->pixels;
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
		//	(if ever draws incorrectly, the reason might be using width instead of pitch / bpp)
		fill(pixels, width, height, blue);
		drawSquare(pixels, width, height, 100, white);

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
