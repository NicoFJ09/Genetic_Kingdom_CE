#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include <utility>
#include <array>
#include <cstddef>

// Recibe el mapa como array fijo y lo convierte internamente

template <size_t ROWS, size_t COLUMNS>
std::vector<std::pair<int, int>> AStarPath(
    int startX, int startY, int endX, int endY,
    const std::array<std::array<int, COLUMNS>, ROWS>& map
);

#endif