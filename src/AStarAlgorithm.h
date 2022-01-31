/*
 * AStarAlgorithm.h
 *
 *  Created on: Jan 25, 2022
 *      Author: larsolt
 */

#ifndef ASTARALGORITHM_H_
#define ASTARALGORITHM_H_

#include "DijkstraAlgorithm.h"
#include <iostream>

using namespace std;

namespace lso {

class AStarAlgorithm : public DijkstraAlgorithm {

public:
	AStarAlgorithm(NodeGrid nodeGrid, int gridWidth, int gridHeight, int gridStepLength);
	void setDistancesFromEnd();

	void setEnd(int endX, int endY);
	void setShortestStep();
	int* getSmallestGlobalDistance();
	void setPathDistances(int gridX, int gridY);

};

} /* namespace lso */

#endif /* ASTARALGORITHM_H_ */
