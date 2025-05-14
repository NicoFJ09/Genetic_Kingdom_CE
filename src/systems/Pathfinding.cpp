#include "Pathfinding.h"
#include "Constants.h"
#include <queue>
#include <cmath>
#include <algorithm>

constexpr int ROWS = 19;
constexpr int COLUMNS = 31;

//Nodes with (x,y) coordinates given by map. (Cells)
struct Node {
    int x, y;
    int gCost; //Moving cost from start to end
    int hCost; //Estimated cost (heuristic)
    Node* parent;

    Node(int x, int y, int g = 0, int h = 0, Node* p = nullptr)
        : x(x), y(y), gCost(g), hCost(h), parent(p) {}

    int fCost() const { return gCost + hCost; }

    //Compares nodes fcost
    bool operator>(const Node& other) const { return fCost() > other.fCost(); }
};

//======================= A* Algorithm ===========================

int heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

bool isWalkable(int x, int y) {
    if (x < 0 || x >= ROWS || y < 0 || y >= COLUMNS) return false;
    return GAME_MAP[x][y] == 0 || GAME_MAP[x][y] == 2 || GAME_MAP[x][y] == 3;
}

std::vector<std::pair<int, int>> AStarPath(int startX, int startY, int endX, int endY) {
    std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLUMNS, false));
    std::vector<Node*> allNodes; // Store all nodes to free them later

    //Compare nodes by fCost and list them in priority queue from lowest(first in queue) to highest (last in queue)

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
            std::vector<std::pair<int, int>> path;        // Generate path once reached the castle
            Node* p = current;
            while (p != nullptr) {                        // Backtrack to find the path
                path.emplace_back(p->x, p->y);
                p = p->parent;
            }
            std::reverse(path.begin(), path.end());
            for (Node* n : allNodes) delete n;            // Free memory once path is generated
            return path;                                  // Path 
        }

        const int dx[] = {0, 1, 0, -1};
        const int dy[] = {1, 0, -1, 0};

        for (int i = 0; i < 4; ++i) {                              //Check all 4 directions of current node and add them to the openList queue
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (!isWalkable(nx, ny) || visited[nx][ny]) continue;

            int newG = current->gCost + 1;
            int h = heuristic(nx, ny, endX, endY);
            Node* neighbor = new Node(nx, ny, newG, h, current);
            openList.push(neighbor);
            allNodes.push_back(neighbor);
        }
    }
        for (Node* n: allNodes) delete n; //Free all nodes from heap
        return {};

}
