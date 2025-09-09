#include "Memory.h"
#include <EEPROM.h>

Memory::Memory() {}

void Memory::save(MemoryPos pos, int newValue, bool forceWrite)
{
    int addr = static_cast<int>(pos) * sizeof(int);
    int oldValue = load(pos);
    if (forceWrite || oldValue != newValue)
    {
        EEPROM.put(addr, newValue);
    }
}

int Memory::load(MemoryPos pos) const
{
    int addr = static_cast<int>(pos) * sizeof(int);
    int value = 0;
    EEPROM.get(addr, value);
    return value;
}