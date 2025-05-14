#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include <utility> 

std::vector<std::pair<int, int>> AStarPath(int startX, int startY, int endX, int endY);
bool isWalkable(int x, int y);

#endif
