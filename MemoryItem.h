#include <vector>

struct MemoryItem
{
    unsigned long long itemAddress;
    unsigned long long itemSize;
    int PID; // PID of the process using this chunk of memory
};
 
using MemoryUsage = std::vector<MemoryItem>;