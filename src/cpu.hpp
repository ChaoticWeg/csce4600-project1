#pragma once

#include <vector>
#include "process.hpp"

class CPU
{

private:
    std::vector<Process> _processes;
    unsigned long long _hz;
    unsigned long long _ram;
    unsigned long long _numCycles;
    unsigned int _nextPid = 0;

public:
    // constructor: initialize private instance fields
    CPU(unsigned long long hz, unsigned long long ram) : _hz(hz), _ram(ram) {}

    // run queue and execution
    void queue(const Process &);
    inline unsigned long long peek_cycles() const { return _numCycles; }
    float execute_all() const;
    float execute_one();
    float remaining_time() const;
    unsigned long queue_size() const;

    // accessors
    inline unsigned long long hz() { return _hz; }
    inline unsigned long long ram() { return _ram; }
};

void getCPUs_Part1(std::vector<CPU> &);
void getCPUs_Part2(std::vector<CPU> &);
void getCPUs_Part3(std::vector<CPU> &);
void getCPUs_Part4(std::vector<CPU> &);

