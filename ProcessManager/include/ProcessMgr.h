#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

class ProcessManager{
  //Member functions.
  int SetUp();
  int CleanUp();

  int SpawnGPSManager();
  int SpawnCLIServer();
  
  //Data members
  pid_t processID;
  pid_t gpsMgrProcessID;
  pid_t cliServerProcessID;

  sigset_t sigset;
  siginfo_t sigInfo;

  public:
  //Member functions
  ProcessManager();
  ~ProcessManager();

  int SpawnProcesses();
  void HandleSignalEvent(siginfo_t sigInfo);
  void HandleSigChild(siginfo_t sigInfo);
};

