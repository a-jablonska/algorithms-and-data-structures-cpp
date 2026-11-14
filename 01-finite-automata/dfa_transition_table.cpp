// Deterministic Finite Automaton (DFA) using a 2D transition table
// Pattern: A*(B|C)*B
//
// Approach: Each cell transitionTable[state][input] defines exactly one next state.
// An explicit TRAP state allows immediate rejection of invalid inputs.

#include <iostream>
#include <string>

using namespace std;

enum State {
    S0 = 0,   // Start state: zero or more 'A's read so far
    S1 = 1,   // Last character read was 'B' (accepting state)
    S2 = 2,   // Last character read was 'C'
    TRAP = 3  // Dead state: input cannot match the pattern
};

// Maps input characters to column indices in the transition table
int charToIndex(char c) {
    if (c == 'A') return 0;
    if (c == 'B') return 1;
    if (c == 'C') return 2;
    return 3; // Characters outside the pattern alphabet
}

bool matchesPatternTable(const string& str) {
    // Transition table: [current_state][input_char] -> next_state
    const State transitionTable[4][4] = {
        /*           'A'    'B'    'C'    OTHER */
        /* S0 */   { S0,    S1,    S2,    TRAP },
        /* S1 */   { TRAP,  S1,    S2,    TRAP },
        /* S2 */   { TRAP,  S1,    S2,    TRAP },
        /* TRAP */ { TRAP,  TRAP,  TRAP,  TRAP }
    };

    State currentState = S0;

    for (char ch : str) {
        currentState = transitionTable[currentState][charToIndex(ch)];

        // Early exit if the automaton enters the dead state
        if (currentState == TRAP) {
            return false;
        }
    }

    // Accept only if the string ends on 'B' (state S1)
    return currentState == S1;
}

int main() {
    string tests[] = {
        "B",        // MATCHED
        "AAAB",     // MATCHED
        "BCBCB",    // MATCHED
        "AABCCCB",  // MATCHED
        "",         // NOT MATCHED (empty string)
        "AAA",      // NOT MATCHED (missing trailing 'B')
        "BCBC",     // NOT MATCHED (ends with 'C')
        "BA",       // NOT MATCHED ('A' cannot appear after 'B')
        "ABXD"      // NOT MATCHED (invalid characters)
    };

    for (const auto& s : tests) {
        cout << "\"" << s << "\" -> "
             << (matchesPatternTable(s) ? "MATCHED" : "NOT MATCHED") << "\n";
    }

    return 0;
}
