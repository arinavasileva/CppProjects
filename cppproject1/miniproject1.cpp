#include <iostream>
#include <cmath>
#include <chrono> // for measuring execution time

const int SIZE = 300; // size of the game field

// calculating the distance between two points
double distance(int c0, int r0, int c1, int r1) {
    return std::sqrt((c0 - c1) * (c0 - c1) + (r0 - r1) * (r0 - r1));
}

int main() {
    int map[SIZE][SIZE];             // game field map
    double influence_map[SIZE][SIZE]; // influence map

    // Initialize the maps
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = 0;             // setting all units to 0
            influence_map[i][j] = 0.0; // initializing the influence map to 0
        }
    }

    // example units
    map[100][100] = 50;  // AI unit with strength 50
    map[150][150] = -30; // player unit with strength -30
    map[200][50] = 20;   // another AI unit with strength 20

    auto start = std::chrono::high_resolution_clock::now(); // start time

    // computation of the influence map
    for (int c0 = 0; c0 < SIZE; c0++) {
        for (int r0 = 0; r0 < SIZE; r0++) {
            influence_map[c0][r0] = 0.0; // initializing each point to 0

            for (int c1 = 0; c1 < SIZE; c1++) {
                for (int r1 = 0; r1 < SIZE; r1++) {
                    int I0 = map[c1][r1]; // the strength of the unit
                    double d = distance(c0, r0, c1, r1); // distance

                    // calculating and adding the influence if d is non-zero
                    if (d != 0) {
                        influence_map[c0][r0] += I0 / (1 + d);
                    } else {
                        influence_map[c0][r0] += I0; // influence from the same square
                    }
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // end time

    // the duration
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
