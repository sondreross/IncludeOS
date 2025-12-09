#include <os>
#include <service>
#include <chrono>
#include <thread>
#include <cstdio>
#include <string>

using namespace std;

// keep Service::start just for the early prints
void Service::start(const std::string& args) {
  std::printf("Args = %s\n", args.c_str());
  std::printf("Try giving the service less memory, eg. 10MB in vm.json\n");
}

// run the loop after timers/APIC are up
void Service::ready() {
  for (int i = 0; i < 100; ++i) {
    std::printf("Testing sleep for 10ms...\n");
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::printf("Sleep requested: 10ms\n");
    std::printf("Actual sleep duration: %lld microseconds (%.3f ms)\n",
           duration.count(), duration.count() / 1000.0);
    for (volatile long j = 0; j < 1000000000; ++j) ;
    std::printf("Finished iteration %d\n", i);
  }
  std::printf("Service done. Shutting down...\n");
  os::shutdown();
}