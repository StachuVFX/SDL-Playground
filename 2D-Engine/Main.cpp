#include <iostream>
#include <SDL.h>
#include <thread>
#include <SDL_keycode.h>

/* TODO:
	- use Uint32 for pixels and SDL_MapRGBA for colors
*/

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
	SDL_Surface* drawingSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_ABGR8888);   /* ABGR bc it's in reverse lol */
	uint8_t* pixels = static_cast<uint8_t*>(drawingSurface->pixels);

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
					drawingSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA8888);   /* And now look it will change color lol */
					pixels = static_cast<uint8_t*>(drawingSurface->pixels);
				}
			}
			else if (event.type == SDL_QUIT) {   /* Stop game loop if window was quited */
				running = false;
			}
		}

		/* Drawing */
		SDL_LockSurface(drawingSurface);
		pixels = static_cast<uint8_t*>(drawingSurface->pixels);
		for (int i = 0; i < 100; i++) {
			int targetHeight = height / 2 - 50 + i;
			for (int j = 0; j < 100; j++) {
				int targetWidth = width / 2 - 50 + j;
				int targetPixel = targetHeight * drawingSurface->pitch + targetWidth * 4;
				for (int k = 0; k < 4; k++)
				{
					pixels[targetPixel + 0] = (uint8_t)255;   /* Why tf is it ABGR not RGBA */
					pixels[targetPixel + 1] = (uint8_t)255;   /* It's bc SDL is writing pixels as Uint32 (full 4 bytes) and they're endian in memory */
					pixels[targetPixel + 2] = (uint8_t)0;
					pixels[targetPixel + 3] = (uint8_t)255;
				}
			}
		}
		SDL_UnlockSurface(drawingSurface);

		/* Swapping buffers */
		SDL_BlitSurface(drawingSurface, NULL, windowSurface, NULL);
		SDL_UpdateWindowSurface(window);
	}

	/* Cleaning */
	SDL_FreeSurface(drawingSurface);
	SDL_FreeSurface(windowSurface);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
