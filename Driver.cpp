#include "SimOS.h"

#include <iostream>
#include <queue>

using namespace std;

void printCPUandQueue(SimOS& sim) {
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

int main() {
    // Cascading Termination
    SimOS sim(2, 100);
    
    sim.NewProcess(10, 2); // 1

    sim.SimFork(); // 2 - child of 1
    sim.DiskReadRequest(0, "x"); // Send 1 to disk

    sim.SimFork(); // 3 - child of 2
    sim.DiskReadRequest(0, "x"); // Send 2 to disk

    sim.SimFork(); // 4 - child of 3
    sim.DiskReadRequest(0, "x"); // Send 3 to disk

    sim.SimFork(); // 5 - child of 4
    sim.DiskReadRequest(0, "x"); // Send 4 to disk

    sim.SimFork(); // 6 - child of 5
    sim.SimFork(); // 7 - child of 5
    sim.SimFork(); // 8 - child of 5

    sim.DiskReadRequest(0, "x"); // Send 5 to disk
    sim.DiskReadRequest(0, "x"); // Send 6 to disk
    sim.DiskReadRequest(0, "x"); // Send 7 to disk
    sim.DiskReadRequest(0, "x"); // Send 8 to disk

    sim.DiskJobCompleted(0);
    sim.DiskJobCompleted(0);
    sim.DiskJobCompleted(0);
    sim.DiskJobCompleted(0);
    sim.DiskJobCompleted(0);
    sim.DiskJobCompleted(0);
    sim.DiskJobCompleted(0);
    sim.DiskJobCompleted(0);

    printMem(sim);
    printCPUandQueue(sim);

    cout << "EXIT call on P1, should terminated all children" << endl;
    sim.SimExit();

    printMem(sim);
    printCPUandQueue(sim);





    // SimOS sim(2, 1000000);
    // sim.NewProcess(6, 10000); // Process 1, priority 6, Should be in mem and CPU
    // cout << "AFTER NP CALL, Current CPU process: (Should be 1) " << sim.GetCPU() << endl;
    // sim.SimFork(); // Process 2, priority 6, child of 1, should be in queue
    // sim.SimFork(); // Process 3, priority 6, child of 1, should be in queue
    // cout << "AFTER 2 FORKS CALL, Current CPU process: (Should be 1) " << sim.GetCPU() << endl;
    
    // cout << "READY QUEUE: (should be 3 2) ";
    // for (int p : sim.GetReadyQueue()) {
    //     cout << p << " ";
    // }
    // cout << endl;

    // cout << "MEMORY: ";
    // MemoryUsage mem = sim.GetMemory();
    // for (auto process : mem) {
    //     cout << "P" << process.PID << " [" << process.itemAddress << ", " << (process.itemAddress + process.itemSize) - 1 << "] ";
    // }
    // cout << endl;

    // sim.SimWait(); // Called on 1, should be waiting for children to exit, should not be in CPU
    // cout << "AFTER WAIT CALL, Current CPU process: (Should be 3) " << sim.GetCPU() << endl;
    // sim.SimExit(); // Called on 3(?), should make 1 go back to CPU

    // cout << "AFTER EXIT CALL, Current CPU process: (Should be 1 or 2) " << sim.GetCPU() << endl;

    // cout << "READY QUEUE: (should be 1 or 2) ";
    // for (int p : sim.GetReadyQueue()) {
    //     cout << p << " ";
    // }
    // cout << endl;

    // cout << "MEMORY: ";
    // mem = sim.GetMemory();
    // for (auto process : mem) {
    //     cout << "P" << process.PID << " [" << process.itemAddress << ", " << (process.itemAddress + process.itemSize) - 1 << "] ";
    // }
    // cout << endl;








    // // MEMORY PRINTOUT
    // cout << endl;
    // cout << "mem print out: " << endl;
    // MemoryUsage mem = sim.GetMemory();
    // for (auto process : mem) {
    //     cout << "P" << process.PID << " [" << process.itemAddress << ", " << (process.itemAddress + process.itemSize) - 1 << "]" << endl;
    // }
    // cout << endl;

    // // READY QUEUE PRINTOUT
    // cout << endl;
    // cout << "Ready queue (should be 3): ";
    // for (int p : sim.GetReadyQueue()) {
    //     cout << p << " ";
    // }
    // cout << endl;
}