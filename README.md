# Maze Solver – SFML 3.0.0

A visual demonstration of maze-solving algorithms (DFS, BFS, and A*) built using **SFML 3.0.0**. It features random maze generation and a UI window to visualize how different algorithms explore and solve the maze.

---

## 📌 Features

- ✅ Uses **only SFML 3.0.0** – no deprecated or 2.x APIs
- 🎲 Random maze generated every run
- 🧭 Choose from:
  - **DFS (Depth-First Search)**
  - **BFS (Breadth-First Search)**
  - **A* Search**
- 🖼️ Visual representation of:
  - Walls and free paths
  - Visited cells
  - Final path from start to end
- ⌨️ CLI selection with separate UI windows for input preview and final output

---

## 🧱 Maze Representation

- Black: Wall
- White: Free path
- Green: Start
- Magenta: End
- Red (semi-transparent): Visited
- Blue: Final path

---

## 🛠️ Build Instructions

1. Install [SFML 3.0.0](https://www.sfml-dev.org/download.php)
2. Link SFML include and lib directories in your C++ compiler (Visual Studio recommended)
3. Compile with `sfml-graphics`, `sfml-window`, and `sfml-system` linked

### Example (Visual Studio):

- C++ > General > Additional Include Directories → `SFML-3.0.0/include`
- Linker > Input > Additional Dependencies:
  - `sfml-graphics.lib`
  - `sfml-window.lib`
  - `sfml-system.lib`

---

## ▶️ How to Run

1. On running, an **initial maze preview window** opens for 3 seconds.
2. You are prompted in the **CLI**:
