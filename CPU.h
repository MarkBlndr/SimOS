// Mark Blinder
// CPU: contains CPU ready-queue (priority based with preemption)

#include <queue>

class CPU {
public:
    int GetCPU();
    void IncomingProcess(int, int);
    void NextProcess();
private:
    std::pair<int, int> currentProcess = std::make_pair(0, 0); // int priority, int PID, idle (0,0)
    std::priority_queue<std::pair<int,int>> readyQueue;
};