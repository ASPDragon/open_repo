#pragma once

#include <vector>
#include <cmath>
#include <numeric>
#include "Insert_sorted.hpp"

double DigitalSignalErr(const std::vector<double>& analog_signal) {
    auto cut = [](const auto& accum, const auto& element) {
        return accum + pow(element - floor(element), 2);
    };
    return ::std::accumulate(analog_signal.begin(), analog_signal.end(), 0.0, cut);
}
