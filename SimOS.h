// Author: Mark Blinder
// SimOS implementation 

#include "Disk.h"
#include "Memory.h"
#include "CPU.h"

#include <vector>
#include <iostream>

class SimOS {
public:
    SimOS(int, unsigned long long);

    bool NewProcess(int, unsigned long long);
    // MemoryUsage GetMemory( )
    MemoryUsage GetMemory();
    
    // TODO: For testing
    void KillProcess(int);

    //bool SimFork();
    //void SimExit();
    //void SimWait();

    // Disk management
    void DiskReadRequest(int, std::string, int);
    FileReadRequest GetDisk(int);
    std::queue<FileReadRequest> GetDiskQueue(int);
    void DiskJobCompleted(int);

private:
    std::vector<Disk> disks;
    Memory memory;

    int nextPID;
};