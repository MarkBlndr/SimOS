// Mark Blinder
// CPU class implementation

#include "CPU.h"

int CPU::GetCPU() {
    return currentProcess.second;
}

void CPU::IncomingProcess(int priority, int PID) {
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
    std::pair<int, int> next;
    next = readyQueue.top();
    readyQueue.pop();
    currentProcess.first = next.first;
    currentProcess.second = next.second;
}