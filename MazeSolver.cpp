#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

const int CELL_SIZE = 40;
const int ROWS = 15;
const int COLS = 20;

using Grid = vector<vector<int>>;
const vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

bool isValid(int r, int c, const Grid& maze) {
    return r >= 0 && r < maze.size() && c >= 0 && c < maze[0].size() && maze[r][c] == 0;
}

Grid generateMaze(int rows, int cols, pair<int, int> start, pair<int, int> end) {
    random_device rd;
    mt19937 rng(rd());
    Grid maze(rows, vector<int>(cols, 1));

    stack<pair<int, int>> s;
    maze[start.first][start.second] = 0;
    s.push(start);

    while (!s.empty()) {
        auto [r, c] = s.top(); s.pop();
        vector<pair<int, int>> dirs = directions;
        shuffle(dirs.begin(), dirs.end(), rng);

        for (auto [dr, dc] : dirs) {
            int nr = r + dr * 2, nc = c + dc * 2;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && maze[nr][nc] == 1) {
                maze[r + dr][c + dc] = 0;
                maze[nr][nc] = 0;
                s.push({ nr, nc });
            }
        }
    }

    for (int i = 0; i < 30; ++i) {
        int r = rng() % rows;
        int c = rng() % cols;
        if (maze[r][c] == 1)
            maze[r][c] = 0;
    }

    maze[start.first][start.second] = 0;
    maze[end.first][end.second] = 0;
    return maze;
}

void drawMaze(sf::RenderWindow& window, const Grid& maze,
    const vector<vector<bool>>& visited,
    const vector<pair<int, int>>& path,
    pair<int, int> start, pair<int, int> end) {
    window.clear();
    for (int r = 0; r < maze.size(); ++r) {
        for (int c = 0; c < maze[0].size(); ++c) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            cell.setPosition({ static_cast<float>(c * CELL_SIZE), static_cast<float>(r * CELL_SIZE) });

            if (make_pair(r, c) == start)
                cell.setFillColor(sf::Color::Green);
            else if (make_pair(r, c) == end)
                cell.setFillColor(sf::Color::Magenta);
            else if (maze[r][c] == 1)
                cell.setFillColor(sf::Color::Black);
            else if (find(path.begin(), path.end(), make_pair(r, c)) != path.end())
                cell.setFillColor(sf::Color::Blue);
            else if (visited[r][c])
                cell.setFillColor(sf::Color(255, 0, 0, 150));
            else
                cell.setFillColor(sf::Color::White);

            window.draw(cell);
        }
    }
    window.display();
}

vector<pair<int, int>> reconstructPath(pair<int, int> end,
    const vector<vector<pair<int, int>>>& parent) {
    vector<pair<int, int>> path;
    for (auto at = end; at != make_pair(-1, -1); at = parent[at.first][at.second])
        path.push_back(at);
    reverse(path.begin(), path.end());
    return path;
}

vector<pair<int, int>> solveDFS(const Grid& maze, vector<vector<bool>>& visited,
    pair<int, int> start, pair<int, int> end) {
    vector<vector<pair<int, int>>> parent(maze.size(), vector<pair<int, int>>(maze[0].size(), { -1, -1 }));
    stack<pair<int, int>> s;
    s.push(start);
    visited[start.first][start.second] = true;

    while (!s.empty()) {
        auto [r, c] = s.top(); s.pop();
        if (make_pair(r, c) == end) break;
        for (auto [dr, dc] : directions) {
            int nr = r + dr, nc = c + dc;
            if (isValid(nr, nc, maze) && !visited[nr][nc]) {
                visited[nr][nc] = true;
                parent[nr][nc] = { r, c };
                s.push({ nr, nc });
            }
        }
    }
    return reconstructPath(end, parent);
}

