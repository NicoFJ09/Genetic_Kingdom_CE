#include "Pathfinding.h"
#include <queue>
#include <cmath>
#include <algorithm>
#include <vector>
#include <array>

// Nodo para el algoritmo A*
struct Node {
    int x, y;
    int gCost;
    int hCost;
    Node* parent;

    Node(int x, int y, int g = 0, int h = 0, Node* p = nullptr)
        : x(x), y(y), gCost(g), hCost(h), parent(p) {}

    int fCost() const { return gCost + hCost; }
    bool operator>(const Node& other) const { return fCost() > other.fCost(); }
};

int heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

bool isWalkable(int x, int y, const std::vector<std::vector<int>>& map, int rows, int columns) {
    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
    return map[x][y] == 0 || map[x][y] == 2 || map[x][y] == 3;
}

template <size_t ROWS, size_t COLUMNS>
std::vector<std::pair<int, int>> AStarPath(
    int startX, int startY, int endX, int endY,
    const std::array<std::array<int, COLUMNS>, ROWS>& map
) {
    // Convertir el array fijo a vector de vectores
    std::vector<std::vector<int>> mapVector;
    mapVector.reserve(ROWS);
    for (const auto& row : map) {
        mapVector.emplace_back(row.begin(), row.end());
    }
    int rows = static_cast<int>(ROWS);
    int columns = static_cast<int>(COLUMNS);

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(columns, false));
    std::vector<Node*> allNodes;

    auto cmp = [](Node* a, Node* b) { return a->fCost() > b->fCost(); };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> openList(cmp);

    Node* startNode = new Node(startX, startY, 0, heuristic(startX, startY, endX, endY));
    openList.push(startNode);
    allNodes.push_back(startNode);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (visited[current->x][current->y]) continue;
        visited[current->x][current->y] = true;

        if (current->x == endX && current->y == endY) {
            std::vector<std::pair<int, int>> path;
            Node* p = current;
            while (p != nullptr) {
                path.emplace_back(p->x, p->y);
                p = p->parent;
            }
            std::reverse(path.begin(), path.end());
            for (Node* n : allNodes) delete n;
            return path;
        }

        const int dx[] = {0, 1, 0, -1};
        const int dy[] = {1, 0, -1, 0};

        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (!isWalkable(nx, ny, mapVector, rows, columns) || visited[nx][ny]) continue;

            int newG = current->gCost + 1;
            int h = heuristic(nx, ny, endX, endY);
            Node* neighbor = new Node(nx, ny, newG, h, current);
            openList.push(neighbor);
            allNodes.push_back(neighbor);
        }
    }
    for (Node* n: allNodes) delete n;
    return {};
}

// Instanciación explícita para evitar linker errors si usas el cpp separado
template std::vector<std::pair<int, int>> AStarPath<19, 31>(
    int, int, int, int, const std::array<std::array<int, 31>, 19>&
);