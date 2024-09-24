#include <iostream>
#include <ctime>

// Let's create a lookup table for all possible 13-bit combinations
const int MAX_MASK = (1 << 13);  // 2^13 possible combinations (13 bits, representing cards 2 to 14)
bool lookup_table[MAX_MASK];      // Lookup table to indicate if a bitmask represents a straight

// Predefined straight bitmasks (same as Part 1)
const int STRAIGHT_MASKS[10] = {
    0b1111100000000, // 10 to Ace
    0b0111110000000, // 9 to King
    0b0011111000000, // 8 to Queen
    0b0001111100000, // 7 to Jack
    0b0000111110000, // 6 to 10
    0b0000011111000, // 5 to 9
    0b0000001111100, // 4 to 8
    0b0000000111110, // 3 to 7
    0b0000000011111, // 2 to 6
    0b1000000001111  // A-2-3-4-5 (Ace low)
};

// Initializing the lookup table
void initialize_lookup_table() {
    // Marking all bitmask indices that correspond to straights
    for (int i = 0; i < 10; ++i) {
        lookup_table[STRAIGHT_MASKS[i]] = true;
    }
}

// Function to generate a bitmask for the hand
inline int get_bitmask(const int* k) {
    int mask = 0;
    for (int i = 0; i < 5; ++i) {
        // Converting card values (2 to 14) to bitmask (1 << (value - 2))
        mask |= (1 << (k[i] - 2));
    }
    return mask;
}

// Optimized straight detection using lookup table
inline int is_straight(const int* k) {
    int mask = get_bitmask(k);
    return lookup_table[mask];  // Return the lookup result (1 if straight, 0 otherwise)
}

int main() {
    initialize_lookup_table();  // Initializing the lookup table before use

    int k0, k1, k2, k3, k4;
    int k[5];
    int straights;
    clock_t t1, t2;

    // Optimized execution time with lookup table
    t1 = clock();
    straights = 0;
    for (k0 = 0; k0 < 52; ++k0) {
        for (k1 = 0; k1 < 52; ++k1) { if (k1 == k0) continue;
            for (k2 = 0; k2 < 52; ++k2) { if (k2 == k0 || k2 == k1) continue;
                for (k3 = 0; k3 < 52; ++k3) { if (k3 == k0 || k3 == k1 || k3 == k2) continue;
                    for (k4 = 0; k4 < 52; ++k4) { if (k4 == k0 || k4 == k1 || k4 == k2 || k4 == k3) continue;

                        // Generate hand values
                        k[0] = (k0 % 13) + 2;
                        k[1] = (k1 % 13) + 2;
                        k[2] = (k2 % 13) + 2;
                        k[3] = (k3 % 13) + 2;
                        k[4] = (k4 % 13) + 2;

                        if (is_straight(k)) {
                            ++straights;
                        }
                    }
                }
            }
        }
    }
    t2 = clock();
    std::cout << "Straights found: " << straights << " (Correct value: 1228800)" << std::endl;
    std::cout << "Time spent: " << (t2 - t1) / (float)CLOCKS_PER_SEC << "s" << std::endl;

    return 0;
}


