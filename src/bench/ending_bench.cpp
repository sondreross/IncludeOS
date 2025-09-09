#include <bench/ending_bench.hpp>
#include <kernel/timers.hpp>
#include <arch/x86/msr.hpp>
#include <smp>
#include <stdint.h>
#include <cstddef>
#include <chrono>
#include <sys/types.h>
#include <stdio.h>

/* Right now this only works on x86_64 */
namespace ending_bench {
    static constexpr size_t MAX_ENTRIES = 60000;
    static uint64_t entries[MAX_ENTRIES];
    static size_t entry_count = 0;
    static bool bench_started = false;

    void bench_timer() {
        SMP::add_task([]() {
            printf("Setting up timer on CPU %d\n", SMP::cpu_id());
            // Clear previous entries
            entry_count = 0;
            // Create the timer
            auto timer_id = Timers::periodic(std::chrono::milliseconds(10), [](Timers::id_t id) {
                // Timer callback
                if (bench_started && entry_count < MAX_ENTRIES) {
                    entries[entry_count++] = 0xDEADBEEF;
                    printf("CPU %d collected %zu entries\n", SMP::cpu_id(), entry_count);
                }
            });
            printf("Timer created with ID %d on CPU %d\n", timer_id, SMP::cpu_id());
        }, nullptr, SMP::cpu_count() - 1);
        SMP::signal(SMP::cpu_count() - 1);
    }

    void start_bench(uint64_t duration_ms) {
        printf("Starting ending bench for %lu ms\n", duration_ms);
        printf("Current CPU: %d, Total CPUs: %d\n", SMP::cpu_id(), SMP::cpu_count());
        
        // Set bench_started BEFORE scheduling the task
        bench_started = true;
        entry_count = 0;
        
        bench_timer();

        printf("Active timers: %zu\n", Timers::active());
        printf("Bench started, timer should start firing soon...\n");
    }

    uint64_t end_bench(uint64_t **table) {
        printf("Ending ending bench, collected %zu entries\n", entry_count);
        if (!bench_started) {
            *table = nullptr;
            return 0;
        }
        *table = entries;
        bench_started = false;
        return entry_count;
    }
}