vector<pair<int, int>> solveBFS(const Grid& maze, vector<vector<bool>>& visited,
    pair<int, int> start, pair<int, int> end) {
    vector<vector<pair<int, int>>> parent(maze.size(), vector<pair<int, int>>(maze[0].size(), { -1, -1 }));
    queue<pair<int, int>> q;
    q.push(start);
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (make_pair(r, c) == end) break;
        for (auto [dr, dc] : directions) {
            int nr = r + dr, nc = c + dc;
            if (isValid(nr, nc, maze) && !visited[nr][nc]) {
                visited[nr][nc] = true;
                parent[nr][nc] = { r, c };
                q.push({ nr, nc });
            }
        }
    }
    return reconstructPath(end, parent);
}

int heuristic(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<pair<int, int>> solveAStar(const Grid& maze, vector<vector<bool>>& visited,
    pair<int, int> start, pair<int, int> end) {
    vector<vector<int>> gScore(maze.size(), vector<int>(maze[0].size(), 1e9));
    vector<vector<pair<int, int>>> parent(maze.size(), vector<pair<int, int>>(maze[0].size(), { -1, -1 }));
    using Node = tuple<int, int, int>;
    priority_queue<Node, vector<Node>, greater<>> pq;

    gScore[start.first][start.second] = 0;
    pq.push({ heuristic(start, end), start.first, start.second });

    while (!pq.empty()) {
        auto [f, r, c] = pq.top(); pq.pop();
        visited[r][c] = true;
        if (make_pair(r, c) == end) break;
        for (auto [dr, dc] : directions) {
            int nr = r + dr, nc = c + dc;
            if (isValid(nr, nc, maze)) {
                int tentative_g = gScore[r][c] + 1;
                if (tentative_g < gScore[nr][nc]) {
                    gScore[nr][nc] = tentative_g;
                    int fScore = tentative_g + heuristic({ nr, nc }, end);
                    pq.push({ fScore, nr, nc });
                    parent[nr][nc] = { r, c };
                }
            }
        }
    }
    return reconstructPath(end, parent);
}

int main() {
    pair<int, int> start = { 0, 0 };
    pair<int, int> end = { ROWS - 1, COLS - 1 };
    Grid maze = generateMaze(ROWS, COLS, start, end);

    // Show original maze before algorithm is selected
    sf::RenderWindow preWindow(sf::VideoMode({ static_cast<unsigned>(COLS * CELL_SIZE), static_cast<unsigned>(ROWS * CELL_SIZE) }), "Maze Preview");
    vector<vector<bool>> dummyVisited(ROWS, vector<bool>(COLS, false));
    vector<pair<int, int>> dummyPath;
    drawMaze(preWindow, maze, dummyVisited, dummyPath, start, end);

    // Delay and wait for window close
    sf::Clock clock;
    while (preWindow.isOpen()) {
        if (clock.getElapsedTime().asSeconds() > 6.f)
            preWindow.close();
    }

    cout << "Choose Algorithm:\n";
    cout << "1 - Depth-First Search (DFS)\n";
    cout << "2 - Breadth-First Search (BFS)\n";
    cout << "3 - A* Search\n";
    cout << "Enter option (1/2/3): ";

    int selectedAlgorithm = 0;
    while (!(cin >> selectedAlgorithm) || selectedAlgorithm < 1 || selectedAlgorithm > 3) {
        cout << "Invalid input. Enter 1, 2, or 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));
    vector<pair<int, int>> path;

    if (selectedAlgorithm == 1)
        path = solveDFS(maze, visited, start, end);
    else if (selectedAlgorithm == 2)
        path = solveBFS(maze, visited, start, end);
    else if (selectedAlgorithm == 3)
        path = solveAStar(maze, visited, start, end);

    sf::RenderWindow mazeWindow(sf::VideoMode({ static_cast<unsigned>(COLS * CELL_SIZE), static_cast<unsigned>(ROWS * CELL_SIZE) }), "Maze Solver");

    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        drawMaze(mazeWindow, maze, visited, path, start, end);
    }

    return 0;
}
