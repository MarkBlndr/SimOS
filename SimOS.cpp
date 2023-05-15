// Author: Mark Blinder
// SimOS: contains OS functions

#include "SimOS.h"

SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM) {
    // Initialise disks
    for (int i = 0; i < numberOfDisks; i++) {
        disks.push_back(Disk());
    }
    memory.Init(amountOfRAM);
    nextPID = 1;
}

bool SimOS::NewProcess(int priority, unsigned long long size) {
    bool sufficientMem = memory.FindAndInsert(size, nextPID);
    if (sufficientMem) {
        processes.insert(std::make_pair(nextPID, Process{priority, size, false}));
        cpu.IncomingProcess(priority, nextPID); // Send to CPU
        nextPID++;
        return true;
    }
    return false;
}

bool SimOS::SimFork() {
    int parentPID = GetCPU(), childPID = nextPID;
    Process parentProcess = processes[parentPID];
    bool forked = NewProcess(parentProcess.priority, parentProcess.size);

    if (forked) {
        processes[childPID].parentPID = parentPID;
        processes[parentPID].children.push_back(childPID);
        return true;
    }
    return false;
}

void SimOS::SimExit() {
    int exitingPID = GetCPU();
    int parentPID = processes[exitingPID].parentPID;

    // Terminate children of process
    for (auto child : processes[exitingPID].children) {
        memory.Terminate(child); // remove from memory
        processes.erase(child); // remove from process table/list
    }

    if (processes[parentPID].waiting) {
        // Remove child from parent
        for (std::vector<int>::iterator it = processes[parentPID].children.begin(); it != processes[parentPID].children.end(); ++it) {
            if (*it == exitingPID) {
                processes[parentPID].children.erase(it);
            }
        }
        memory.Terminate(exitingPID); // Remove exiting process from memory 
        processes.erase(exitingPID); // Remove exiting process from processes

        // Send parent to ready queue (stop waiting)
        processes[parentPID].waiting = false;
        cpu.NextProcess();
        cpu.IncomingProcess(processes[parentPID].priority, parentPID);
    }
    else {
        memory.Terminate(exitingPID);
        processes[exitingPID].terminated = true;
    }
}

void SimOS::SimWait() {
    int waitingPID = GetCPU();
    processes[waitingPID].waiting = true; // start waiting

    // If no children, go back to ready-queue
    if (processes[waitingPID].children.empty()) {
        processes[waitingPID].waiting = false;
        cpu.NextProcess();
        cpu.IncomingProcess(processes[waitingPID].priority, waitingPID);
        return;
    }
    // Check for zombie children
    int zombieChild = -1;
    for (auto child : processes[waitingPID].children) {
        if (processes[child].terminated == true) {
            zombieChild = child;
            processes.erase(child);
            break;
        }
    }
    // If zombie child is found, remove from parent and send parent to ready-queue
    if (zombieChild > -1) {
        for (std::vector<int>::iterator it = processes[waitingPID].children.begin(); it != processes[waitingPID].children.end(); ++it) {
            if (*it == zombieChild) {
                processes[waitingPID].children.erase(it);
            }
        }
        processes[waitingPID].waiting = false;
        cpu.NextProcess();
        cpu.IncomingProcess(processes[waitingPID].priority, waitingPID);
    }
}

int SimOS::GetCPU() {
    return cpu.GetCPU();
}

MemoryUsage SimOS::GetMemory() {
    return memory.GetMemory();
}

void SimOS::DiskReadRequest(int diskNumber, std::string fileName) {
    disks[diskNumber].DiskReadRequest(GetCPU(), fileName);
}

FileReadRequest SimOS::GetDisk(int diskNumber) {
    return disks[diskNumber].getCurrentJob();
}

std::queue<FileReadRequest> SimOS::GetDiskQueue(int diskNumber) {
    return disks[diskNumber].getDiskQueue();
}

void SimOS::DiskJobCompleted(int diskNumber) {
    if (diskNumber > (disks.size() - 1)) {
        std::cout << "ERROR: DISK" << diskNumber << " not found" << std::endl;
        return;
    }

    int PID = disks[diskNumber].DiskJobCompleted();
    
    if (PID == -1) {
        std::cout << "ERROR: DISK" << diskNumber << " is idle" << std::endl;
        return;
    }

    // Send process back to the CPU ready queue
    cpu.IncomingProcess(processes[PID].priority, PID);
}