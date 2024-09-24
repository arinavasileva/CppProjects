//Optimized lookup table version 

#include <iostream>
#include <ctime>

// Lookup table for identifying quads and full house
const int MAX_MASK = (1 << 13);  // 2^13 combinations for 13 possible card values
bool quads_fullhouse_lookup[MAX_MASK];

// Initializing the lookup table
void initialize_quads_fullhouse_lookup() {
    // Iterating through all possible 13-bit combinations
    for (int mask = 0; mask < MAX_MASK; ++mask) {
        int count[13] = {0};  // Array to count occurrences of each card value

        // Counting the bits set to 1 in the mask
        for (int i = 0; i < 13; ++i) {
            if (mask & (1 << i)) {
                count[i]++;
            }
        }

        bool has_four_of_a_kind = false;
        bool has_three_of_a_kind = false;
        bool has_pair = false;
        int distinct_values = 0;

        // Checking the bit counts
        for (int i = 0; i < 13; ++i) {
            if (count[i] == 4) {
                has_four_of_a_kind = true;
            }
            if (count[i] == 3) {
                has_three_of_a_kind = true;
            }
            if (count[i] == 2) {
                has_pair = true;
            }
            if (count[i] > 0) {
                distinct_values++;
            }
        }

        // Marking the lookup table for quads or full house
        if (has_four_of_a_kind || (has_three_of_a_kind && has_pair)) {
            quads_fullhouse_lookup[mask] = true;
        }
    }
}

// Function to generate bitmask for the hand
inline int get_bitmask(const int* k) {
    int mask = 0;
    for (int i = 0; i < 5; ++i) {
        mask |= (1 << (k[i] - 2));
    }
    return mask;
}

// Optimized quads or full house detection using lookup table
inline bool is_quadsorfullhouse_lookup(const int* k) {
    int mask = get_bitmask(k);
    return quads_fullhouse_lookup[mask];  // Using the lookup table
}

int main() {
    initialize_quads_fullhouse_lookup();  // Initializing the lookup table

    int k0, k1, k2, k3, k4;
    int k[5];
    int hands_detected;
    clock_t t1, t2;

    // Optimized detection with lookup table
    t1 = clock();
    hands_detected = 0;
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

                        if (is_quadsorfullhouse_lookup(k)) {
                            ++hands_detected;
                        }
                    }
                }
            }
        }
    }
    t2 = clock();
    std::cout << "Hands detected (quads or full house, lookup): " << hands_detected << std::endl;
    std::cout << "Time spent: " << (t2 - t1) / (float)CLOCKS_PER_SEC << "s" << std::endl;

    return 0;
}


