// Author: Mark Blinder
// SimOS implementation 

#include "Disk.h"
#include "Memory.h"
#include "CPU.h"
#include "Process.h"

#include <vector>
#include <iostream>
#include <unordered_map>

class SimOS {
public:
    SimOS(int, unsigned long long);

    bool NewProcess(int, unsigned long long);
    MemoryUsage GetMemory();

    int GetCPU(); // return PID of current process, if idle return 0
    std::vector<int> GetReadyQueue();

    bool SimFork();
    void SimExit();
    void SimWait();

    void findChildren(int, std::vector<int>&);

    // Disk management
    void DiskReadRequest(int, std::string);
    FileReadRequest GetDisk(int);
    std::queue<FileReadRequest> GetDiskQueue(int);
    void DiskJobCompleted(int);

private:
    std::vector<Disk> disks;
    Memory memory;
    CPU cpu;
    std::unordered_map<int, Process> processes;
    int nextPID = 1;
};