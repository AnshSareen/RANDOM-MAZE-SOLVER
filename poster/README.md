# Maze Solver – Project Poster Overview

This project presents a visual and algorithmic approach to solving mazes using classic pathfinding techniques. Initially created with educational clarity in mind, it demonstrates how **DFS**, **BFS**, and **A\*** algorithms behave across random mazes.

## 📌 Objective

To develop a maze-solving program that clearly visualizes how different algorithms navigate through mazes, and to compare their efficiency in various scenarios.

## 🧠 Algorithms Used

- **Depth-First Search (DFS)**  
  Explores deeply along a path before backtracking. Fast, but not guaranteed to find the shortest path.

- **Breadth-First Search (BFS)**  
  Explores all neighbors level by level. Guarantees the shortest path in unweighted mazes.

- **A\* Search**  
  Combines actual distance from start and heuristic (Manhattan) to end. Fastest and most optimal in many cases.

## 🧱 Maze Features

- Randomly generated at each run  
- Walls (black), paths (white), visited nodes (red), solution path (blue)  
- Start (green) and End (magenta) marked clearly  
- Multiple valid paths for richer algorithm behavior  

## 🖥️ Visual Output (Poster Highlights)

The poster showcases basic SFML renderings:

- A grid-based maze with thick walls  
- Immediate color-coded output for selected algorithms  
- User input (algorithm choice) via CLI  

## 📊 Performance Displayed

- Side-by-side visualizations of DFS, BFS, and A*  
- Timings and visited node counts to compare efficiency (shown conceptually in the poster)

---

### 📎 Poster Context Note

The visuals and performance comparison in the poster reflect the initial implementation.  
The code in this repository has since been upgraded to **SFML 3.0.0** with a more refined interface and interaction model.

---

### 📌 Note

The UI shown in the poster reflects an earlier, simpler version of the project using basic SFML window drawing.  
The current implementation (available in this repository) uses an enhanced interface fully aligned with **SFML 3.0.0**, offering clearer visuals and a split UI for preview and solving phases.

