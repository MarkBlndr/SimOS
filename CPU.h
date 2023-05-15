// Mark Blinder
// CPU: contains CPU ready-queue (priority based with preemption)

#include <queue>
#include <vector>

class CPU {
public:
    int GetCPU();
    void IncomingProcess(int, int);
    void NextProcess();
    std::vector<int> GetQueue();
    void RemoveFromQueue(int);

private:
    std::pair<int, int> currentProcess = std::make_pair(0, 0); // int priority, int PID, idle (0,0)
    std::priority_queue<std::pair<int,int>> readyQueue;
};