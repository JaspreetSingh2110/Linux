#include "GPSMgr.h"

int main()
{
  std::cout << "Starting GPS manager...\n";

  int parentID = getppid();
  int processID = getpid();

  std::cout << "GPS manager running... PID: " << processID << ", parentID: " << parentID << std::endl;

  sleep(30);

  std::cout << "GPS manager terminating...\n";

  return EXIT_SUCCESS;
}
