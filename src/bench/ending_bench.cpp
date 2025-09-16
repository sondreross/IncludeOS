#include <os>
#include <delegate>
#include <arch/x86/cpu.hpp>
#include <cstdint>
#include <iostream>

#include <bench/energy_bench_function.hpp>

namespace energy_bench {

void bench_function(delegate<void()> func) 
{
  std::uint64_t energy_before = x86::CPU::read_msr(MSR_PKG_ENERGY_STATUS);
  func();
  std::uint64_t energy_after = x86::CPU::read_msr(MSR_PKG_ENERGY_STATUS);
  std::cout << "Energy used: " << (energy_after - energy_before) << std::endl;
}

} // namespace energy_bench