//
//  day_twelve.cpp
//  advent_of_code_2022_cpp
//
//  Created by Maksym Kostynskyi on 09.11.2023.
//

#include "day_twelve.hpp"
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <array>
#include <sstream>
#include <queue>           // For using std::priority_queue
#include <unordered_map>   // For using std::unordered_map
#include <unordered_set>   // For using std::unordered_set
#include <functional>      // For using std::greater

struct Move {
    int valueY;
    int valueX;
    char direction;
};


struct Position {
    int y, x;

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template <>
    struct hash<Position> {
        size_t operator()(const Position& pos) const {
            // Combine the hash of the individual members using bitwise XOR and bit shifting
            return hash<int>()(pos.y) ^ (hash<int>()(pos.x) << 1);
        }
    };
}

struct Node {
    Position pos;
    int height;
    int g_cost;  // Cost from start node
    int h_cost;  // Heuristic cost to end node
    Node* parent;  // Parent node in the path

    int f_cost() const { return g_cost + h_cost; }

    bool operator>(const Node& other) const {
        return f_cost() > other.f_cost();
    }
};

struct Maze {
    int width, height;
    char heightmap[100][1000]; // Maps (y, x) to step height

    Maze(int h, int w) : width(w), height(h) {}

    // Set height of a step at a specific position
    void setStepHeight(int y, int x, char h) {
        heightmap[y][x] = h;
    }

    // Get height of a step at a specific position
    char getHeight(const Position& pos) const {
        return heightmap[pos.y][pos.x]; // Return -1 or some other indicator for an invalid position
    }

    // Check if the position is valid within the maze
    bool isValidPosition(const Position& pos) const {
        return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
    }
};

int heuristic(const Position& a, const Position& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

std::vector<Node> getNeighbors(const Node& current, const Maze& maze) {
    std::vector<Node> neighbors;

    // Assuming you have a function to get the height of a position in the maze
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;  // Skip the current node itself

            Position newPos = {current.pos.y + dy, current.pos.x + dx};

            // Check for valid position and movement rules
            if (maze.isValidPosition(newPos)) {
                int newHeight = maze.getHeight(newPos);
                if ((newHeight == current.height || newHeight == current.height + 1 || newHeight < current.height) && (abs(current.pos.x - newPos.x) + (abs(current.pos.y - newPos.y))) < 2) {
                    Node neighbor = {newPos, newHeight, 0, 0, nullptr};
                    neighbors.push_back(neighbor);
                }
            }
        }
    }

    return neighbors;
}

Node AStar(const Position& start, const Position& end, const Maze& maze) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::unordered_set<Position> closedSet;  // Using Position for simplicity

    Node startNode = {start, maze.getHeight(start), 0, heuristic(start, end), nullptr};
    openSet.push(startNode);

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.pos == end) {
            return current;  // Path found
        }

        if (closedSet.find(current.pos) != closedSet.end()) {
            continue;  // Already processed this node
        }

        closedSet.insert(current.pos);
        std::vector<Node> neighbors = getNeighbors(current, maze);
        for (const auto& neighbor : neighbors) {
            if (closedSet.find(neighbor.pos) != closedSet.end()) {
                continue;
            }

            int tentative_g_cost = current.g_cost + 1;  // Assuming equal cost for each move

            Node updatedNeighbor = neighbor;
            updatedNeighbor.g_cost = tentative_g_cost;
            updatedNeighbor.h_cost = heuristic(neighbor.pos, end);
            updatedNeighbor.parent = new Node(current);  // Memory management considerations

            openSet.push(updatedNeighbor);
        }
    }

    return Node();  // Path not found
}

