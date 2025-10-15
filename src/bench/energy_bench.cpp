#include <os>
#include <delegate>
#include <arch/x86/cpu.hpp>
#include <cstdint>

#include <bench/energy_bench.hpp>

namespace energy_bench {

static inline uint64_t rdtsc_start() {
    uint32_t lo, hi;
    asm volatile (
        "cpuid\n\t"
        "rdtsc\n\t"
        : "=a"(lo), "=d"(hi)
        :: "%rbx", "%rcx"
    );
    return ((uint64_t)hi << 32) | lo;
}

static inline uint64_t rdtsc_end() {
    uint32_t lo, hi;
    asm volatile (
        "rdtsc\n\t"
        "lfence\n\t"
        : "=a"(lo), "=d"(hi)
        :
        : "memory"
    );
    return ((uint64_t)hi << 32) | lo;
}

double get_rapl_units() {
    uint64_t power_unit_msr = x86::CPU::read_msr(MSR_RAPL_POWER_UNIT);
    uint8_t energy_unit_bits = (power_unit_msr >> 8) & 0x1F;  // Bits 12:8
    
    // Energy unit: 1/2^ESU joules per count
    double energy_unit_joules = 1.0 / (1 << energy_unit_bits);

    return energy_unit_joules;
}


uint64_t bench_function_single(delegate<void()> func) 
{
    double energy_unit = get_rapl_units();
    uint64_t raw_before = x86::CPU::read_msr(MSR_PKG_ENERGY_STATUS);

    func();

    uint64_t raw_after = x86::CPU::read_msr(MSR_PKG_ENERGY_STATUS);
    
    // Calculate difference first, then convert to microjoules
    uint64_t raw_diff = raw_after - raw_before;
    //TODO: Handle wrap-around
    uint64_t energy_microjoules = static_cast<uint64_t>(raw_diff * energy_unit * 1000000.0);
    return energy_microjoules;
}

energy_result bench_function(delegate<void()> func, uint32_t domains) 
{
    double energy_unit = get_rapl_units();
    energy_result result;
    
    // Store raw "before" values
    uint64_t pkg_before = 0, dram_before = 0, pp0_before = 0, pp1_before = 0;
    
    if (domains & PKG) {
        pkg_before = x86::CPU::read_msr(MSR_PKG_ENERGY_STATUS);
        result.measured_domains |= PKG;
    }
    if (domains & DRAM) {
        dram_before = x86::CPU::read_msr(MSR_DRAM_ENERGY_STATUS);
        result.measured_domains |= DRAM;
    }
    if (domains & PP0) {
        pp0_before = x86::CPU::read_msr(MSR_PP0_ENERGY_STATUS);
        result.measured_domains |= PP0;
    }
    if (domains & PP1) {
        pp1_before = x86::CPU::read_msr(MSR_PP1_ENERGY_STATUS);
        result.measured_domains |= PP1;
    }
    
    // Capture start time (CPU cycles) using serialized RDTSC
    volatile uint64_t start_cycles = rdtsc_start();
    result.cycles_start = start_cycles;
    
    func();
    
    // Capture end time (CPU cycles) using serialized RDTSCP
    volatile uint64_t end_cycles = rdtsc_end();
    result.cycles_end = end_cycles;
    result.cycles_elapsed = result.cycles_end - result.cycles_start;
    
    // Calculate differences and convert to microjoules
    if (domains & PKG) {
        uint64_t pkg_after = x86::CPU::read_msr(MSR_PKG_ENERGY_STATUS);
        uint64_t raw_diff = pkg_after - pkg_before;
        result.pkg_microjoules = static_cast<uint64_t>(raw_diff * energy_unit * 1000000.0);
    }
    if (domains & DRAM) {
        uint64_t dram_after = x86::CPU::read_msr(MSR_DRAM_ENERGY_STATUS);
        uint64_t raw_diff = dram_after - dram_before;
        result.dram_microjoules = static_cast<uint64_t>(raw_diff * energy_unit * 1000000.0);
    }
    if (domains & PP0) {
        uint64_t pp0_after = x86::CPU::read_msr(MSR_PP0_ENERGY_STATUS);
        uint64_t raw_diff = pp0_after - pp0_before;
        result.pp0_microjoules = static_cast<uint64_t>(raw_diff * energy_unit * 1000000.0);
    }
    if (domains & PP1) {
        uint64_t pp1_after = x86::CPU::read_msr(MSR_PP1_ENERGY_STATUS);
        uint64_t raw_diff = pp1_after - pp1_before;
        result.pp1_microjoules = static_cast<uint64_t>(raw_diff * energy_unit * 1000000.0);
    }
    
    return result;
}

} // namespace energy_bench