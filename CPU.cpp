// Mark Blinder
// CPU class implementation

#include "CPU.h"

int CPU::GetCPU() {
    return currentProcess.second;
}

void CPU::IncomingProcess(int priority, int PID) {
    // Idle CPU and empty queue
    if (readyQueue.empty() && currentProcess.first == 0 && currentProcess.second == 0) {
        currentProcess.first = priority;
        currentProcess.second = PID;
        return;
    }

    // Preemption
    if (priority > currentProcess.first) {
        readyQueue.push(currentProcess);
        currentProcess.first = priority;
        currentProcess.second = PID;
    }
    else {
        readyQueue.push(std::make_pair(priority, PID));
    }
}

void CPU::NextProcess() {
    if (readyQueue.empty()) {
        currentProcess.first = 0;
        currentProcess.second = 0;   
    }
    else {
        std::pair<int, int> next;
        next = readyQueue.top();
        readyQueue.pop();
        currentProcess.first = next.first;
        currentProcess.second = next.second;
    }
}

// Inefficient, but iteration over priority queue is not allowed 
std::vector<int> CPU::GetQueue() {

    std::vector<std::pair<int, int>> vecQueue;
    std::vector<int> returnVec;

    if (readyQueue.empty()) {
        returnVec.empty();
        return returnVec;
    }
    
    // Get everything out of the queue and into a vector
    while (!readyQueue.empty()) {
        vecQueue.push_back(readyQueue.top());
        readyQueue.pop();
    }

    // Get the PIDs of all the processes that were in the queue
    for (auto process : vecQueue) {
        returnVec.push_back(process.second);
    }

    // Put everything back
    for (auto process : vecQueue) {
        readyQueue.push(process);
    }

    return returnVec;
}