#include "common.hpp"
#include <time.h>
#include <atomic>
#include <cstdio>
#include <timers>
#include <smp>
#include <os>
#include <kernel/events.hpp>
using namespace std::chrono;

#ifndef INCLUDEOS_NANOSLEEP_TRACE
#define NANOSLEEP_LOG(...) do {} while (0)
#else
#define NANOSLEEP_LOG(...) printf(__VA_ARGS__)
#endif

static void nanosleep(nanoseconds nanos)
{
  std::atomic<bool> ticked{false};

  Timers::oneshot(nanos,
  [&ticked] (int) {
    ticked.store(true, std::memory_order_release);
    NANOSLEEP_LOG("[nanosleep] cb cpu=%d set ticked\n", SMP::cpu_id());
  });

  NANOSLEEP_LOG("[nanosleep] wait start cpu=%d\n", SMP::cpu_id());
  while (ticked.load(std::memory_order_acquire) == false) {
    // Process pending events first; the timer may already have fired.
    Events::get().process_events();
    if (ticked.load(std::memory_order_acquire)) break;
    os::halt();
    NANOSLEEP_LOG("[nanosleep] woke up cpu=%d\n", SMP::cpu_id());
  }
  NANOSLEEP_LOG("[nanosleep] wait done cpu=%d\n", SMP::cpu_id());
}

static long sys_nanosleep(const struct timespec* req, struct timespec */*rem*/)
{
  if (req == nullptr) return -EINVAL;
  auto nanos = nanoseconds(req->tv_sec * 1'000'000'000ull + req->tv_nsec);
  nanosleep(nanos);
  return 0;
}

extern "C"
long syscall_SYS_nanosleep(const struct timespec *req, struct timespec *rem)
{
  return strace(sys_nanosleep, "nanosleep", req, rem);
}

extern "C"
long syscall_SYS_clock_nanosleep(clockid_t, int,
        const struct timespec *req, struct timespec *rem)
{
  return strace(sys_nanosleep, "clock_nanosleep", req, rem);
}

extern "C"
long syscall_SYS_clock_nanosleep_time64(clockid_t, int,
        const struct timespec *req, struct timespec *rem)
{
  return strace(sys_nanosleep, "clock_nanosleep_time64", req, rem);
}
