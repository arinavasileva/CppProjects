//Regural function = Direct Approach

#include <iostream>
#include <ctime>
#include <unordered_map>

// Function to check if the hand is four of a kind or full house
inline bool is_quadsorfullhouse(const int* k) {
    // Counting occurrences of each card value
    std::unordered_map<int, int> value_count;
    for (int i = 0; i < 5; ++i) {
        value_count[k[i]]++;
    }

    bool has_four_of_a_kind = false;
    bool has_three_of_a_kind = false;
    bool has_pair = false;

    // Checking the counts to see if it's quads or full house
    for (const auto& pair : value_count) {
        if (pair.second == 4) {
            has_four_of_a_kind = true;
        }
        if (pair.second == 3) {
            has_three_of_a_kind = true;
        }
        if (pair.second == 2) {
            has_pair = true;
        }
    }

    // Returning true if the hand is quads or full house
    return has_four_of_a_kind || (has_three_of_a_kind && has_pair);
}

int main() {
    int k0, k1, k2, k3, k4;
    int k[5];
    int hands_detected;
    clock_t t1, t2;

    // Direct method for detecting quads and full houses
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

                        if (is_quadsorfullhouse(k)) {
                            ++hands_detected;
                        }
                    }
                }
            }
        }
    }
    t2 = clock();
    std::cout << "Hands detected (quads or full house): " << hands_detected << std::endl;
    std::cout << "Time spent: " << (t2 - t1) / (float)CLOCKS_PER_SEC << "s" << std::endl;

    return 0;
}
