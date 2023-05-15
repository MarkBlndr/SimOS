// Mark Blinder
// Disk implementation

#include "Disk.h"

void Disk::DiskReadRequest(int PID, std::string fileName) {
    // Start disk job if idle, else add to queue
    if (idle) {
        currentJob.PID = PID;
        currentJob.fileName = fileName;
        idle = false;
    }
    else {
        diskQueue.push(FileReadRequest{PID, fileName});
    }
}

FileReadRequest Disk::getCurrentJob() {
    return currentJob;
}

std::queue<FileReadRequest> Disk::getDiskQueue() {
    return diskQueue;
}

int Disk::DiskJobCompleted() {
    // Disk is idle, no job to complete
    if (idle) {
        return -1;
    }
    else {
        int PID = currentJob.PID;
        if (!diskQueue.empty()) {
            currentJob.fileName = diskQueue.front().fileName;
            currentJob.PID = diskQueue.front().PID;
            diskQueue.pop();
            return PID;
        }
        else {
            // Set currentJob to default (idle)
            currentJob.fileName = "";
            currentJob.PID = 0;
            idle = true;
            return PID;
        }
    }
}

void Disk::RemoveFromDiskQueue(int PID) {
    std::queue<FileReadRequest> tempQueue;
    while(!diskQueue.empty()) {
        if (diskQueue.front().PID != PID) {
            tempQueue.push(diskQueue.front());
            diskQueue.pop();
        }
        else {
            diskQueue.pop();
        }
    }
    while(!tempQueue.empty()) {
        diskQueue.push(tempQueue.front());
        tempQueue.pop();
    }
}