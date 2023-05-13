// Author: Mark Blinder
// Disk class header, handles disk read requests from OS, 
//  contains queue of next disk requests to be processed

#include "FileReadRequest.h"

#include <string>
#include <vector>
#include <queue>

class Disk {
public:
    //Disk(); No need it seems
    void DiskReadRequest(int, std::string);
    FileReadRequest getCurrentJob();
    std::queue<FileReadRequest> getDiskQueue();
    int DiskJobCompleted();

private:
    FileReadRequest currentJob;
    bool idle{true};
    std::queue<FileReadRequest> diskQueue;
};