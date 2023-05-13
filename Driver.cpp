#include "SimOS.h"

#include <iostream>
#include <queue>

using namespace std;

int main() {
    FileReadRequest frr;

    SimOS sim(2, 1000);
    sim.DiskReadRequest(0, "t1.txt", 1);
    sim.DiskReadRequest(0, "t2.txt", 20);
    sim.DiskReadRequest(0, "t3.txt", 300);
    sim.DiskReadRequest(0, "t4.txt", 4000);

    // DISK QUEUE PRINT OUT
    queue<FileReadRequest> dqTemp = sim.GetDiskQueue(0);
    cout << "DISK0 QUEUE:" << endl;
    for (size_t i = 0; i < dqTemp.size(); i++) {
        cout << i+1 << ": " << dqTemp.front().fileName << " " << dqTemp.front().PID << endl;;
        dqTemp.push(dqTemp.front()); // This is added so that the queue size does not change
        dqTemp.pop();
    }

    cout << endl;

    // TESTING DISK JOB COMPLETION
    sim.DiskJobCompleted(2); // No such Disk
    sim.DiskJobCompleted(1); // Disk is idle
    sim.DiskJobCompleted(0); // Should return PID 1
    sim.DiskJobCompleted(0); // Should return PID 20

    cout << endl;

    cout << "CURRENT JOB: " << sim.GetDisk(0).fileName << " " << sim.GetDisk(0).PID << endl;

    cout << endl;

    dqTemp = sim.GetDiskQueue(0);
    cout << "DISK0 QUEUE:" << endl;
    for (size_t i = 0; i < dqTemp.size(); i++) {
        cout << i+1 << ": " << dqTemp.front().fileName << " " << dqTemp.front().PID << endl;;
        dqTemp.push(dqTemp.front()); // This is added so that the queue size does not change
        dqTemp.pop();
    }


    return 0;
}