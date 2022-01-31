/*
 * Grid.cpp
 *
 *  Created on: Jan 16, 2022
 *      Author: larsolt
 */

#include "NodeGrid.h"

namespace lso {

NodeGrid::NodeGrid(int windowWidth, int windowHeight): m_windowWidth(windowWidth), m_windowHeight(windowHeight) {
	m_endUndefined = true;
	m_gridWidth = (m_windowWidth - GRID_BOARDER * 2) / GRID_PADDING;
	m_gridHeight = (m_windowHeight - GRID_BOARDER * 2) / GRID_PADDING;
	p_nodeGrid = new Node[m_gridWidth * m_gridHeight];
}

void NodeGrid::init() {
	for(int y = 0; y < m_gridHeight; y++) {
		for(int x = 0; x < m_gridWidth; x++) {
			p_nodeGrid[(m_gridWidth * y) + x].setPos(((x * GRID_PADDING) + GRID_BOARDER), ((y * GRID_PADDING) + GRID_BOARDER));
		}
	}
}

void NodeGrid::setCursorCluster(int x, int y) {
	for(int tempX = x - 1; tempX <= x + 1; tempX++) {
		for(int tempY = y - 1; tempY <= y + 1; tempY++) {
			p_nodeGrid[(m_gridWidth * tempY) + tempX].m_isCursorSurrounding = true;
		}
	}

	p_nodeGrid[(m_gridWidth * y) + x].m_isCursorCenter = true;
}

void NodeGrid::clearCursorCluster(int x, int y) {
	for(int tempX = x - 1; tempX <= x + 1; tempX++) {
		for(int tempY = y - 1; tempY <= y + 1; tempY++) {
			p_nodeGrid[(m_gridWidth * tempY) + tempX].m_isCursorSurrounding = false;
			p_nodeGrid[(m_gridWidth * tempY) + tempX].m_isCursorCenter = false;
		}
	}
}

void NodeGrid::resetGrid() {
	for(int y = 0; y < m_gridHeight; y++) {
		for(int x = 0; x < m_gridWidth; x++) {
			p_nodeGrid[(m_gridWidth * y) + x].resetVariables();
		}
	}

	m_endUndefined = true;
}

Uint32 NodeGrid::getColor(int pos) {
	bool startOrEnd = p_nodeGrid[pos].m_isStart || p_nodeGrid[pos].m_isEnd;
	bool cursorCenter = p_nodeGrid[pos].m_isCursorCenter;
	bool cursorSurrounding = p_nodeGrid[pos].m_isCursorSurrounding;
	bool barrier = p_nodeGrid[pos].m_isBarrier;
	bool path = p_nodeGrid[pos].m_isPath;
	bool visited = !p_nodeGrid[pos].m_unvisited;

	if(startOrEnd) {
		return Node::START_AND_END_COLOR;
	} else if(barrier) {
		return Node::BARRIER_COLOR;
	} else if(path) {
		return Node::PATH_COLOR;
	} else if(visited) {
		return Node::VISITED_COLOR;
	} else if(cursorCenter && m_endUndefined) {
		return Node::START_AND_END_COLOR;
	} else if(cursorCenter) {
		return Node::BARRIER_COLOR;
	} else if(cursorSurrounding) {
		return Node::CURSOR_OUTSIDE_COLOR;
	} else {
		return Node::NORMAL_NODE_COLOR;
	}
}

NodeGrid::~NodeGrid() {}

} // namespace lso

