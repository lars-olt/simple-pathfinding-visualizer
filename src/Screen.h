/*
 * Screen.h
 *
 *  Created on: Jan 11, 2022
 *      Author: larsolt
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

namespace lso {

struct Screen {
	const static int WINDOW_WIDTH = 800;
	const static int WINDOW_HEIGHT = 800;

private:
	SDL_Window *m_pWindow;
	SDL_Renderer *m_pRenderer;
	SDL_Texture *m_pTexture;

	Uint32 *m_pBuffer;

private:
	const bool checkBounds(int x, int y);

public:
	Screen();
	bool init();
	void update();
	void drawCircle(int centerX, int centerY, int radius, Uint32 color);
	void drawHorizontalLine(int x1, int x2, int y, Uint32 color);
	void setPixel(int x, int y, Uint32 color);
	Uint32 static getColor(Uint8 red, Uint8 green, Uint8 blue);
	bool const checkBounds();
	void close();
	virtual ~Screen();
};

} // namespace lso

#endif /* SCREEN_H_ */
