// Epsilon-NFA (NFA with empty transitions) using a graph adjacency list
// Pattern: A*(B|C)*AC
//
// Approach: Represents the automaton as a directed graph supporting free
// epsilon-transitions ('\0'). Uses recursive Depth-First Search (DFS) to compute
// epsilon-closures and std::set to maintain unique active states.

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

const char EPSILON = '\0'; // Represents a free transition without consuming input

struct Edge {
    char letter;
    int to_state;
};

// Graph adjacency list representing states S0..S6
const vector<vector<Edge>> nfaGraph = {
    /* S0 */ { {'A', 1}, {EPSILON, 2} },          // Start: enter A* loop or bypass to (B|C)*
    /* S1 */ { {EPSILON, 0} },                    // Loop back for A*
    /* S2 */ { {'B', 3}, {'C', 3}, {EPSILON, 4} },// Enter (B|C)* loop or proceed to "AC"
    /* S3 */ { {EPSILON, 2} },                    // Loop back for (B|C)*
    /* S4 */ { {'A', 5} },                        // Match 'A' of trailing "AC"
    /* S5 */ { {'C', 6} },                        // Match 'C' of trailing "AC"
    /* S6 */ { }                                  // Accepting state (no outgoing edges)
};

// Recursively adds all states reachable via epsilon-transitions (DFS)
void addEpsilonClosure(int state, set<int>& current_states) {
    // Prevent infinite loops on epsilon cycles
    if (current_states.count(state)) return;

    current_states.insert(state);

    for (const auto& edge : nfaGraph[state]) {
        if (edge.letter == EPSILON) {
            addEpsilonClosure(edge.to_state, current_states);
        }
    }
}

// Returns the set of states reachable by consuming a single character c
set<int> moveByLetter(const set<int>& current_states, char c) {
    set<int> next_states;

    for (int state : current_states) {
        for (const auto& edge : nfaGraph[state]) {
            if (edge.letter == c) {
                next_states.insert(edge.to_state);
            }
        }
    }

    return next_states;
}

bool matchesNFA(const string& str) {
    set<int> current_states;

    // Initialize with the epsilon-closure of the start state S0
    addEpsilonClosure(0, current_states);

    for (char c : str) {
        // Step 1: Transition on the input character
        set<int> after_letter = moveByLetter(current_states, c);

        // Step 2: Compute epsilon-closure from all newly reached states
        current_states.clear();
        for (int state : after_letter) {
            addEpsilonClosure(state, current_states);
        }

        // Early exit if no valid paths remain
        if (current_states.empty()) return false;
    }

    // Accept if the accepting state S6 is in the final active set
    return current_states.count(6) > 0;
}

int main() {
    string tests[] = {
        "AC",       // MATCHED (epsilon transitions bypass A* and (B|C)*)
        "AAC",      // MATCHED
        "BAC",      // MATCHED
        "BCAAC",    // NOT MATCHED
        "ACAC",     // MATCHED
        "ADAC",     // NOT MATCHED
        "BCBBCAC"   // MATCHED
    };

    for (const auto& s : tests) {
        cout << "\"" << s << "\" -> "
             << (matchesNFA(s) ? "MATCHED" : "NOT MATCHED") << "\n";
    }

    return 0;
}
