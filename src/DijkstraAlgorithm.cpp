/*
 * DijkstraAlgorithm.cpp
 *
 *  Created on: Jan 20, 2022
 *      Author: larsolt
 */

#include "DijkstraAlgorithm.h"

using namespace std;

namespace lso {

DijkstraAlgorithm::DijkstraAlgorithm(NodeGrid nodeGrid, int gridWidth, int gridHeight, int gridStepLength): m_nodeGrid(nodeGrid) {
	m_gridWidth = gridWidth;
	m_gridHeight = gridHeight;
	m_pathFound = false;
	m_algorithmRunning = false;
	m_rightGridStepLength = gridStepLength;
	m_diagonalGridStepLength = m_rightGridStepLength / sin(45);

	// init start/end nodes to (0,0) (overridden in setStartEnd)
	m_startNodeX = 0;
	m_startNodeY = 0;
	m_endNodeX = 0;
	m_endNodeY = 0;

	// init focus node to zero (overridden in setStartEnd)
	m_currentX = 0;
	m_currentY = 0;
}

void DijkstraAlgorithm::setStart(int startX, int startY) {
	m_startNodeX = startX;
	m_startNodeY = startY;

	// set focus node to start
	m_currentX = startX;
	m_currentY = startY;
}

void DijkstraAlgorithm::setEnd(int endX, int endY) {
	m_endNodeX = endX;
	m_endNodeY = endY;
}

bool DijkstraAlgorithm::nodeWithinBounds(int x, int y) {
	if((x >= 0) && (y >= 0) && (x < m_gridWidth) && (y < m_gridHeight)) {
		return true;
	} else {
		return false;
	}
}

void DijkstraAlgorithm::step() {
	// set algorithm running
	m_algorithmRunning = true;

	// check path not found
	if(!m_pathFound) {
		setPathDistances(m_currentX, m_currentY);

		// mark focus node as visited
		m_nodeGrid.setNodeUnvisited((m_gridWidth * m_currentY) + m_currentX);

		// set new focus node
		int* pos = getSmallestGlobalDistance();

		m_currentX = pos[0];
		m_currentY = pos[1];

		// if focus node is end node
		if((m_currentX == m_endNodeX) && (m_currentY == m_endNodeY)) {
			m_pathFound = true;
		}

	} else {
		int pos = (m_gridWidth * m_currentY) + m_currentX;
		int startPos = (m_gridWidth * m_startNodeY) + m_startNodeX;

		if(pos != startPos) {
			setShortestStep();
		} else {
			m_algorithmRunning = false;
		}
	}
}

void DijkstraAlgorithm::setPathDistances(int gridX, int gridY) {
	int pos = (m_gridWidth * gridY) + gridX;
	float focusDistanceFromStart = m_nodeGrid.getDistanceFromStart(pos);

	for(int tempY = (gridY - m_rightGridStepLength); tempY <= (gridY + m_rightGridStepLength); tempY++) {
		for(int tempX = (gridX - m_rightGridStepLength); tempX <= (gridX + m_rightGridStepLength); tempX++) {

			int tempPos = (m_gridWidth * tempY) + tempX;

			// loop only surrounding nodes on the grid which are not barriers
			if((tempPos != pos) && nodeWithinBounds(tempX, tempY) && !(m_nodeGrid.getIsBarrierNode(tempPos))) {
				float tempExistingDistance = m_nodeGrid.getDistanceFromStart(tempPos);
				float tempDistanceThroughFocus;

				if((tempX != gridX) && (tempY != gridY)) { // is corner
					tempDistanceThroughFocus = focusDistanceFromStart + m_diagonalGridStepLength;
				} else {
					tempDistanceThroughFocus = focusDistanceFromStart + m_rightGridStepLength;
				}

				if(tempDistanceThroughFocus < tempExistingDistance) {
					m_nodeGrid.setDistanceFromStart(tempPos, tempDistanceThroughFocus);
				}
			}
		}
	}
}

int* DijkstraAlgorithm::getSmallestGlobalDistance() {
	float shortestDistance = std::numeric_limits<float>::max();
	int pos[2]; // [x, y]
	int* pPos = pos;

	// loop over grid, find shortest distance
	for(int y = 0; y < m_gridHeight; y++) {
		for(int x = 0; x < m_gridWidth; x++) {
			int tempPos = (m_gridWidth * y) + x;
			float tempDistance = m_nodeGrid.getDistanceFromStart(tempPos);

			if(m_nodeGrid.getIsNodeUnvisited(tempPos) && (tempDistance < shortestDistance)) {
				shortestDistance = tempDistance;
				pos[0] = x;
				pos[1] = y;
			}
		}
	}

	return pPos;
}

void DijkstraAlgorithm::setShortestStep() {
	int pos = (m_gridWidth * m_currentY) + m_currentX;
	float shortestDistance = std::numeric_limits<float>::max();
	int shortestPosX;
	int shortestPosY;

	// set current focus node as path
	m_nodeGrid.setPathNode(pos);

	// find nearest neighbor to start
	for(int tempY = (m_currentY - m_rightGridStepLength); tempY <= (m_currentY + m_rightGridStepLength); tempY++) {
		for(int tempX = (m_currentX - m_rightGridStepLength); tempX <= (m_currentX + m_rightGridStepLength); tempX++) {

			int tempPos = (m_gridWidth * tempY) + tempX;

			// loop only surrounding nodes on the grid
			if((tempPos != pos) && nodeWithinBounds(tempX, tempY)) {

				float tempDistance = m_nodeGrid.getDistanceFromStart(tempPos);

				if(tempDistance < shortestDistance) {
					shortestDistance = tempDistance;

					shortestPosX = tempX;
					shortestPosY = tempY;
				}

			}
		}
	}

	// set focus node to shortest neighbor
	m_currentX = shortestPosX;
	m_currentY = shortestPosY;
}

DijkstraAlgorithm::~DijkstraAlgorithm() {
	setAlgorithmRunning(false);
	setPathFound(false);
}

} /* namespace lso */
