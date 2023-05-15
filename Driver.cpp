#include "SimOS.h"

#include <iostream>
#include <queue>

using namespace std;

int main() {

    SimOS sim(2, 1000000);
    sim.NewProcess(6, 10000); // Process 1, priority 6, Should be in mem and CPU
    cout << "AFTER NP CALL, Current CPU process: (Should be 1) " << sim.GetCPU() << endl;
    sim.SimFork(); // Process 2, priority 6, child of 1, should be in queue
    sim.SimFork(); // Process 3, priority 6, child of 1, should be in queue
    cout << "AFTER 2 FORKS CALL, Current CPU process: (Should be 1) " << sim.GetCPU() << endl;
    
    cout << "READY QUEUE: (should be 3 2) ";
    for (int p : sim.GetReadyQueue()) {
        cout << p << " ";
    }
    cout << endl;

    cout << "MEMORY: ";
    MemoryUsage mem = sim.GetMemory();
    for (auto process : mem) {
        cout << "P" << process.PID << " [" << process.itemAddress << ", " << (process.itemAddress + process.itemSize) - 1 << "] ";
    }
    cout << endl;

    sim.SimWait(); // Called on 1, should be waiting for children to exit, should not be in CPU
    cout << "AFTER WAIT CALL, Current CPU process: (Should be 3) " << sim.GetCPU() << endl;
    sim.SimExit(); // Called on 3(?), should make 1 go back to CPU

    cout << "AFTER EXIT CALL, Current CPU process: (Should be 1 or 2) " << sim.GetCPU() << endl;

    cout << "READY QUEUE: (should be 1 or 2) ";
    for (int p : sim.GetReadyQueue()) {
        cout << p << " ";
    }
    cout << endl;

    cout << "MEMORY: ";
    mem = sim.GetMemory();
    for (auto process : mem) {
        cout << "P" << process.PID << " [" << process.itemAddress << ", " << (process.itemAddress + process.itemSize) - 1 << "] ";
    }
    cout << endl;








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