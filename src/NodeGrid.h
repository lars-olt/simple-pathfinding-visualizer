/*
 * Grid.h
 *
 *  Created on: Jan 16, 2022
 *      Author: larsolt
 */

#ifndef NODEGRID_H_
#define NODEGRID_H_

#include "Node.h"

namespace lso {

struct NodeGrid {

static const int GRID_BOARDER = 10;
static const int GRID_PADDING = 15;
static const int CIRCLE_RADIUS = (GRID_PADDING * 2)/5;

Node* p_nodeGrid;

int m_windowWidth;
int m_windowHeight;
int m_gridWidth;
int m_gridHeight;


public:
	NodeGrid(int windowWidth, int windowHeight);
	void init();
	void clearCursorCluster(int x, int y);
	void resetGrid();
	void close() { delete [] p_nodeGrid; };

	// setters
	void setStartNode(int pos) { p_nodeGrid[pos].m_isStart = true; };
	void setEndNode(int pos) { p_nodeGrid[pos].m_isEnd = true; m_endUndefined = false; };
	void setBarrierNode(int pos) { p_nodeGrid[pos].m_isBarrier = true; };
	void setPathNode(int pos) { p_nodeGrid[pos].m_isPath = true; };
	void setNodeUnvisited(int pos) { p_nodeGrid[pos].m_unvisited = false; };
	void setDistanceFromStart(int pos, float dist) { p_nodeGrid[pos].m_distanceFromStart = dist; };
	void setCalculatedDistanceToEnd(int pos, float dist) { p_nodeGrid[pos].m_calculatedDistanceToEnd = dist; };
	void setCursorCluster(int x, int y);

	// getters
	int getNodeX(int pos) { return p_nodeGrid[pos].m_x; };
	int getNodeY(int pos) { return p_nodeGrid[pos].m_y; };
	float getDistanceFromStart(int pos) { return p_nodeGrid[pos].m_distanceFromStart; };
	float getCalculatedDistanceToEnd(int pos) { return p_nodeGrid[pos].m_calculatedDistanceToEnd; };
	bool getIsStartNode(int pos) { return p_nodeGrid[pos].m_isStart; };
	bool getIsEndNode(int pos) { return p_nodeGrid[pos].m_isEnd; };
	bool getIsBarrierNode(int pos) { return p_nodeGrid[pos].m_isBarrier; };
	bool getIsPathNode(int pos) { return p_nodeGrid[pos].m_isPath; };
	bool getIsNodeUnvisited(int pos) { return p_nodeGrid[pos].m_unvisited;  };
	bool getIsCursorCenter(int x, int y) { return p_nodeGrid[m_gridWidth * y + x].m_isCursorCenter; };
	Node* getGrid() { return p_nodeGrid; };
	Uint32 getColor(int pos);

	virtual ~NodeGrid();

private:
	bool m_endUndefined;

};

} // namespace lso

#endif /* NODEGRID_H_ */
