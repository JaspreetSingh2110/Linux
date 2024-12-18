#include "CLIServer.h"

int main()
{
  std::cout << "Starting CLI server...\n";

  int parentID = getppid();
  int processID = getpid();

  std::cout << "CLI server running... PID: " << processID << ", parentID: " << parentID << std::endl;

  sleep(40);

  std::cout << "CLI server terminating...\n";

  return EXIT_SUCCESS;
}
