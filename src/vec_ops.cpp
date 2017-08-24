#include "vec_ops.h"
#include <random>
#include <chrono>
#include <iostream>

namespace vector_ops{
    std::vector<double> randomVector(int size, double mu, double stddev) {
        std::normal_distribution<double> generator = std::normal_distribution<double>(mu, stddev);
        std::default_random_engine seed_val(std::chrono::system_clock::now().time_since_epoch().count());
        std::vector<double> r_vec;
        for (int i=0; i<size; i++) {
            r_vec.push_back(generator(seed_val));
        }
        return r_vec;
    }
}
