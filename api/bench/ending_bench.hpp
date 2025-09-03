
#pragma once
#ifndef ENDING_BENCH_HPP
#define ENDING_BENCH_HPP

#include <kernel/timers.hpp>
#include <cstdint>

namespace ending_bench {
    void start_bench();

    /* Returns how many entries were recorded and sets the address pointed to by table
       to the address of the first recorded entry */
    uint64_t end_bench(uint64_t **table);
}

#endif // ENDING_BENCH_HPP