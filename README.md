# Custom NFA-DFA Implementation and Visualizer

This project implements NFA (Non-deterministic Finite Automaton) and DFA (Deterministic Finite Automaton) classes from scratch in C++. It provides functionality for:
1. Checking if a string is acceptable by an NFA.
2. Creating the equivalent DFA from an NFA.
3. Visualizing the NFA.
4. Checking if a string is acceptable by a DFA.
5. Simplifying the DFA.
6. Visualizing the DFA.

## Features
- Custom implementation of NFA and DFA with transition functions and state management.
- NFA to DFA conversion and DFA minimization.
- Graphical visualization of automata using the WinBGIm graphics library.

## Requirements
- C++ compiler (e.g., g++).
- WinBGIm graphics library for visualization. Follow the installation instructions [here](http://winbgim.codecutter.org/) to set up the necessary library.

## How to Compile and Run
1. Clone the repository, compile and run the main.cpp file.


## Usage

Once you run the program, you will be prompted to input the following (regarded to your NFA):

1. **Q**: A set of states (comma-separated).
2. **Sigma**: The input alphabet.
3. **Final States**: A set of final states (comma-separated).
4. **Transition Functions**: The number of transitions followed by transitions in the format `(state1, input, state2)`.

### Menu Options

After setting up the NFA, the program will display a menu with the following options:

- `0- Exit`: Exit the program.
- `1- is acc by NFA`: Check if a string is accepted by the NFA.
- `2- create equi DFA`: Create an equivalent DFA from the NFA.
- `3- show schematic NFA`: Visualize the NFA as a graph.
- `4- is acc by DFA`: Check if a string is accepted by the DFA (after creating it).
- `5- make simple DFA`: Simplify (minimize) the DFA.
- `6- show schematic DFA`: Visualize the DFA as a graph.

### Example Input

1. Enter states: `{q0,q1,q2}`
2. Enter input alphabet: `{a,b}`
3. Enter final states: `{q2}`
4. Enter the number of transitions: `3`
   - Transition 1: `q0,a,q1`
   - Transition 2: `q1,b,q2`
   - Transition 3: `q2,a,q0`

Then, follow the menu prompts to run the automata operations.

