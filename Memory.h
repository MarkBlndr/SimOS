#include "MemoryItem.h"
#include <algorithm>

class Memory {
public:
    void Init(unsigned long long);
    MemoryUsage GetMemory();
    static bool comparator(MemoryItem&, MemoryItem&);
    bool FindAndInsert(unsigned long long &, int);

    // TODO: For testing
    void KillProcess(int);

private:
    MemoryUsage mem;
    unsigned long long mSize;
};