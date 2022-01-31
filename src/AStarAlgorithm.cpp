/*
 * AStarAlgorithm.cpp
 *
 *  Created on: Jan 25, 2022
 *      Author: larsolt
 */

#include "AStarAlgorithm.h"

namespace lso {

AStarAlgorithm::AStarAlgorithm(NodeGrid nodeGrid, int gridWidth, int gridHeight, int gridStepLength):
		DijkstraAlgorithm(nodeGrid, gridWidth, gridHeight, gridStepLength) {
}

void AStarAlgorithm::setEnd(int endX, int endY) {
	m_endNodeX = endX;
	m_endNodeY = endY;

	// init distances from end
	setDistancesFromEnd();
}

void AStarAlgorithm::setDistancesFromEnd() {
	for(int y = 0; y < m_gridHeight; y++) {
		for(int x = 0; x < m_gridWidth; x++) {
			int tempPos = (m_gridWidth * y) + x;
			int xLeg = m_endNodeX - x;
			int yLeg = m_endNodeY - y;

			float dist = sqrt(pow(xLeg, 2) + pow(yLeg, 2));
			m_nodeGrid.setCalculatedDistanceToEnd(tempPos, dist);
		}
	}
}

void AStarAlgorithm::setPathDistances(int gridX, int gridY) {
	int pos = (m_gridWidth * gridY) + gridX;
	float focusDistanceFromStart = m_nodeGrid.getDistanceFromStart(pos);

	for(int tempY = (gridY - m_rightGridStepLength); tempY <= (gridY + m_rightGridStepLength); tempY++) {
		for(int tempX = (gridX - m_rightGridStepLength); tempX <= (gridX + m_rightGridStepLength); tempX++) {
			int tempPos = (m_gridWidth * tempY) + tempX;

			// loop only surrounding nodes on the grid which are not barriers
			if((tempPos != pos) && nodeWithinBounds(tempX, tempY) && !(m_nodeGrid.getIsBarrierNode(tempPos))) {
				float tempDistanceFromStart;
				float tempDistanceToEnd = m_nodeGrid.getCalculatedDistanceToEnd(tempPos);
				float existingDistanceTotal = m_nodeGrid.getDistanceFromStart(tempPos) + m_nodeGrid.getCalculatedDistanceToEnd(tempPos);

				if((tempX != gridX) && (tempY != gridY)) { // is corner
					tempDistanceFromStart = focusDistanceFromStart + m_diagonalGridStepLength;
				} else {
					tempDistanceFromStart = focusDistanceFromStart + m_rightGridStepLength;
				}

				float tempDistanceTotal = tempDistanceFromStart + tempDistanceToEnd;

				if(tempDistanceTotal < existingDistanceTotal) {
					m_nodeGrid.setDistanceFromStart(tempPos, tempDistanceFromStart);
					m_nodeGrid.setCalculatedDistanceToEnd(tempPos, tempDistanceToEnd);
				}
			}
		}
	}
}

void AStarAlgorithm::setShortestStep() {
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

			// loop only visited surrounding nodes on the grid
			if(!m_nodeGrid.getIsNodeUnvisited(tempPos) && (tempPos != pos) && nodeWithinBounds(tempX, tempY)) {

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

int* AStarAlgorithm::getSmallestGlobalDistance() {
	float shortestDistance = std::numeric_limits<float>::max();
	int pos[2]; // [x, y]
	int* pPos = pos;

	// loop over grid, find shortest distance
	for(int y = 0; y < m_gridHeight; y++) {
		for(int x = 0; x < m_gridWidth; x++) {
			int tempPos = (m_gridWidth * y) + x;
			float tempDistanceTotal = m_nodeGrid.getDistanceFromStart(tempPos) + m_nodeGrid.getCalculatedDistanceToEnd(tempPos);

			if(m_nodeGrid.getIsNodeUnvisited(tempPos) && (tempDistanceTotal < shortestDistance)) {
				shortestDistance = tempDistanceTotal;
				pos[0] = x;
				pos[1] = y;
			}
		}
	}

	return pPos;
}

} /* namespace lso */
