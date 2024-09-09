#include <iostream>
#include <cmath>
#include <chrono>
#include <future>
#include <vector>

const int SIZE = 300; // Size of the game field

// Function to calculate the distance between two points
double distance(int c0, int r0, int c1, int r1) {
    return std::sqrt((c0 - c1) * (c0 - c1) + (r0 - r1) * (r0 - r1));
}

// Function to compute a chunk of the influence map
void compute_influence_chunk(int start_row, int end_row, const int map[SIZE][SIZE], double influence_map[SIZE][SIZE]) {
    for (int c0 = start_row; c0 < end_row; c0++) {
        for (int r0 = 0; r0 < SIZE; r0++) {
            influence_map[c0][r0] = 0.0; // Initialize each point to 0

            for (int c1 = 0; c1 < SIZE; c1++) {
                for (int r1 = 0; r1 < SIZE; r1++) {
                    int I0 = map[c1][r1]; // Get the strength of the unit
                    double d = distance(c0, r0, c1, r1); // Calculate distance

                    // Calculate and add the influence if d is non-zero
                    if (d != 0) {
                        influence_map[c0][r0] += I0 / (1 + d);
                    } else {
                        influence_map[c0][r0] += I0; // Influence from the same square
                    }
                }
            }
        }
    }
}

int main() {
    int map[SIZE][SIZE];              // Game field map
    double influence_map[SIZE][SIZE];  // Influence map

    // Initialize the maps
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = 0;             // Set all units to 0
            influence_map[i][j] = 0.0; // Initialize the influence map to 0
        }
    }

    // Example units
    map[100][100] = 50;  // AI unit with strength 50
    map[150][150] = -30; // Player unit with strength -30
    map[200][50] = 20;   // Another AI unit with strength 20

    auto start = std::chrono::high_resolution_clock::now(); // Start time

    // Define number of threads and rows per thread
    int num_threads = std::thread::hardware_concurrency(); // Number of concurrent threads supported
    int rows_per_thread = SIZE / num_threads;

    // Vector to store futures
    std::vector<std::future<void>> futures;

    // Launch asynchronous tasks
    for (int i = 0; i < num_threads; ++i) {
        int start_row = i * rows_per_thread;
        int end_row = (i == num_threads - 1) ? SIZE : (i + 1) * rows_per_thread;

        futures.push_back(std::async(std::launch::async, compute_influence_chunk, start_row, end_row, std::ref(map), std::ref(influence_map)));
    }

    // Wait for all tasks to finish
    for (auto &fut : futures) {
        fut.get();
    }

    auto end = std::chrono::high_resolution_clock::now(); // End time

    // Calculate the duration
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time with async: " << duration.count() << " seconds" << std::endl;

    return 0;
}
