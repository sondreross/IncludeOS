#pragma once
#ifndef ENERGY_BENCH_HPP
#define ENERGY_BENCH_HPP

#include <delegate>
#include <cstdint>

namespace energy_bench {
    
    // RAPL domain flags (can be combined with |)
    enum rapl_flags : uint8_t {
        PKG  = 1 << 0,  // Package (CPU + integrated GPU)
        DRAM = 1 << 1,  // Memory
        PP0  = 1 << 2,  // Core (CPU cores only)
        PP1  = 1 << 3,  // Uncore (integrated GPU)
        
        // Common combinations
        PKG_DRAM = PKG | DRAM,
        ALL = PKG | DRAM | PP0 | PP1
    };
    
    struct energy_result {
        uint64_t pkg_microjoules = 0;
        uint64_t dram_microjoules = 0;
        uint64_t pp0_microjoules = 0;
        uint64_t pp1_microjoules = 0;
        uint32_t measured_domains = 0;  // Which domains were actually measured
        
        // Convenience methods
        double pkg_joules() const { return pkg_microjoules / 1'000'000.0; }
        double dram_joules() const { return dram_microjoules / 1'000'000.0; }
        double pp0_joules() const { return pp0_microjoules / 1'000'000.0; }
        double pp1_joules() const { return pp1_microjoules / 1'000'000.0; }
        
        double total_joules() const { 
            return (pkg_microjoules + dram_microjoules + pp0_microjoules + pp1_microjoules) / 1'000'000.0; 
        }
        
        bool has_domain(rapl_flags domain) const { 
            return (measured_domains & domain) != 0; 
        }
    };
    
    // Default: measure PKG and DRAM
    energy_result bench_function(delegate<void()> func, uint32_t domains = PKG);
    
    // Legacy single-value version (returns PKG energy only)
    uint64_t bench_function_single(delegate<void()> func);
}

#endif // ENERGY_BENCH_HPP