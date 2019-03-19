#pragma once

#include <vector>
#include "process.hpp"

class CPU
{

private:
    std::vector<Process> _processes;
    unsigned long long _hz;
    unsigned long long _ram;

public:
    // constructor: initialize private instance fields
    CPU(unsigned long long hz, unsigned long long ram) : _hz(hz), _ram(ram) {}

    // run queue and execution
    void queue(const Process &);
    unsigned long long execute_all();

    // accessors
    inline unsigned long long hz() { return _hz; }
    inline unsigned long long ram() { return _ram; }
};

