/*
 * Node.cpp
 *
 *  Created on: Jan 13, 2022
 *      Author: larsolt
 */

#include "Node.h"

namespace lso {

Node::Node(): m_x(-1), m_y(-1), m_distanceFromStart(std::numeric_limits<float>::max()), m_calculatedDistanceToEnd(std::numeric_limits<float>::max()),
		m_isStart(false), m_isEnd(false), m_isBarrier(false),
		m_isPath(false), m_unvisited(true), m_isCursorSurrounding(false),
		m_isCursorCenter(false) {
	//m_color = NORMAL_NODE_COLOR;
}

void Node::setPos(int x, int y) {
	m_x = x;
	m_y = y;
}

void Node::resetVariables() {
	m_distanceFromStart = std::numeric_limits<float>::max();
	m_calculatedDistanceToEnd = std::numeric_limits<float>::max();
	m_isStart = false;
	m_isEnd = false;
	m_isBarrier = false;
	m_isPath = false;
	m_unvisited = true;
	m_isCursorCenter = false;
	m_isCursorSurrounding = false;
}

Node::~Node() {}

} /* namespace lso */
