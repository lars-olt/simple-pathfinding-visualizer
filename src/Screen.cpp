/*
 * Screen.cpp
 *
 *  Created on: Jan 11, 2022
 *      Author: larsolt
 */

#include "Screen.h"

namespace lso {
Screen::Screen(): m_pWindow(NULL), m_pRenderer(NULL), m_pTexture(NULL), m_pBuffer(NULL) {
	// TODO Auto-generated constructor stub

}

bool Screen::init() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	m_pWindow = SDL_CreateWindow("Pathfinding Visualiser",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	if(m_pWindow == NULL) {
		SDL_Quit();
		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow,
			-1, SDL_RENDERER_PRESENTVSYNC);

	m_pTexture = SDL_CreateTexture(m_pRenderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WINDOW_WIDTH, WINDOW_HEIGHT);

	if(m_pRenderer == NULL) {
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		return false;
	}

	if(m_pTexture == NULL) {
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
		return false;
	}

	m_pBuffer = new Uint32[WINDOW_WIDTH*WINDOW_HEIGHT];

	return true;
}

void Screen::update() {
	// update texture and renderer based off of buffer
	SDL_UpdateTexture(m_pTexture, NULL, m_pBuffer, WINDOW_WIDTH*sizeof(Uint32));
	SDL_RenderClear(m_pRenderer);
	SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, NULL);
	SDL_RenderPresent(m_pRenderer);
}

void Screen::drawCircle(int centerX, int centerY, int radius, Uint32 color) {
	int addX = radius - 1;
	int addY = 0;
	int changeX = 1;
	int changeY = 1;
	int diameter = radius * 2;
	int error = (changeX - diameter);

	while(addX >= addY) {

		drawHorizontalLine((centerX - addX), (centerX + addX), (centerY - addY), color); // Octant 3 to 0
		drawHorizontalLine((centerX - addY), (centerX + addY), (centerY - addX), color); // Octant 2 to 1
		drawHorizontalLine((centerX - addX), (centerX + addX), (centerY + addY), color); // octant 4 to 7
		drawHorizontalLine((centerX - addY), (centerX + addY), (centerY + addX), color); // octant 5 to 6

		if(error <= 0) {
			// pixel less or equal to radius from circle center
			++addY;
			error += changeY;
			changeY += 2;
		}

		if(error > 0) {
			// pixel greater than radius from circle center
			--addX;
			changeX += 2;
			error += (changeX - diameter);
		}
	}
}

void Screen::drawHorizontalLine(int x1, int x2, int y, Uint32 color) {
	if(x1 < x2) {
		for(int x = x1; x < x2; x++) {
			setPixel(x, y, color);
		}
	}
}

void Screen::setPixel(int x, int y, Uint32 color) {
	if(checkBounds(x, y)) {
		// assign color value to buffer at (x, y)
		m_pBuffer[(WINDOW_WIDTH*y) + x] = color;
	}
}

bool const Screen::checkBounds(int x, int y) {
	// check (x, y) within window
	if(x<0 || x >= WINDOW_WIDTH || y<0 || y >= WINDOW_HEIGHT) {
		return false;
	}
	return true;
}

Uint32 Screen::getColor(Uint8 red, Uint8 green, Uint8 blue) {
	Uint32 color = 0;

	// append rgb values
	color += red;
	color <<= 8;

	color += green;
	color <<= 8;

	color += blue;
	color <<= 8;

	color += 0xFF; // add alpha values

	return color;
}

void Screen::close() {
	// de-alocate memory
	delete [] m_pBuffer;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyTexture(m_pTexture);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

Screen::~Screen() {
	// TODO Auto-generated destructor stub
}

} // namespace lso
