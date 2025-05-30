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

1. On running, an **initial maze preview window** opens for 6 seconds.(You can change it according to your preference)
2. You are prompted in the **CLI**:<br>
Choose Algorithm:<br>
1 - Depth-First Search (DFS)<br>
2 - Breadth-First Search (BFS)<br>
3 - A* Search<br>
Enter option (1/2/3):<br>
3. The **final maze solving visualization** window opens.
4. Press **ESC** to close the visualization.

---

## 🧠 Algorithms

### Depth-First Search (DFS)

- Explores deeply along one path until dead-end.
- Fast but may not find shortest path.

### Breadth-First Search (BFS)

- Explores level by level.
- Guarantees shortest path in unweighted graphs.

### A* Search

- Heuristic + cost-based search (Manhattan distance).
- Balances exploration speed and path optimality.

---

## 📁 File Structure

- `main.cpp` – core logic and rendering
- SFML 3.0.0 – must be linked externally

---

## 🙋‍♂️ Credits

Developed as part of a **minor project** using modern SFML.

---

## 💡 Notes

- Maze is generated with multiple paths to allow variation in algorithm decisions.
- UI completely avoids SFML 2.x constructs like `sf::Event`.

