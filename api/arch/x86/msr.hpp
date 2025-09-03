// -*-C++-*-
// This file is a part of the IncludeOS unikernel - www.includeos.org
//
// Copyright 2025 Oslo and Akershus University College of Applied Sciences
// and Alfred Bratterud
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef X86_MSR_HPP
#define X86_MSR_HPP

#include <cstdint>

// Model Specific Register (MSR) addresses for x86 processors

namespace x86 {
namespace msr {

// RAPL (Running Average Power Limit) MSRs
constexpr uint32_t MSR_RAPL_POWER_UNIT         = 0x606;
constexpr uint32_t MSR_PKG_POWER_LIMIT         = 0x610;
constexpr uint32_t MSR_PKG_ENERGY_STATUS       = 0x611;
constexpr uint32_t MSR_PKG_POWER_INFO          = 0x614;
constexpr uint32_t MSR_DRAM_POWER_LIMIT        = 0x618;
constexpr uint32_t MSR_DRAM_ENERGY_STATUS      = 0x619;
constexpr uint32_t MSR_DRAM_PERF_STATUS        = 0x61B;
constexpr uint32_t MSR_DRAM_POWER_INFO         = 0x61C;
constexpr uint32_t MSR_PP0_POWER_LIMIT         = 0x638;
constexpr uint32_t MSR_PP0_ENERGY_STATUS       = 0x639;
constexpr uint32_t MSR_PP0_POLICY              = 0x63A;
constexpr uint32_t MSR_PP0_PERF_STATUS         = 0x63B;
constexpr uint32_t MSR_PP1_POWER_LIMIT         = 0x640;
constexpr uint32_t MSR_PP1_ENERGY_STATUS       = 0x641;
constexpr uint32_t MSR_PP1_POLICY              = 0x642;

// Time Stamp Counter
constexpr uint32_t MSR_TSC                     = 0x10;
constexpr uint32_t MSR_IA32_TSC_DEADLINE       = 0x6E0;

// Performance Monitoring
constexpr uint32_t MSR_IA32_PERF_GLOBAL_STATUS = 0x38E;
constexpr uint32_t MSR_IA32_PERF_GLOBAL_CTRL   = 0x38F;
constexpr uint32_t MSR_IA32_PERF_GLOBAL_OVF_CTRL = 0x390;
constexpr uint32_t MSR_IA32_PERFCTR0           = 0xC1;
constexpr uint32_t MSR_IA32_PERFCTR1           = 0xC2;
constexpr uint32_t MSR_IA32_PERFEVTSEL0        = 0x186;
constexpr uint32_t MSR_IA32_PERFEVTSEL1        = 0x187;

// Feature Control
constexpr uint32_t MSR_IA32_FEATURE_CONTROL    = 0x3A;
constexpr uint32_t MSR_IA32_VMX_BASIC          = 0x480;
constexpr uint32_t MSR_IA32_VMX_PINBASED_CTLS  = 0x481;
constexpr uint32_t MSR_IA32_VMX_PROCBASED_CTLS = 0x482;

// Temperature and Thermal
constexpr uint32_t MSR_IA32_THERM_STATUS       = 0x19C;
constexpr uint32_t MSR_IA32_TEMP_TARGET        = 0x1A2;
constexpr uint32_t MSR_TEMPERATURE_TARGET      = 0x1A2;

// Platform Info
constexpr uint32_t MSR_PLATFORM_INFO           = 0xCE;
constexpr uint32_t MSR_IA32_MISC_ENABLE        = 0x1A0;

// CPU Frequency
constexpr uint32_t MSR_IA32_PERF_STATUS        = 0x198;
constexpr uint32_t MSR_IA32_PERF_CTL           = 0x199;

// APIC
constexpr uint32_t MSR_IA32_APIC_BASE          = 0x1B;
constexpr uint32_t MSR_X2APIC_APICID           = 0x802;
constexpr uint32_t MSR_X2APIC_VERSION          = 0x803;
constexpr uint32_t MSR_X2APIC_TPR              = 0x808;
constexpr uint32_t MSR_X2APIC_EOI              = 0x80B;
constexpr uint32_t MSR_X2APIC_LDR              = 0x80D;
constexpr uint32_t MSR_X2APIC_SIVR             = 0x80F;
constexpr uint32_t MSR_X2APIC_ISR0             = 0x810;
constexpr uint32_t MSR_X2APIC_TMR0             = 0x818;
constexpr uint32_t MSR_X2APIC_IRR0             = 0x820;
constexpr uint32_t MSR_X2APIC_ESR              = 0x828;
constexpr uint32_t MSR_X2APIC_LVT_CMCI         = 0x82F;
constexpr uint32_t MSR_X2APIC_ICR              = 0x830;
constexpr uint32_t MSR_X2APIC_LVT_TIMER        = 0x832;
constexpr uint32_t MSR_X2APIC_LVT_THERMAL      = 0x833;
constexpr uint32_t MSR_X2APIC_LVT_PMI          = 0x834;
constexpr uint32_t MSR_X2APIC_LVT_LINT0        = 0x835;
constexpr uint32_t MSR_X2APIC_LVT_LINT1        = 0x836;
constexpr uint32_t MSR_X2APIC_LVT_ERROR        = 0x837;
constexpr uint32_t MSR_X2APIC_TIMER_ICR        = 0x838;
constexpr uint32_t MSR_X2APIC_TIMER_CCR        = 0x839;
constexpr uint32_t MSR_X2APIC_TIMER_DCR        = 0x83E;

// Memory Type Range Registers (MTRR)
constexpr uint32_t MSR_IA32_MTRRCAP            = 0xFE;
constexpr uint32_t MSR_IA32_MTRR_DEF_TYPE      = 0x2FF;
constexpr uint32_t MSR_IA32_MTRR_PHYSBASE0     = 0x200;
constexpr uint32_t MSR_IA32_MTRR_PHYSMASK0     = 0x201;

// Machine Check Architecture
constexpr uint32_t MSR_IA32_MCG_CAP            = 0x179;
constexpr uint32_t MSR_IA32_MCG_STATUS         = 0x17A;
constexpr uint32_t MSR_IA32_MCG_CTL            = 0x17B;

// Debug and Trace
constexpr uint32_t MSR_IA32_DEBUGCTL           = 0x1D9;
constexpr uint32_t MSR_IA32_DS_AREA            = 0x600;

// Function to read an MSR
inline uint64_t read_msr(uint32_t msr) {
    uint32_t lo, hi;
    __asm__ volatile("rdmsr" : "=a"(lo), "=d"(hi) : "c"(msr));
    return ((uint64_t)hi << 32) | lo;
}

// Function to write to an MSR
inline void write_msr(uint32_t msr, uint64_t value) {
    uint32_t lo = value & 0xFFFFFFFF;
    uint32_t hi = value >> 32;
    __asm__ volatile("wrmsr" : : "c"(msr), "a"(lo), "d"(hi));
}

} // namespace msr
} // namespace x86

#endif // X86_MSR_HPP
