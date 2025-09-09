#include <os>
#include <service>
#include <ending_bench>
#include <cmath>
#include <random>
#include <smp>

void Service::start(const std::string& args){
  printf("Args = %s\n", args.c_str());
  printf("Try giving the service less memory, eg. 10MB in vm.json\n");

  uint64_t *table;
  uint64_t rc;

  printf("CPU ID: %d\n", SMP::cpu_id());
  printf("CPU Count: %d\n", SMP::cpu_count());

  ending_bench::start_bench(1);
  
  // Better simulated workload - mix of CPU-intensive operations
  volatile double result = 0.0;  // volatile prevents optimization
  volatile uint64_t hash = 0;
  
  printf("Starting CPU-intensive workload...\n");
  
  for (int iteration = 0; iteration < 500; iteration++) {
    // Mathematical operations
    for (int i = 0; i < 100000; i++) {
      result += sin(i * 0.001) * cos(i * 0.002);
      result += sqrt(i + 1.0);
    }
    
    // Memory access patterns and simple hash computation
    for (int i = 0; i < 50000; i++) {
      hash = hash * 31 + i;  // Simple hash function
      hash ^= (hash >> 16);  // Mix bits
    }
    
    // Branch-heavy workload
    for (int i = 0; i < 25000; i++) {
      if (i % 7 == 0) {
        result *= 1.001;
      } else if (i % 11 == 0) {
        result += i * 0.0001;
      } else {
        result -= i * 0.00001;
      }
    }
    
    // Prevent compiler from optimizing away the work
    if (iteration % 100 == 0) {
      printf("Iteration %d, result: %f, hash: %lu\n", iteration, result, hash);
    }
  }
  
  printf("Workload complete. Final result: %f, hash: %lu\n", result, hash);
  
  rc = ending_bench::end_bench(&table);
  printf("Entries %lu\n", rc);
  os::shutdown();
}
