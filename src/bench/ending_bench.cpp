#include <bench/ending_bench.hpp>
#include <kernel/timers.hpp>
#include <stdint.h>
#include <cstddef>
#include <chrono>

namespace ending_bench {
    static constexpr size_t MAX_ENTRIES = 300000;
    static uint64_t entries[MAX_ENTRIES];
    static size_t entry_count = 0;
    static bool bench_started = false;

    void start_bench() {
        entry_count = 0;
        bench_started = true;

        // Set up a periodic timer to poll the RAPL register every millisecond
        /* 1 ms */
        Timers::periodic(std::chrono::milliseconds(1), [](Timers::id_t) {
            if (bench_started && entry_count < MAX_ENTRIES) {
                // Replace with actual RAPL register read
                uint64_t rapl_value = read_rapl_register();
                entries[entry_count++] = rapl_value;
            }
            });
        }

    uint64_t end_bench(uint64_t **table) {
        if (!bench_started) {
            *table = nullptr;
            return 0;
        }
        // Simulate recording some entries for demonstration
        for (size_t i = 0; i < MAX_ENTRIES; ++i) {
            entries[i] = i * 100; // Example data
        }
        entry_count = MAX_ENTRIES;
        *table = entries;
        bench_started = false;
        return entry_count;
    }
}