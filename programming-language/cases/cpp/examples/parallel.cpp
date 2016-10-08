#include <iostream>             // cout, endl
#include <vector>               // vector
#include <random>               // random_device, mt19937, normal_distribution
#include <chrono>               // high_resolution_clock
#include <parallel/algorithm>   // sort, for_each

int main() {

    // http://en.cppreference.com/w/cpp/numeric/random/normal_distribution

    std::random_device rd;
    std::mt19937 gen(rd());

    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d(5, 2);

    std::vector<int> x(9000000, 42);


    for (auto i = 0; i < 10; ++i) {
        // normal version
        auto start = std::chrono::high_resolution_clock::now();

        for_each(x.begin(), x.end(), [&](auto& i){ i = d(gen); });
        sort(x.begin(), x.end());

        auto end = std::chrono::high_resolution_clock::now();
        auto diff = end - start;
        std::cout << "[Normal  ] Time: "
                  << diff.count() << " ticks"
                  << " | "
                  << std::chrono::duration_cast<std::chrono::seconds>(diff).count() << " s" << std::endl;
    }

    for (auto i = 0; i < 10; ++i) {
        // parallel version
        auto start = std::chrono::high_resolution_clock::now();

        __gnu_parallel::for_each(x.begin(), x.end(), [&](auto& i){ i = d(gen); });
        __gnu_parallel::sort(x.begin(), x.end());

        auto end = std::chrono::high_resolution_clock::now();
        auto diff = end - start;
        std::cout << "[Parallel] Time: "
                  << diff.count() << " ticks"
                  << " | "
                  << std::chrono::duration_cast<std::chrono::seconds>(diff).count() << " s" << std::endl;
    }

    return 0;
}
