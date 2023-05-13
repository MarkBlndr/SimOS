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
    bool DiskRequest(int, std::string);
    FileReadRequest getCurrentRequest();
    std::queue<FileReadRequest> getDiskQueue();

private:
    FileReadRequest currentRequest;
    bool idle{true};
    std::queue<FileReadRequest> diskQueue;
};