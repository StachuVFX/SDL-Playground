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

//void scaleSurface_old(SDL_Surface* source, SDL_Surface* destination, int ratio)
//{
//	SDL_BlitSurface(source, NULL, destination, NULL);
//}

void scaleSurface(SDL_Surface* source, SDL_Surface* destination, int ratio)
{
	SDL_LockSurface(source);
	SDL_LockSurface(destination);

	Uint32* sourcePixels = (Uint32*)source->pixels;
	Uint32* destinationPixels = (Uint32*)destination->pixels;

	bool fitToHeight = true;
	float sh = (float)source->h;
	float dh = (float)destination->h;
	float sw = (float)source->w;
	float dw = (float)destination->w;
	float hScale = (float)source->h / (float)destination->h;
	float wScale = (float)source->w / (float)destination->w;
	switch (ratio)
	{
	case FIT:
		if (wScale > hScale) {
			fitToHeight = false;
		}
				// probably can be optimized
		switch (fitToHeight)
		{
		case true:
			for (int i = 0; i < destination->h; i++) {
				for (int j = 0; j < destination->w * (wScale / hScale); j++) {
					int targetH = i * hScale;
					int wShift = (1 - (wScale / hScale)) * destination->w / 2;
					int targetW = j * hScale;
					destinationPixels[i * destination->w + j + wShift] = sourcePixels[targetH * source->w + targetW];
				}
			}
			break;
		case false:
			for (int i = 0; i < destination->h * (hScale / wScale); i++) {
				for (int j = 0; j < destination->w; j++) {
					int targetH = i * wScale;
					int hShift = (1 - (hScale / wScale)) * destination->h / 2;
					int targetW = j * wScale;
					destinationPixels[(i + hShift) * destination->w + j] = sourcePixels[targetH * source->w + targetW];
				}
			}
			break;
		default:
			break;
		}
		break;
	case FILL:
					// can be optimized
		for (int  i = 0; i < destination->h; i++) {
			for (int j = 0; j < destination->w; j++) {
				float hScale = (float)source->h / (float)destination->h;
				float wScale = (float)source->w / (float)destination->w;
				int targetH = i * hScale;
				int targetW = j * wScale;
				destinationPixels[i * destination->w + j] = sourcePixels[targetH * source->w + targetW];
			}
		}
		break;
	default:
		break;
	}

	SDL_UnlockSurface(source);
	SDL_UnlockSurface(destination);
}
