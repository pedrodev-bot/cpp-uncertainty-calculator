#pragma once
#include <boost/multiprecision/cpp_dec_float.hpp>

// Type aliases
using big_float = boost::multiprecision::cpp_dec_float_50;

/** Stores measurements */
struct Measurement {
    std::string nome;
    std::vector<big_float> distance;
    std::vector<big_float> mass;
    std::vector<big_float> time;
    std::vector<big_float> averageVelocity;
    std::vector<big_float> linearMomentum;
};