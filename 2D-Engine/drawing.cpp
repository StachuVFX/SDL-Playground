#include <SDL.h>

#define SIGN(x) ((x > 0) - (x < 0))

int min(int numbers[], int length);
int max(int numbers[], int length);

struct Point
{
	int x, y;
	Point(int x, int y) : x(x), y(y) {};
};

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

void drawSquare(Uint32* pixels, int surfaceWidth, int surfaceHeight, int squareSize, int squareX, int squareY, Uint32 color)
{
	// can be optimized
	for (int i = 0; i < squareSize; i++) {
		int targetHeight = squareY - (squareSize / 2) + i;
		// out of bounds safety
		if (targetHeight < 0 || targetHeight > surfaceHeight - 1) {
			continue;
		}
		for (int j = 0; j < squareSize; j++) {
			int targetWidth = squareX - (squareSize / 2) + j;
			// out of bounds safety
			if (targetWidth < 0 || targetWidth > surfaceWidth - 1) {
				continue;
			}
			int targetPixel = targetHeight * (surfaceWidth) + targetWidth;
			pixels[targetPixel] = color;
		}
	}
}

void drawLine(Uint32* pixels, int surfaceWidth, int surfaceHeight, Point vertexA, Point vertexB, Uint32 color)
{			// can be optimized for sure
	int width = vertexA.x - vertexB.x;
	int height = vertexA.y - vertexB.y;
	bool widthLonger = abs(width) > abs(height);
	switch (widthLonger)
	{
	case true:
		// V1
		/*for (int i = vertexA.x, j = vertexA.y; i != vertexB.x; i -= SIGN(width), j -= SIGN(height)) {
			int x = i;
			int y = (float)(vertexA.y - (i - vertexA.x));
				//	continue here!
		}*/
		// V2
		for (int i = 0; i < abs(width); i++) {
			float localX = i;
			float localY = (float)(i * ((float)abs(height) / (float)abs(width)));
			float globalX = vertexA.x - localX * SIGN(width);
			// out of bounds safety
			if (globalX < 0 || globalX > surfaceWidth - 1) {
				continue;
			}
			float globalY = vertexA.y - localY * SIGN(height);
			// out of bounds safety
			if (globalY < 0 || globalY > surfaceHeight - 1) {
				continue;
			}
			int targetPixel = (int)globalY * surfaceWidth + (int)globalX;
			pixels[targetPixel] = color;
		}
		break;
	case false:
		for (int i = 0; i < abs(height); i++) {
			float localY = i;
			float localX = (float)(i * ((float)abs(width) / (float)abs(height)));
			float globalY = vertexA.y - localY * SIGN(height);
			// out of bounds safety
			if (globalY < 0 || globalY > surfaceHeight - 1) {
				continue;
			}
			float globalX = vertexA.x - localX * SIGN(width);
			// out of bounds safety
			if (globalX < 0 || globalX > surfaceWidth - 1) {
				continue;
			}
			int targetPixel = (int)globalY * surfaceWidth + (int)globalX;
			pixels[targetPixel] = color;
		}
		break;
	default:
		break;
	}
}

void drawTriangle(Uint32* pixels, int surfaceWidth, int surfaceHeight, Point vertexA, Point vertexB, Point vertexC, Uint32 color, int version)
{
		int width = vertexB.x - vertexC.x;
		int height = vertexB.y - vertexC.y;
		bool widthLonger = abs(width) > abs(height);
	switch (version)
	{
	// V1 - lines from one vertex (mid efficiency, has artifacts)
	case 1:
		switch (widthLonger)
		{
		case true:
			for (int i = 0; i < abs(width); i++) {
				float localX = i;
				float localY = (float)(i * ((float)abs(height) / (float)abs(width)));
				float globalX = vertexB.x - localX * SIGN(width);
				// out of bounds safety
				/*if (globalX < 0 || globalX > surfaceWidth - 1) {
					continue;
				}*/
				float globalY = vertexC.y - localY * SIGN(height);
				// out of bounds safety
				/*if (globalY < 0 || globalY > surfaceHeight - 1) {
					continue;
				}*/
				//int targetPixel = (int)globalY * surfaceWidth + (int)globalX;
				Point targetPoint((int)globalX, (int)globalY);
				//pixels[targetPixel] = color;
				drawLine(pixels, surfaceWidth, surfaceHeight, targetPoint, vertexA, color);
			}
			break;
		case false:
			for (int i = 0; i < abs(height); i++) {
				float localY = i;
				float localX = (float)(i * ((float)abs(width) / (float)abs(height)));
				float globalY = vertexB.y - localY * SIGN(height);
				// out of bounds safety
				/*if (globalY < 0 || globalY > surfaceHeight - 1) {
					continue;
				}*/
				float globalX = vertexB.x - localX * SIGN(width);
				// out of bounds safety
				/*if (globalX < 0 || globalX > surfaceWidth - 1) {
					continue;
				}*/
				//int targetPixel = (int)globalY * surfaceWidth + (int)globalX;
				Point targetPoint((int)globalX, (int)globalY);
				//pixels[targetPixel] = color;
				drawLine(pixels, surfaceWidth, surfaceHeight, targetPoint, vertexA, color);
			}
			break;
		default:
			break;
		}
		break;
	// V2 - lines from the center (least efficeint)
	case 2:
		break;
	// V3 - parallel lines starting between two vertices (high efficiency)
	case 3:
		break;
	// V4 - parallel horizontal lines (most efficient)
	case 4:
					// here!
		/*int yArray[3] = { vertexA.y, vertexB.y, vertexC.y };
		int xArray[3] = { vertexA.x, vertexB.x, vertexC.x };
		int top = min(yArray, 3);
		int bottom = max(yArray, 3);
		int left = min(xArray, 3);
		int right = max(xArray, 3);*/

		break;
	default:
		break;
	}
}
