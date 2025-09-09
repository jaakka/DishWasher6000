#ifndef MEMORY_H
#define MEMORY_H

enum class MemoryPos 
{
    warmWaterHeatTime,
    hotWaterHeatTime,
    waterFillTime,
    errorCode
};

class Memory {
public:
    Memory();
    void save(MemoryPos pos, int newValue, bool forceWrite = false);
    int load(MemoryPos pos) const;
};

#endif