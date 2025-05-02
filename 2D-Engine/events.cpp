#include <SDL.h>

bool handleEvents(SDL_Event& event)
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				return false;
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
			return false;
		}
	}
	return true;
}