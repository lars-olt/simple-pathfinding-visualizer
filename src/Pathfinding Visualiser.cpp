//============================================================================
// Name        : Pathfinding Visualiser.cpp
// Author      : Lars Olt
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <SDL.h>
#include "Screen.h"
#include "NodeGrid.h"
#include "DijkstraAlgorithm.h"
#include "AStarAlgorithm.h"
#include <iostream>

using namespace std;
using namespace lso;

int main() {

	Screen screen;
	NodeGrid nodeGrid(Screen::WINDOW_WIDTH, Screen::WINDOW_HEIGHT);


	screen.init();
	nodeGrid.init();

	// get mouse variables
	int mouseX;
	int mouseY;
	int lastHoveredX = 0;
	int lastHoveredY = 0;
	bool clicked = false;

	// get constants
	int gridBoarder = NodeGrid::GRID_BOARDER;
	int gridPadding = NodeGrid::GRID_PADDING;
	int windowWidth = Screen::WINDOW_WIDTH;
	int windowHeight = Screen::WINDOW_HEIGHT;
	int gridWidth = nodeGrid.m_gridWidth;
	int gridHeight = nodeGrid.m_gridHeight;
	int radius = NodeGrid::CIRCLE_RADIUS;

	// get start/end node
	int startX = -1;
	int startY = -1;
	int endX = -1;
	int endY = -1;

	bool quit = false;
	bool dijkstraRunning;
	bool aStarRunning;

	// define algorithms
	DijkstraAlgorithm dijkstra(nodeGrid, gridWidth, gridHeight, 1);
	AStarAlgorithm aStar(nodeGrid, gridWidth, gridHeight, 1);

	// run loop
	while(!quit) {
		dijkstraRunning = dijkstra.getAlgorithmRunning();
		aStarRunning = aStar.getAlgorithmRunning();

		// check cursor within bounds
		if(!dijkstraRunning && !aStarRunning
				&& mouseX <= (windowWidth - gridBoarder)
				&& mouseX >= gridBoarder
				&& mouseY <= (windowHeight - gridBoarder)
				&& mouseY >= gridBoarder) {

			// scale cursor position to grid
			int scaledX = ((mouseX + radius) - gridBoarder * 2) / gridPadding;
			int scaledY = ((mouseY + radius) - gridBoarder * 2) / gridPadding;

			if(lastHoveredX != mouseX || lastHoveredY != mouseY) {
				nodeGrid.clearCursorCluster(lastHoveredX, lastHoveredY); // reset last hovered
				nodeGrid.setCursorCluster(scaledX, scaledY); // set new hovered

				lastHoveredX = scaledX;
				lastHoveredY = scaledY;
			}

			if(clicked) {
				int pos = (gridWidth * scaledY) + scaledX;

				if(startX == -1) { // start uninitilised
					startX = scaledX;
					startY = scaledY;

					nodeGrid.setStartNode(pos);
					nodeGrid.setDistanceFromStart(pos, 0.0);

					dijkstra.setStart(startX, startY);
					aStar.setStart(startX, startY);

				} else if(!nodeGrid.getIsStartNode(pos) && endX == -1) { // end uninitilised
					endX = scaledX;
					endY = scaledY;

					nodeGrid.setEndNode(pos);

					dijkstra.setEnd(endX, endY);
					aStar.setEnd(endX, endY);

				} else if(!nodeGrid.getIsEndNode(pos) && !nodeGrid.getIsStartNode(pos)) { // start and end initilised => draw barrier
					nodeGrid.setBarrierNode(pos);
				}

			}
		}

		// remove cursor clustor if algorithm running
		if((dijkstraRunning || aStarRunning) && nodeGrid.getIsCursorCenter(lastHoveredX, lastHoveredY)) {
			nodeGrid.clearCursorCluster(lastHoveredX, lastHoveredY);
		}

		// Dijkstra's algorithm
		if(dijkstraRunning) {
			dijkstra.step(); // take step
			dijkstraRunning = dijkstra.getAlgorithmRunning(); // check still running
		}

		// A* algorithm
		if(aStarRunning) {
			aStar.step();
			aStarRunning = aStar.getAlgorithmRunning(); // check still running
		}

		// draw circles
		for(int y = 0; y < gridHeight; y++) {
			for(int x = 0; x < gridWidth; x++) {
				int pos = (gridWidth * y) + x;

				int scaledX = (nodeGrid.getNodeX(pos) + (gridPadding / 2));
				int scaledY = (nodeGrid.getNodeY(pos) + (gridPadding / 2));

				screen.drawCircle(scaledX, scaledY, radius, nodeGrid.getColor(pos));
			}
		}

		screen.update();

		// check screen close
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {

				case SDL_QUIT:
					quit = true; // stop run loop
					break;

				case SDL_MOUSEMOTION:
					mouseX = event.motion.x;
					mouseY = event.motion.y;
					break;

				case SDL_MOUSEBUTTONDOWN:
					clicked = true;
					break;

				case SDL_MOUSEBUTTONUP: clicked = false; break;

				case SDL_KEYDOWN:
					if(!aStarRunning && startX != -1 && endX != -1 && event.key.keysym.sym == SDLK_d && !event.key.repeat) {
						dijkstra.toggleRunning();
					}  else if(!dijkstraRunning && startX != -1 && endX != -1 && event.key.keysym.sym == SDLK_a && !event.key.repeat) {
						aStarRunning = aStar.toggleRunning();
					} else if(event.key.keysym.sym == SDLK_r && !event.key.repeat) {
						// reset algorithms
						dijkstra.setAlgorithmRunning(false);
						dijkstra.setPathFound(false);
						aStar.setAlgorithmRunning(false);
						aStar.setPathFound(false);

						// reset start and end positions
						startX = -1;
						startY = -1;
						endX = -1;
						endY = -1;

						// reset node variables
						nodeGrid.resetGrid();
					}
					break;
			}
		}
	}

	screen.close();
	nodeGrid.close();

	return 0;
}
