#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <utility> // for std::pair

const int SIZE = 300; // Size of the game field

// Function to calculate the distance between two points
double distance(int c0, int r0, int c1, int r1) {
    return std::sqrt((c0 - c1) * (c0 - c1) + (r0 - r1) * (r0 - r1));
}

int main() {
    int map[SIZE][SIZE];  // Game field map
    double influence_map[SIZE][SIZE];  // Influence map

    // Initializing the maps
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = 0;             // Set all units to 0
            influence_map[i][j] = 0.0; // Initializing the influence map to 0
        }
    }

    // Example units
    map[100][100] = 50;   // AI unit with strength 50
    map[150][150] = -30;  // Player unit with strength -30
    map[200][50] = 20;    // Another AI unit with strength 20

    // Find all the positions with units
    std::vector<std::pair<int, int>> unit_positions;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] != 0) {
                unit_positions.emplace_back(i, j); // Store the positions of non-zero units
            }
        }
    }

    auto start = std::chrono::high_resolution_clock::now();  // Start time

    // Computing the influence map using the better serial algorithm
    for (const auto& unit_pos : unit_positions) {
        int c1 = unit_pos.first;
        int r1 = unit_pos.second;
        int I0 = map[c1][r1];

        // Calculating the influence of this unit on every other cell
        for (int c0 = 0; c0 < SIZE; c0++) {
            for (int r0 = 0; r0 < SIZE; r0++) {
                double d = distance(c0, r0, c1, r1);  // Calculating distance

                // Calculating and adding the influence
                if (d != 0) {
                    influence_map[c0][r0] += I0 / (1 + d);
                } else {
                    influence_map[c0][r0] += I0;  // Influence from the same square
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();  // End time

    // Calculating the duration
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time with better serial algorithm: " << duration.count() << " seconds" << std::endl; // After completing part 5

    return 0;
}

/* Question 1: Is the counter value COLS * ROWS when the count is finished? If not, why not?

The counter might not be COLS * ROWS because multiple threads are updating the ready_count simultaneously,
causing some updates to be lost. This happens due to threads competing to modify the same variable without coordination,
leading to an incorrect count.

Question 2: Measure the execution time with and without locking. What could be the difference?

With Locking Enabled: Higher execution time due to lock contention.
Without Locking Enabled: Lower execution time but incorrect results.

Question 3: hen define a parallel execution for the for_each algorithm std::execution::par_unseq. How much did the execution time drop?

In practice, the execution time should drop extremely low,
as the algorithm can now utilize multiple cores to process
different parts of the map concurrently.


/*
