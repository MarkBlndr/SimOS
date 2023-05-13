// Author: Mark Blinder
// Disk implementation

#include "Disk.h"

// TODO: Adjust functions to queue calls after vec has been updated to queue

bool Disk::DiskRequest(int PID, std::string fn) {
    // Start disk request if idle, else add to queue
    if (idle) {
        currentRequest.PID = PID;
        currentRequest.fileName = fn;
        idle = false;
    }
    else {
        diskQueue.push(FileReadRequest{PID, fn});
    }

    // Should return false if something went wrong
    return true;
}

FileReadRequest Disk::getCurrentRequest() {
    return currentRequest;
}

std::queue<FileReadRequest> Disk::getDiskQueue() {
    return diskQueue;
}