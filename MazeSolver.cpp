#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Node {
public:
    pair<int, int> state;
    Node* parent;
    string action;

    Node(pair<int, int> state, Node* parent, string action)
        : state(state), parent(parent), action(action) {}
};

// StackFrontier for DFS (LIFO)
class StackFrontier {
protected:
    stack<Node*> frontier;

public:
    void add(Node* node) {
        frontier.push(node);
    }

    bool contains_state(pair<int, int> state) {
        stack<Node*> temp = frontier;
        while (!temp.empty()) {
            if (temp.top()->state == state) {
                return true;
            }
            temp.pop();
        }
        return false;
    }

    bool empty() {
        return frontier.empty();
    }

    Node* remove() {
        if (empty()) {
            throw runtime_error("Empty frontier");
        }
        Node* node = frontier.top();
        frontier.pop();
        return node;
    }
};

// QueueFrontier for BFS (FIFO)
class QueueFrontier {
protected:
    queue<Node*> frontier;

public:
    void add(Node* node) {
        frontier.push(node);
    }

    bool contains_state(pair<int, int> state) {
        queue<Node*> temp = frontier;
        while (!temp.empty()) {
            if (temp.front()->state == state) {
                return true;
            }
            temp.pop();
        }
        return false;
    }

    bool empty() {
        return frontier.empty();
    }

    Node* remove() {
        if (empty()) {
            throw runtime_error("Empty frontier");
        }
        Node* node = frontier.front();
        frontier.pop();
        return node;
    }
};

class Maze {
private:
    vector<vector<bool>> walls;
    pair<int, int> start;
    pair<int, int> goal;
    vector<pair<int, int>> solution;
    set<pair<int, int>> explored;
    int num_explored;
    int height, width;

public:
    // Maze directly in the code, using '|' for walls, ' ' for free space, 's' for start, 'e' for goal
    Maze() {
        vector<string> maze_data = {
            "|s|     |",
            "| | | | |",
            "| | | | |",
            "|   |   |",
            "| |   |e|",
            "| | | | |",
            "|       |",
            "| | | | |"
        };

        height = maze_data.size();
        width = maze_data[0].size();

        walls.resize(height, vector<bool>(width, false));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (maze_data[i][j] == 's') {
                    start = {i, j};
                } else if (maze_data[i][j] == 'e') {
                    goal = {i, j};
                } else if (maze_data[i][j] == '|') {
                    walls[i][j] = true;
                }
            }
        }
    }

    void print() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (walls[i][j]) {
                    cout << "|";
                } else if (make_pair(i, j) == start) {
                    cout << "s";
                } else if (make_pair(i, j) == goal) {
                    cout << "e";
                } else if (find(solution.begin(), solution.end(), make_pair(i, j)) != solution.end()) {
                    cout << "*";
                } else {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    vector<pair<string, pair<int, int>>> neighbors(pair<int, int> state) {
        int row = state.first;
        int col = state.second;

        vector<pair<string, pair<int, int>>> candidates = {
            {"up", {row - 1, col}},
            {"down", {row + 1, col}},
            {"left", {row, col - 1}},
            {"right", {row, col + 1}}
        };

        vector<pair<string, pair<int, int>>> result;
        for (auto& candidate : candidates) {
            int r = candidate.second.first;
            int c = candidate.second.second;
            if (r >= 0 && r < height && c >= 0 && c < width && !walls[r][c]) {
                result.push_back(candidate);
            }
        }
        return result;
    }

    void solve(bool use_dfs) {
        num_explored = 0;
        solution.clear();

        Node* start_node = new Node(start, nullptr, "");
        
        // Use DFS (StackFrontier) or BFS (QueueFrontier) based on user choice
        StackFrontier dfs_frontier;
        QueueFrontier bfs_frontier;
        if (use_dfs) {
            dfs_frontier.add(start_node);
        } else {
            bfs_frontier.add(start_node);
        }

        explored.clear();

        while (true) {
            if ((use_dfs && dfs_frontier.empty()) || (!use_dfs && bfs_frontier.empty())) {
                throw runtime_error("No solution");
            }

            Node* node = use_dfs ? dfs_frontier.remove() : bfs_frontier.remove();
            num_explored++;

            if (node->state == goal) {
                while (node->parent != nullptr) {
                    solution.push_back(node->state);
                    node = node->parent;
                }
                reverse(solution.begin(), solution.end());
                return;
            }

            explored.insert(node->state);

            for (auto& neighbor : neighbors(node->state)) {
                if (!use_dfs ? !bfs_frontier.contains_state(neighbor.second) : !dfs_frontier.contains_state(neighbor.second)) {
                    if (explored.find(neighbor.second) == explored.end()) {
                        Node* child = new Node(neighbor.second, node, neighbor.first);
                        if (use_dfs) {
                            dfs_frontier.add(child);
                        } else {
                            bfs_frontier.add(child);
                        }
                    }
                }
            }
        }
    }
};

int main() {
    Maze maze;

    cout << "Maze:" << endl;
    maze.print();

    cout << "\nChoose the algorithm to solve the maze: \n";
    cout << "1. DFS (Depth-First Search)\n";
    cout << "2. BFS (Breadth-First Search)\n";
    int choice;
    cin >> choice;

    bool use_dfs = (choice == 1);
    
    try {
        cout << "Solving..." << endl;
        maze.solve(use_dfs);
        cout << "Solution:" << endl;
        maze.print();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

return 0;
}
