#include "../MartinAlgo.hpp"

#include <cstdio>
#include <vector>

// Objective : enumerating all 4-connected figures of sizes <= 8
// and verifying if the result matches what is already known.

int main() {
    // https://oeis.org/A001168 (except for size 0, which do not matter)
    constexpr int expected[] = { 0, 1, 2, 6, 19, 63, 216, 760, 2725, 9910, 36446, 135268, 505861, 1903890, 7204874, 27394666, 104592937, };
    constexpr int max_size = std::size(expected)-1;
    
    int result[max_size+1] = { 0 };

    MartinAlgo martin;
    martin.Init(max_size);
    for(;;) {
        if (martin.level == max_size || martin.next_free == martin.candidates.size()) {
            bool could_pop = martin.Pop();
            if (!could_pop)
                break; // We could not pop, end of enumeration.
        } else {
            // Push next free candidate.
            Coordinate coord = martin.Push(martin.next_free);
            // Add its 4-connected neighbours.
            martin.AddCandidates4(coord);
            // Count the new figure.
            ++result[martin.level];
        }
    }

    int total = 0;
    for (int i = 1; i <= max_size; ++i) {
        std::printf("Found %10d figures of size %3d (expected %10d)\n", result[i], i, expected[i]);
        total += result[i];
    }
    std::printf("Generated %d figures in total.\n", total);

    return 0;
}