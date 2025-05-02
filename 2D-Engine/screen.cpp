#include <SDL.h>

enum SurfaceRatio
{
	FIT = 0,
	FILL = 1
};

void fill(Uint32* pixels, int width, int height, Uint32 color)
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i * (width) + j] = color;
		}
	}
}

void scaleSurface(SDL_Surface* surfaceA, SDL_Surface* surfaceB, int ratio)
{
	//SDL_BlitSurface(surfaceA, NULL, surfaceB, NULL);

	SDL_LockSurface(surfaceA);
	SDL_LockSurface(surfaceB);

	Uint32* pixelsA = (Uint32*)(surfaceA->pixels);
	Uint32* pixelsB = (Uint32*)(surfaceB->pixels);

	switch (ratio)
	{
	case FIT:
		bool fitToHeight = true;
		if (surfaceA->w / surfaceB->w > surfaceA->h / surfaceB->h) {
			fitToHeight = false;
		}
		break;
	case FILL:
					// here!
		break;
	default:
		break;
	}

	SDL_UnlockSurface(surfaceA);
	SDL_UnlockSurface(surfaceB);
}
