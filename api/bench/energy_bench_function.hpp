#pragma once
#ifndef ENERGY_BENCH_FUNCTION_HPP
#define ENERGY_BENCH_FUNCTION_HPP

#include <delegate>

namespace energy_bench {
    void bench_function(delegate<void()> func);
}


#endif