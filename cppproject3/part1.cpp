/*
#include <algorithm>
#include <iostream>

void sort_cards(int* k) {
    std::sort(k, k + 5);  // Sort the array of 5 elements
}

bool is_consecutive(int* k) {
    for (int i = 0; i < 4; ++i) {
        if (k[i + 1] != k[i] + 1) {
            return false;
        }
    }
    return true;
}

inline int is_straight(int* k) {
    // Sort the array first
    sort_cards(k);

    // Check for the regular straight
    if (is_consecutive(k)) {
        return 1;
    }

    // Special case: Ace can be 1
    // If the sorted cards are 2, 3, 4, 5, 14, this forms a straight with Ace as 1
    if (k[0] == 2 && k[1] == 3 && k[2] == 4 && k[3] == 5 && k[4] == 14) {
        return 1;
    }

    return 0;
}
*/
//The original version required sorting the card values. This new version does everything in constant time.
