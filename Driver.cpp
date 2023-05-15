#include "SimOS.h"

#include <iostream>
#include <queue>

using namespace std;

int main() {

    SimOS sim(2, 1000000);

    sim.GetReadyQueue();


    sim.NewProcess(6, 10000); // 1
    sim.SimFork(); // 2 p6 from 1 
    sim.SimFork(); // 3 p6 from 1
    sim.DiskReadRequest(0, "my.doc"); // 1 goes to disk 0

    // cout << "Using CPU: (should be 3) " << sim.GetCPU() << endl;

    sim.SimFork(); // 4 p6 from 3

    //cout << "debug 1" << endl;

    sim.DiskReadRequest(1, "my.doc"); // 3 goes to disk 1
    sim.DiskReadRequest(1, "my.doc"); // 4 goes to disk 1
    sim.DiskReadRequest(1, "my.doc"); // 2 goes to disk 1

    // cout << endl;
    // // DISK QUEUE PRINT OUT
    // cout << "CURRENT JOB: " << sim.GetDisk(1).fileName << " " << sim.GetDisk(1).PID << endl;
    // queue<FileReadRequest> dqTemp = sim.GetDiskQueue(1);
    // cout << "DISK1 QUEUE:" << endl;
    // for (size_t i = 0; i < dqTemp.size(); i++) {
    //     cout << i+1 << ": " << dqTemp.front().fileName << " " << dqTemp.front().PID << endl;;
    //     dqTemp.push(dqTemp.front()); // This is added so that the queue size does not change
    //     dqTemp.pop();
    // }

    //cout << "Using CPU: (should be idle 0) " << sim.GetCPU() << endl;

    sim.DiskJobCompleted(0); // 1 comes back to CPU

    //cout << "Using CPU: (should be 1) " << sim.GetCPU() << endl;

    sim.DiskJobCompleted(1); // 3 comes back to CPU queue

    //cout << "Using CPU: (should be 1) " << sim.GetCPU() << endl;

    // cout << endl;
    // cout << "Ready queue (should be 3): ";
    // for (int p : sim.GetReadyQueue()) {
    //     cout << p << " ";
    // }
    // cout << endl;

    sim.SimExit();

    cout << endl;
    cout << "mem print out: " << endl;
    MemoryUsage mem = sim.GetMemory();
    for (auto process : mem) {
        cout << "P" << process.PID << " [" << process.itemAddress << ", " << (process.itemAddress + process.itemSize) - 1 << "]" << endl;
    }
    

    // cout << "Using CPU: " << sim.GetCPU() << endl;
    // cout << "Using DISK0: " << sim.GetDisk(0).PID << endl;

    // cout << "Using CPU: " << sim.GetCPU() << endl;

    // cout << "Ready queue:";
    // for (int p : sim.GetReadyQueue()) {
    //     cout << p << " ";
    // }
    // cout << endl;




    // SimOS sim(2, 64000000000);

    // // // TESTING CPU
    // // sim.NewProcess(3,2000000000);
    // // cout << "Current Process using CPU: " << sim.GetCPU() << endl;
    
    // // // Testing preemption
    // // sim.NewProcess(5,2000000000);
    // // cout << "After new Process with higher priority is created: " << sim.GetCPU() << endl;

    // // TESTING FORK

    // cout << "testing fork:" << sim.SimFork() << endl;




    // // TESTING MEMORY
    // sim.NewProcess(0, 4);
    // sim.NewProcess(0, 5);
    // sim.NewProcess(0, 3);
    // sim.NewProcess(0, 3);
    // // To many
    // if (!sim.NewProcess(0, 3)) {
    //     cout << "Could not add new process to mem" << endl;
    // }
    // MemoryUsage mem = sim.GetMemory();
    // for (auto process : mem) {
    //     cout << "P" << process.PID << " [" << process.itemAddress << ", " << (process.itemAddress + process.itemSize) - 1 << "]" << endl;
    // }
    // cout << endl;
    // sim.KillProcess(3);
    // sim.KillProcess(1);
    // cout << endl;
    // cout << "After process kill calls" << endl;
    // mem = sim.GetMemory();
    // for (auto process : mem) {
    //     cout << "P" << process.PID << " [" << process.itemAddress << ", " << (process.itemAddress + process.itemSize) - 1 << "]" << endl;
    // }
    // cout << endl;
    // // Test mid small gap
    // sim.NewProcess(0, 2);
    // cout << endl;
    // cout << "After process 5 add" << endl;
    // mem = sim.GetMemory();
    // for (auto process : mem) {
    //     cout << "P" << process.PID << " [" << process.itemAddress << ", " << (process.itemAddress + process.itemSize) - 1 << "]" << endl;
    // }
    // cout << endl;


    // // TESTING DISK
    // sim.DiskReadRequest(0, "t1.txt", 1);
    // sim.DiskReadRequest(0, "t2.txt", 20);
    // sim.DiskReadRequest(0, "t3.txt", 300);
    // sim.DiskReadRequest(0, "t4.txt", 4000);

    // // DISK QUEUE PRINT OUT
    // queue<FileReadRequest> dqTemp = sim.GetDiskQueue(0);
    // cout << "DISK0 QUEUE:" << endl;
    // for (size_t i = 0; i < dqTemp.size(); i++) {
    //     cout << i+1 << ": " << dqTemp.front().fileName << " " << dqTemp.front().PID << endl;;
    //     dqTemp.push(dqTemp.front()); // This is added so that the queue size does not change
    //     dqTemp.pop();
    // }

    // cout << endl;

    // // TESTING DISK JOB COMPLETION
    // sim.DiskJobCompleted(2); // No such Disk
    // sim.DiskJobCompleted(1); // Disk is idle
    // sim.DiskJobCompleted(0); // Should return PID 1
    // sim.DiskJobCompleted(0); // Should return PID 20

    // cout << endl;
    // cout << "CURRENT JOB: " << sim.GetDisk(0).fileName << " " << sim.GetDisk(0).PID << endl;
    // cout << endl;

    // dqTemp = sim.GetDiskQueue(0);
    // cout << "DISK0 QUEUE:" << endl;
    // for (size_t i = 0; i < dqTemp.size(); i++) {
    //     cout << i+1 << ": " << dqTemp.front().fileName << " " << dqTemp.front().PID << endl;;
    //     dqTemp.push(dqTemp.front()); // This is added so that the queue size does not change
    //     dqTemp.pop();
    // }


    //return 0;
}