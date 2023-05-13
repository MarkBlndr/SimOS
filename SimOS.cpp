// Author: Mark Blinder
// SimOS class header, contains OS functions 

#include "SimOS.h"

// TODO: Implement memory management
SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM) {
    // Initialise disks
    for (int i = 0; i < numberOfDisks; i++) {
        disks.push_back(Disk());
    }
}

// TODO: PID should come from CPU, not passed in as argument
void SimOS::DiskReadRequest(int diskNumber, std::string fileName, int tempPID) {
    disks[diskNumber].DiskRequest(tempPID, fileName);
}

FileReadRequest SimOS::GetDisk(int diskNumber) {
    return disks[diskNumber].getCurrentRequest();
}

std::queue<FileReadRequest> SimOS::GetDiskQueue(int diskNumber) {
    return disks[diskNumber].getDiskQueue();
}