# 2D Autonomous Agent Simulator (C++)

A terminal-based simulation engine developed in C++ that demonstrates Object-Oriented Programming principles, memory management with Smart Pointers, and pathfinding algorithms.

## Overview
This project simulates a grid-based environment where autonomous agents ("Heroes") navigate a maze to interact with objects, avoid traps, and achieve objectives. The simulation runs in the terminal using the **ncurses** library for real-time rendering.

Detailed architecture and logic analysis can be found in the [Project Report](docs/Project_Report.pdf).

## Technical Highlights
Based on the project architecture:
* [cite_start]**Modern C++ Management:** Extensive use of `std::shared_ptr` for memory safety and object lifecycle management[cite: 31, 33].
* [cite_start]**OOP Architecture:** Implementation of **Inheritance** and **Polymorphism** via Abstract Base Classes (`Hero`, `Item`) to manage diverse entities like Traps, Cages, and Keys[cite: 50, 63].
* [cite_start]**AI & Pathfinding:** Agents utilize scanning algorithms (8-neighbor awareness) to detect targets and calculate movement logic dynamically[cite: 56].
* [cite_start]**Game Loop Pattern:** Implements a structured `update()` / `render()` loop for real-time state management[cite: 35].

## Project Structure
* `src/`: Contains all source code (`.cpp`) and header files (`.h`).
* `assets/`: Contains the map configuration files loaded by the `Map` class.
* `docs/`: Contains the full academic report/documentation.
