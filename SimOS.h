// Author: Mark Blinder
// SimOS implementation 


#include <vector>
#include "Disk.h"

class SimOS {
public:
    SimOS(int, unsigned long long);
    
    //bool NewProcess(int, unsigned long long);
    //bool SimFork();
    //void SimExit();
    //void SimWait();

    // Disk management
    void DiskReadRequest(int, std::string, int);
    FileReadRequest GetDisk(int);
    std::queue<FileReadRequest> GetDiskQueue(int);

private:
    std::vector<Disk> disks;
};