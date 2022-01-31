/*
 * DijkstraAlgorithm.h
 *
 *  Created on: Jan 20, 2022
 *      Author: larsolt
 */

#ifndef DIJKSTRAALGORITHM_H_
#define DIJKSTRAALGORITHM_H_

#include "NodeGrid.h"
#include <iostream>

namespace lso {

class DijkstraAlgorithm {

protected:
	NodeGrid m_nodeGrid;
	int m_gridWidth;
	int m_gridHeight;
	float m_rightGridStepLength;
	float m_diagonalGridStepLength;
	int m_endNodeX;
	int m_endNodeY;
	int m_startNodeX;
	int m_startNodeY;
	bool m_pathFound;
	bool m_algorithmRunning;

public:
	int m_currentX;
	int m_currentY;

public:
	DijkstraAlgorithm(NodeGrid nodeGrid, int gridWidth, int gridHeight, int gridStepLength);

	void step();
	void setStart(int startX, int startY);
	bool nodeWithinBounds(int x, int y);

	virtual void setEnd(int endX, int endY);
	virtual int* getSmallestGlobalDistance();
	virtual void setPathDistances(int gridX, int gridY);
	virtual void setShortestStep();

	bool toggleRunning() { m_algorithmRunning = !m_algorithmRunning; return m_algorithmRunning; };

	// getters
	bool getAlgorithmRunning() { return m_algorithmRunning; };

	// setters
	void setPathFound(bool pathFound) { m_pathFound = pathFound; };
	void setAlgorithmRunning(bool algorithmRunning) { m_algorithmRunning = algorithmRunning; };

	virtual ~DijkstraAlgorithm();

};

} /* namespace lso */

#endif /* DIJKSTRAALGORITHM_H_ */
