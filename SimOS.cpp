// Author: Mark Blinder
// SimOS: contains OS functions

#include "SimOS.h"

SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM) {
    // Initialise disks
    for (int i = 0; i < numberOfDisks; i++) {
        disks.push_back(Disk());
    }
    memory.Init(amountOfRAM);
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
    // If CPU is idle, do nothing
    if (!GetCPU()) {
        return false;
    }

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

void SimOS::findChildren(int PID, std::vector<int> &vec) {
    if (!processes[PID].children.empty()) {
        for (int child : processes[PID].children) {
            findChildren(child, vec);
        }
    }
    vec.push_back(PID);
}

void SimOS::SimExit() {
    // If CPU is idle, do nothing
    if (!GetCPU()) {
        return;
    }

    int exitingPID = GetCPU();
    memory.Terminate(exitingPID);

    int parentPID = processes[exitingPID].parentPID;

    // Find all the children of exiting process for termination
    std::vector<int> vec;
    for (auto child : processes[exitingPID].children) {
        findChildren(child, vec);
    }
    for (int i = 0; i < vec.size(); i++) {
        cpu.RemoveFromQueue(vec[i]);
        for (int i = 0; i < disks.size(); i++) {
            disks[i].RemoveFromDiskQueue(vec[i]);
        }
        memory.Terminate(vec[i]);
        processes.erase(vec[i]);
    }

    if (processes[parentPID].waiting) {
        // Remove child from parent
        for (std::vector<int>::iterator it = processes[parentPID].children.begin(); it < processes[parentPID].children.end(); ++it) {
            if (*it == exitingPID) {
                processes[parentPID].children.erase(it);
            }
        }

        processes.erase(exitingPID); // Remove exiting process from processes
        
        // Send parent to ready queue (stop waiting)
        processes[parentPID].waiting = false;
        cpu.NextProcess();
        cpu.IncomingProcess(processes[parentPID].priority, parentPID);
    }
    else {
        cpu.NextProcess();
        processes[exitingPID].terminated = true; // become zombie
    }
}

void SimOS::SimWait() {
    int waitingPID = GetCPU();
    processes[waitingPID].waiting = true; // start waiting

    // If no children, continue using the CPU
    if (processes[waitingPID].children.empty()) {
        processes[waitingPID].waiting = false;
        return;
    }

    // Check for zombie children
    int zombieChild = -1;
    for (auto child : processes[waitingPID].children) {
        if (processes[child].terminated) {
            zombieChild = child;
            processes.erase(child);
            break; // Found zombie child 
        }
    }
    // If zombie child is found, remove from parent and continue using CPU
    if (zombieChild > -1) {
        for (std::vector<int>::iterator it = processes[waitingPID].children.begin(); it < processes[waitingPID].children.end(); ++it) {
            if (*it == zombieChild) {
                processes[waitingPID].children.erase(it);
            }
        }
        processes[waitingPID].waiting = false;
    }
    else {
        cpu.NextProcess();
    }
}

int SimOS::GetCPU() {
    return cpu.GetCPU();
}

std::vector<int> SimOS::GetReadyQueue() {
    return cpu.GetQueue();
}

MemoryUsage SimOS::GetMemory() {
    return memory.GetMemory();
}

void SimOS::DiskReadRequest(int diskNumber, std::string fileName) {
    disks[diskNumber].DiskReadRequest(GetCPU(), fileName);
    cpu.NextProcess();
}

FileReadRequest SimOS::GetDisk(int diskNumber) {
    return disks[diskNumber].getCurrentJob();
}

std::queue<FileReadRequest> SimOS::GetDiskQueue(int diskNumber) {
    return disks[diskNumber].getDiskQueue();
}

void SimOS::DiskJobCompleted(int diskNumber) {
    if (diskNumber > (disks.size() - 1)) {
        //std::cout << "ERROR: DISK" << diskNumber << " not found" << std::endl;
        return;
    }

    int PID = disks[diskNumber].DiskJobCompleted();
    
    if (PID == -1) {
        //std::cout << "ERROR: DISK" << diskNumber << " is idle" << std::endl;
        return;
    }

    // Send process back to the CPU ready queue
    cpu.IncomingProcess(processes[PID].priority, PID);
}