std::vector<Position> reconstructPath(Node* node) {
    std::vector<Position> path;
    while (node != nullptr) {
        path.push_back(node->pos);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}


int find_least_steps(vector<string> input)
{
    cout << endl;
    char heightmap[input.size()][input[0].length()];
    Maze maze((int)input.size(), (int)input[0].length());
    char moves[input.size()][input[0].length()];
    int startY = 0, startX = 0, endY = 0, endX = 0, moveX, moveY;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].length(); j++) {
            heightmap[i][j] = input[i][j];
            maze.setStepHeight(i, j, input[i][j]);
            if (heightmap[i][j] == 'S') {
                startY = i;
                startX = j;
                maze.setStepHeight(i, j, 'a');
                heightmap[i][j] = 'a';
            }
            if (heightmap[i][j] == 'E') {
                endY = i;
                endX = j;
                maze.setStepHeight(i, j, 'z');
                heightmap[i][j] = 'z';
            }
            moves[i][j] = '.';
            cout << heightmap[i][j];
        }
        cout << endl;
    }
    
    cout << endl;
    
    for (int i = 0; i < maze.height; i++) {
        for (int j = 0; j < maze.width; j++) {
            Position pos{i, j};
            cout << maze.getHeight(pos);
        }
        cout << endl;
    }
    
    cout << endl;

    
    // Set start and end positions
    
   
    int min_counter = INT_MAX;
    int counter = 0;
    for (int i = 0; i < input.size(); i++) {
        counter = 0;
        Position start{i, startX};
        Position end{endY, endX};
        // Find the shortestpath using A* algorithm
        Node endNode = AStar(start, end, maze);
        // Reconstruct and print the path
        std::vector<Position> path = reconstructPath(&endNode);
        for (const auto& pos : path) {
            counter++;
    //        std::cout << "(" << pos.x << ", " << pos.y << "): " << " -> ";
        }
        if (min_counter > counter && counter > 0) {
            min_counter = counter;
        }
    }
    
//    std::cout << "End" << std::endl;
    
//    moveX = startX;
//    moveY = startY;
//    
//    char direction = '.';
//    char current_weight = 'a';
//    int steps = 0;
//    
//    Move up;
//    Move down;
//    Move left;
//    Move right;
//    up.direction = '^';
//    down.direction = 'V';
//    right.direction = '>';
//    left.direction = '<';
    
//    int prevMoveX = moveX;
//    int prevMoveY = moveY;
    
//    while (steps < 100) {
//        
//        up.valueY = moveY - 1 >= 0 ? moveY - 1 : INT_MAX;
//        up.valueX = moveX;
//        down.valueY = moveY + 1 < input.size() ? moveY + 1 : INT_MAX;
//        down.valueX = moveX;
//        left.valueX = moveX - 1 >= 0 ? moveX - 1 : INT_MAX;
//        left.valueY = moveY;
//        right.valueX = moveX + 1 < input[0].length() ? moveX + 1 : INT_MAX;
//        right.valueY = moveY;
//        
//        Move possible_moves[] = {up,down,right,left};
//        vector<Move> allowed_moves = {};
//        
//        for (const Move& pos: possible_moves) {
//            if (pos.valueX == INT_MAX || pos.valueY == INT_MAX) {
//                continue;
//            }
//            if ((((int)heightmap[moveY][moveX]) + 1) >= ((int)heightmap[pos.valueY][pos.valueX])) {
//                allowed_moves.push_back(pos);
//            }
//        }
//        
//        if (allowed_moves.size() == 0) {
//            steps++;
//            continue;
//        }
//        
//        Move min = allowed_moves[0];
//        
//        for (int i = 1; i < allowed_moves.size(); i++) {
//            if ((abs(endX - allowed_moves[i].valueX) + abs(endY - allowed_moves[i].valueY))
//                < (abs(endX - min.valueX) + abs(endY - min.valueY))) {
//                min = allowed_moves[i];
//            }
//        }
//        prevMoveX = moveX;
//        prevMoveY = moveY;
//        moveX = min.valueX;
//        moveY = min.valueY;
//        moves[min.valueY][min.valueX] = min.direction;
//        steps++;
//    }
//    cout << endl;
//    cout << endl;
//    for (int i = 0; i < input.size(); i++) {
//        for (int j = 0; j < input[i].length(); j++) {
//            cout << moves[i][j];
//        }
//        cout << endl;
//    }
    
    
//    cout << (int)heightmap[0][1]<< endl;
    
    
    return min_counter - 1;
}

