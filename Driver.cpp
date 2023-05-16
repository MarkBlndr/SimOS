#include "SimOS.h"

#include <iostream>
#include <queue>

using namespace std;

void printCPUandQueue(SimOS& sim) {
    cout << endl;
    cout << "CURRENT PROCESS: " << sim.GetCPU() << endl << "READY QUEUE: ";
    for (int p : sim.GetReadyQueue()) {
        cout << p << " ";
    }
    cout << endl;
}

void printMem(SimOS& sim) {
    cout << endl;
    cout << "MEMORY: " << endl;
    MemoryUsage mem = sim.GetMemory();
    for (auto process : mem) {
        cout << "P" << process.PID << " [" << process.itemAddress << ", " << (process.itemAddress + process.itemSize) - 1 << "]" << endl;
    }
    cout << endl;
}

void printDisk(SimOS& sim, int d) {
    cout << endl;
    std::queue<FileReadRequest> q = sim.GetDiskQueue(d);
    cout << "DISK" << d << " CURRENT: " << sim.GetDisk(d).PID << " QUEUE: ";
    while (!q.empty()) {
        cout << q.front().PID;
        q.pop();
    }
    cout << endl;
}

int main() {
    // Cascading Termination
    SimOS sim(2, 1000);
    
    sim.NewProcess(10, 10); // 1
    sim.SimFork(); // 2 - child of 1

    sim.DiskReadRequest(0, ""); // send 1 to disk
    sim.SimFork(); // 3 - child of 2
    sim.SimFork(); // 4 - child of 2
    sim.SimFork(); // 5 - child of 2

    sim.DiskReadRequest(0, ""); // send 2 to disk

    sim.SimFork(); // 6 - child of 5

    sim.DiskReadRequest(0, ""); // send 5 to disk
    sim.DiskReadRequest(0, ""); // send 6 to disk
    sim.DiskReadRequest(0, ""); // send 4 to disk

    sim.SimFork(); // 7 - child of 3
    sim.SimFork(); // 8 - child of 3

    sim.DiskReadRequest(0, ""); // send 3 to disk
    sim.DiskReadRequest(0, ""); // send 8 to disk
    sim.DiskReadRequest(0, ""); // send 7 to disk

    sim.DiskJobCompleted(0); // Bring back 1 to CPU queue
    sim.DiskJobCompleted(0); // Bring back 2 to CPU queue
    sim.DiskJobCompleted(0); // Bring back 3 to CPU queue
    sim.DiskJobCompleted(0); // Bring back 4 to CPU queue
    sim.DiskJobCompleted(0); // Bring back 5 to CPU queue
    sim.DiskJobCompleted(0); // Bring back 6 to CPU queue
    sim.DiskJobCompleted(0); // Bring back 7 to CPU queue
    sim.DiskJobCompleted(0); // Bring back 8 to CPU queue

    printCPUandQueue(sim);
    printMem(sim);

    cout << "CALLING EXIT ON P1" << endl;
    sim.SimExit();

    printCPUandQueue(sim);
    printMem(sim);


}