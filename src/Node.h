/*
 * Node.h
 *
 *  Created on: Jan 13, 2022
 *      Author: larsolt
 */

#ifndef NODE_H_
#define NODE_H_

#include <SDL.h>
#include <limits.h>

namespace lso {

struct Node {
static const Uint32 NORMAL_NODE_COLOR = 0x262626FF; // grey
static const Uint32 BARRIER_COLOR = 0x0396A6FF; // light blue
static const Uint32 CURSOR_OUTSIDE_COLOR = 0x332E33FF; // light grey
static const Uint32 START_AND_END_COLOR = 0x0583F2FF; // very light blue
static const Uint32 VISITED_COLOR = 0x025373FF; // blue
static const Uint32 PATH_COLOR = 0x89D973FF; // green

int m_x;
int m_y;

float m_distanceFromStart;
float m_calculatedDistanceToEnd;
bool m_isStart;
bool m_isEnd;
bool m_isBarrier;
bool m_isPath;
bool m_unvisited;
bool m_isCursorSurrounding;
bool m_isCursorCenter;

public:
	Node();
	void setPos(int x, int y);
	void resetVariables();

	virtual ~Node();

};

} /* namespace lso */

#endif /* NODE_H_ */
