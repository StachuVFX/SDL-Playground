#include <SDL.h>

/*void drawSquare_old(Uint32* pixels, int width, int height, int squareSize, Uint32 color)
{
	// can be optimized
	for (int i = 0; i < squareSize; i++) {
		int targetHeight = height / 2 - (squareSize/2) + i;
		for (int j = 0; j < squareSize; j++) {
			int targetWidth = width / 2 - (squareSize/2) + j;
			int targetPixel = targetHeight * (width) + targetWidth;
			pixels[targetPixel] = color;
		}
	}
}*/

void drawSquare(Uint32* pixels, int width, int height, int squareSize, int squareX, int squareY, Uint32 color)
{
	// can be optimized
	for (int i = 0; i < squareSize; i++) {
		int targetHeight = squareY - (squareSize / 2) + i;
		// out of bounds safety
		if (targetHeight < 0 || targetHeight > height - 1) {
			continue;
		}
		for (int j = 0; j < squareSize; j++) {
			int targetWidth = squareX - (squareSize / 2) + j;
			// out of bounds safety
			if (targetWidth < 0 || targetWidth > width - 1) {
				continue;
			}
			int targetPixel = targetHeight * (width) + targetWidth;
			pixels[targetPixel] = color;
		}
	}
}
