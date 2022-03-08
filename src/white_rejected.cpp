// Show figures which are rejected due to their white-connexity.

// Using preprocessor to configure N, B and W.
#ifdef N
constexpr int N_ = N;
#undef N
#else
constexpr int N_ = 4;
#endif

#ifdef B
constexpr int B_ = B;
#undef B
#else
constexpr int B_ = 8;
#endif


#ifdef W
constexpr int W_ = W;
#undef W
#else
constexpr int W_ = 8;
#endif

#include <cstdio>
#include "../MartinAlgoOpti.hpp"

int main() {
    // We will advance two Martin algorithm, one with white-connexity and
    // the other without. We iterate on both and check which figures
    // are generated by 'martin_all' which are skipped by 'martin_white'.
    MartinAlgoOpti<N_, B_, 0> martin_all;
    MartinAlgoOpti<N_, B_, W_> martin_white;

    martin_all.Init();
    martin_white.Init();

    char repr[martin_all.REPR_SIZE];
    int nb_diff = 0;

    do {
        // Go to next white figure.
        martin_white.NextStep();

        for (;;) {
            martin_all.NextStep();
            if (std::memcmp(martin_all.grid.data(), martin_white.grid.data(), sizeof(martin_all.grid)) == 0)
                break; // Found the next white figure.
            // This figure was skipped by 'martin_white', print it.
            martin_all.GetRepr(repr);
            // Draw only non-empty lines.
            std::printf("%d. (size=%d)\n", ++nb_diff, martin_all.level+1);
            for (int i = 0; repr[i] != '\0'; i += martin_all.WIDTH + 1) {
                if (std::memchr(&repr[i], 'X', martin_all.WIDTH) != nullptr)
                    std::printf("%.*s\n", martin_all.WIDTH, &repr[i]);
            }
        }
    } while (martin_white.level > 0);

    std::printf("Total %d-black-connected figures (size <= %d) due to %d-white-connexity: %d\n", B_, N_, W_, nb_diff);
}