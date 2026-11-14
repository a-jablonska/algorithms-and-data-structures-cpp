# Finite Automata & Pattern Matching in C++

Implementations of deterministic and non-deterministic finite automata (DFA, NFA, and ε-NFA) built from scratch in C++ without external regex libraries.

## Overview of Implementations

1. **Deterministic Finite Automaton (`dfa_transition_table.cpp`)**
   * **Pattern:** `A*(B|C)*B`
   * **Approach:** 2D static transition table (`State[4][4]`) with an explicit `TRAP` state for early rejection of invalid inputs.

2. **Non-Deterministic Finite Automaton (`nfa_transition_table.cpp`)**
   * **Pattern:** `A*(B|C)*AC`
   * **Approach:** Transition table storing dynamic state lists (`std::vector<int>`) per cell and tracking active states simultaneously across steps.

3. **Epsilon-NFA (`epsilon_nfa_graph.cpp`)**
   * **Pattern:** `A*(B|C)*AC`
   * **Approach:** Graph adjacency list (`std::vector<std::vector<Edge>>`) supporting ε-transitions (`'\0'`). Uses recursive Depth-First Search (DFS) for ε-closure computation and `std::set` to track unique active states.

## Technologies & Concepts
* **Language:** C++ (C++11 or newer)
* **STL Containers:** `std::vector`, `std::set`, `std::string`
* **Algorithms:** Finite State Machines, Graph Traversal (DFS), ε-closure

## How to Compile and Run

Compile any of the source files using `g++`:

```bash
g++ -std=c++17 -O2 epsilon_nfa_graph.cpp -o epsilon_nfa
./epsilon_nfa
