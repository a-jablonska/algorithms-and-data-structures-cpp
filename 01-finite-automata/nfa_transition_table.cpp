// Non-Deterministic Finite Automaton (NFA) using a transition table of state lists
// Pattern: A*(B|C)*AC
//
// Approach: From a single state, reading one character can lead to multiple states
// simultaneously (e.g., S1 --'A'--> {S1, S3}). The algorithm tracks the set of all
// currently active states across steps (NFA simulation).

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Automaton states (row indices in the transition table)
const int S1 = 0; // A* section (start state)
const int S2 = 1; // (B|C)* section
const int S3 = 2; // Read 'A' of the trailing "AC" sequence
const int S4 = 3; // Read 'C' of "AC" (accepting state)

// Maps input characters to column indices in the transition table
int charToIndex(char c) {
    if (c == 'A') return 0;
    if (c == 'B') return 1;
    if (c == 'C') return 2;
    return 3; // Characters outside the pattern alphabet
}

bool matchesPattern(const string& str) {
    // NFA transition table: [current_state][input_char] -> list of possible next states.
    // An empty list {} represents no valid transition.
    const vector<int> nfaTable[4][4] = {
        /*              'A'         'B'     'C'     OTHER */
        /* [0] S1 */ { {S1, S3},   {S2},   {S2},   {} }, // 'A': stay in A* or start trailing "AC"
        /* [1] S2 */ { {S3},       {S2},   {S2},   {} }, // 'B'/'C': loop in (B|C)*; 'A': start "AC"
        /* [2] S3 */ { {},         {},     {S4},   {} }, // Requires 'C' to reach accepting state S4
        /* [3] S4 */ { {},         {},     {},     {} }  // Accepting state: no further characters allowed
    };

    // Tracks which states are currently active (starts exclusively in S1)
    bool current_states[4] = {true, false, false, false};

    for (char ch : str) {
        bool next_states[4] = {false, false, false, false};
        int col = charToIndex(ch);

        // Expand all reachable next states from every currently active state
        for (int i = 0; i < 4; i++) {
            if (current_states[i]) {
                for (int next_state : nfaTable[i][col]) {
                    next_states[next_state] = true;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            current_states[i] = next_states[i];
        }

        // Early exit if no active paths remain
        if (!current_states[0] && !current_states[1] && !current_states[2] && !current_states[3]) {
            return false;
        }
    }

    // Accept if the accepting state S4 is active after reading the entire string
    return current_states[S4];
}

int main() {
    string tests[] = {
        "AAC",    // MATCHED
        "AC",     // MATCHED (zero occurrences of A* and (B|C)*)
        "BBBBC",  // NOT MATCHED (missing trailing "AC")
        "",       // NOT MATCHED (empty string)
        "CBAC",   // MATCHED
        "AABC"    // NOT MATCHED (ends with "BC")
    };

    for (const auto& s : tests) {
        cout << "\"" << s << "\" -> "
             << (matchesPattern(s) ? "MATCHED" : "NOT MATCHED") << "\n";
    }

    return 0;
}
