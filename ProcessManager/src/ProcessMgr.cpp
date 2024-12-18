#include "ProcessMgr.h"

//Constructor
ProcessManager::ProcessManager()
{
  std::cout << "Process Manager Initialised\n";
  SetUp();
}


//Constructor
ProcessManager::~ProcessManager()
{
  std::cout << "Process Manager de-initialised\n";
  CleanUp();
}


int ProcessManager::SetUp()
{
  std::cout << "Setting up ...\n";
  processID = getpid();

  //Set up signal events.
  sigemptyset(&sigset); //Create empty set.
  sigaddset(&sigset, SIGCHLD);  //Add SIG_CHLD to set.
  sigprocmask(SIG_BLOCK, &sigset, NULL);  //Add this set of signals to blocking set of signals.

  std::cout << "Process manager running..., processID: " << processID << std::endl;
  return 0;
}


int ProcessManager::CleanUp()
{
  std::cout << "Clean up ...\n";
  return 0;
}


int ProcessManager::SpawnGPSManager()
{
  std::cout << "Spawing GPS Manager...\n";
  gpsMgrProcessID = fork();
  if (gpsMgrProcessID < 0)
  {
    std::cout << "Failed to launch GPS manager application... Terminating!!!\n";
    exit(0);
  }
  if (gpsMgrProcessID == 0)
  {
    char *args[]={"/home/jaspreet/Workspace/LinuxSystemProgramming/Linux/GPSMgr/build/gpsMgr",NULL};
    execvp(args[0],args);
  }
  return 0;
}


int ProcessManager::SpawnCLIServer()
{
  std::cout << "Spawing CLI Server...\n";
  cliServerProcessID = fork();
  if (cliServerProcessID < 0)
  {
    std::cout << "Failed to launch CLI server application... Terminating!!!\n";
    exit(0);
  }
  if (cliServerProcessID == 0)
  {
    char *args[]={"/home/jaspreet/Workspace/LinuxSystemProgramming/Linux/CLIServer/build/cliServer",NULL};
    execvp(args[0],args);
  }
  return 0;
}


void ProcessManager::HandleSigChild(siginfo_t sigInfo)
{
  std::cout << "Processing SIG_CHLD\n";
  if (sigInfo.si_pid == gpsMgrProcessID)
  {
    //Call wait to remove zombie state of child process.
    waitpid(gpsMgrProcessID, NULL, WNOHANG);
    //Respawn GPS process...
    SpawnGPSManager();
  }
  else if (sigInfo.si_pid == cliServerProcessID)
  {
    //Call wait to remove zombie state of child process.
    waitpid(cliServerProcessID, NULL, WNOHANG);
    //Respawn CLI server process...
    SpawnCLIServer();
  }
  else
  {
    std::cout << "Should not hit this case!!!\n";
  }

  return;
}


void ProcessManager::HandleSignalEvent(siginfo_t sigInfo)
{
  std::cout << "Signal received... from process with pID: " << sigInfo.si_pid << std::endl;
  switch (sigInfo.si_signo)
  {
    case SIGCHLD:
      HandleSigChild(sigInfo);
      break;
    default:
      break;
  }
}


int ProcessManager::SpawnProcesses()
{
  std::cout << "Spawning processes ...\n";

  SpawnGPSManager();
  SpawnCLIServer();
  
  while(1)
  {
    //Wait for any child process to terminate..
    //If any one of them terminates, respawn them.
    int ret = sigwaitinfo(&sigset, &sigInfo);
    if (ret == -1)
    {
      perror("Sigwait failed\n");
      continue;
    }
    HandleSignalEvent(sigInfo);
  }

  return 0;
}



//Main
int main()
{
  std::cout << "Starting Process Manager...\n";
  ProcessManager processMgr = ProcessManager();

  processMgr.SpawnProcesses();


  return EXIT_SUCCESS;
} 
