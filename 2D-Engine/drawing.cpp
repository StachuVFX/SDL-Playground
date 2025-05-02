#include <SDL.h>

void drawSquare(Uint32* pixels, int width, int height, int squareSize, Uint32 color)
{
	for (int i = 0; i < squareSize; i++) {
		int targetHeight = height / 2 - (squareSize/2) + i;
		for (int j = 0; j < squareSize; j++) {
			int targetWidth = width / 2 - (squareSize/2) + j;
			int targetPixel = targetHeight * (width) + targetWidth;
			pixels[targetPixel] = color;
		}
	}
}
