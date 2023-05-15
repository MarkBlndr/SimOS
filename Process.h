// Author: Mark Blinder
// Process: representation of a process for the OS processes table/list

#include <vector>

struct Process {
    int priority = 0;
    unsigned long long size = 0;
    bool waiting = false;

    bool terminated = false;
    int parentPID = 0;
    
    std::vector<int> children;
};