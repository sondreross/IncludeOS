#include <os>
#include <service>
#include <ending_bench>

void Service::start(const std::string& args){
  printf("Args = %s\n", args.c_str());
  printf("Try giving the service less memory, eg. 10MB in vm.json\n");
  printf("Service done. Shutting down...\n");

  uint64_t *table;
  uint32_t rc;

  ending_bench::start_bench(1);
  int i = 0;
  for (int i = 0; i < 10000000000; i++) i++;
  rc = ending_bench::end_bench(&table);
  printf("Entries %d\n", rc);
  os::shutdown();
}
