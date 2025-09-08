#include <bench/ending_bench.hpp>
#include <kernel/timers.hpp>
#include <arch/x86/msr.hpp>
#include <stdint.h>
#include <cstddef>
#include <chrono>
#include <sys/types.h>

/* Right now this only works on x86_64 */
namespace ending_bench {
    static constexpr size_t MAX_ENTRIES = 300000;
    static uint64_t entries[MAX_ENTRIES];
    static size_t entry_count = 0;
    static bool bench_started = false;

    void start_bench(uint64_t duration_ms) {
        entry_count = 0;
        bench_started = true;

        // Set up a periodic timer to poll the RAPL register every millisecond
        /* 1 ms */
        Timers::periodic(std::chrono::milliseconds(1), [](Timers::id_t id) {
//            if (bench_started && entry_count < MAX_ENTRIES) {
//                // Read RAPL package energy status register
//                uint64_t rapl_value = x86::msr::read_msr(x86::msr::MSR_PKG_ENERGY_STATUS);
//                entries[entry_count++] = rapl_value;
//            }
              entry_count++;
            });
    }

    uint64_t end_bench(uint64_t **table) {
        if (!bench_started) {
            *table = nullptr;
            return 0;
        }
        *table = entries;
        bench_started = false;
        return entry_count;
    }
}
