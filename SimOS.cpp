// Author: Mark Blinder
// SimOS class header, contains OS functions 

// TODO: Implement memory management

#include "SimOS.h"

SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM) {
    // Initialise disks
    for (int i = 0; i < numberOfDisks; i++) {
        disks.push_back(Disk());
    }
}

// TODO: PID should come from CPU, not passed in as argument
void SimOS::DiskReadRequest(int diskNumber, std::string fileName, int tempPID) {
    disks[diskNumber].DiskReadRequest(tempPID, fileName);
}

FileReadRequest SimOS::GetDisk(int diskNumber) {
    return disks[diskNumber].getCurrentJob();
}

std::queue<FileReadRequest> SimOS::GetDiskQueue(int diskNumber) {
    return disks[diskNumber].getDiskQueue();
}

void SimOS::DiskJobCompleted(int diskNumber) {
    // finish current disk process
    // Call the disk function, returns PID for simOS to work on
    if (diskNumber > (disks.size() - 1)) {
        std::cout << "ERROR: DISK" << diskNumber << " not found" << std::endl;
        return;
    }

    int PID;
    PID = disks[diskNumber].DiskJobCompleted();

    if (PID == -1) {
        std::cout << "ERROR: DISK" << diskNumber << " is idle" << std::endl;
        return;
    }

    // TEMP
    std::cout << "JOB COMPLETE: Process " << PID << " moving back to CPU" << std::endl;

    // TODO:
    // CPU(PID)
    // Return process to CPU ready queue or straight to CPU based on priority
}