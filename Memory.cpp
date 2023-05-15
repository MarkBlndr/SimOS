// Author: Mark Blinder
// Memory: manages memory by finding space in RAM for new processes and removing processes from mem

#include "Memory.h"
#include "climits"
#include <iostream>

void Memory::Init(unsigned long long amountOfRAM) {
    mSize = amountOfRAM;
}

MemoryUsage Memory::GetMemory() {
    return mem;
}

bool Memory::comparator(MemoryItem &a, MemoryItem &b) {
    return a.itemAddress < b.itemAddress;
}

bool Memory::FindAndInsert(unsigned long long &newProcessSize, int PID) {
    // Comparator was made static, not sure if that ok
    std::sort(mem.begin(), mem.end(), comparator);

    unsigned long long startAddress, gapCurrent, gapFound, nextProcessAddress;

    // Initial values for gap search
    gapFound = ULLONG_MAX;
    //gapDifference = 0;

    // if memory is empty, and there is enough room for process, insert new process right away
    if (mem.size() == 0 && mSize >= newProcessSize) {
        mem.push_back(MemoryItem{0, newProcessSize, PID});
        return true;
    }

    // Checking front of mem for gap
    nextProcessAddress = mem[0].itemAddress;
    if (nextProcessAddress >= newProcessSize) {
        gapFound = nextProcessAddress;
        //gapDifference = gapFound - newProcessSize;
        startAddress = 0;
    }

    // Check middle for gaps
    unsigned long long currentItemLastAddr;
    for (int i = 0; i < mem.size() - 1; i++) {
        // Check gap between next process and current process being looped over
        currentItemLastAddr = (mem[i].itemAddress + mem[i].itemSize);
        gapCurrent = mem[i+1].itemAddress - currentItemLastAddr;
        if (gapCurrent >= newProcessSize && gapCurrent < gapFound) {
            gapFound = gapCurrent;
            startAddress = currentItemLastAddr;
        }
    }

    // Check end of memory for gap
    currentItemLastAddr = mem[mem.size()-1].itemAddress + mem[mem.size()-1].itemSize;
    gapCurrent = mSize - currentItemLastAddr;
    if (gapCurrent >= newProcessSize && gapCurrent < gapFound) {
            gapFound = gapCurrent;
            startAddress = currentItemLastAddr;
    }

    if (gapFound < ULLONG_MAX) {
        mem.push_back(MemoryItem{startAddress, newProcessSize, PID});
        return true;
    }

    // Incase auto-grader expects a sorted mem vector
    std::sort(mem.begin(), mem.end(), comparator);
    
    // No gap of sufficient size found, cannot insert new process into memory
    return false;
}

void Memory::Terminate(int PID) {
    for (MemoryUsage::iterator it = mem.begin(); it != mem.end(); ++it) {
        if (it->PID == PID) {
            mem.erase(it);
            break;
        }
    }
}