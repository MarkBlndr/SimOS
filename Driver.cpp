#include "SimOS.h"

#include <iostream>

using namespace std;

int main() {
    FileReadRequest frr;

    SimOS sim(2, 1000);
    sim.DiskReadRequest(0, "t3.txt", 1);
    sim.DiskReadRequest(1, "t2.txt", 5);
    sim.DiskReadRequest(0, "t1.txt", 2);
    sim.DiskReadRequest(1, "t4.txt", 8);

    //frr = sim.GetDisk(0);
    //cout << "File name: " << frr.fileName << " PID: " << frr.PID << endl;

    // TODO: Test disk queue somehow
    //cout << sim.GetDiskQueue() << endl;



    return 0;
}