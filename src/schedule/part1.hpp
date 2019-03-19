#pragma once

#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>

#include "process.hpp"
#include "cpu.hpp"

bool part1_compareProcesses(const Process &l, const Process &r) { return l.cpu() > r.cpu(); }

int part1_findLightestLoad(const std::vector<CPU> &cpus)
{
    unsigned int result = cpus.size();
    unsigned long long least = ULLONG_MAX;

    unsigned long long this_cpu;
    for (unsigned int i = 0; i < cpus.size(); ++i)
    {
        this_cpu = cpus[i].peek_cycles();
        if (this_cpu < least)
        {
            result = i;
            least = this_cpu;
        }
    }

    return result;
}

void schedule_Part1()
{
    // read processes from stdin
    std::vector<Process> processes;
    Process::read_from_stdin(processes);

    // get CPUs for part 1
    std::vector<CPU> cpus;
    getCPUs_Part1(cpus);

    // header
    std::cout << cpus.size() << " CPUs, each @ " << cpus[0].hz() / 1000000
        << " GHz\n" << std::endl;

    // running totals and averages etc
    unsigned int totalNumCyclesNeeded = 0;
    unsigned int cyclesPerCPU;

    // sort processes by CPU load ascending
    std::sort(processes.begin(), processes.end(), part1_compareProcesses);

    // count up number of cycles needed in total
    for (auto it = processes.begin(); it != processes.end(); ++it)
    {
        totalNumCyclesNeeded += it->cpu();
    }

    // average load per CPU
    std::cout << totalNumCyclesNeeded << " cycles total, ";
    cyclesPerCPU = totalNumCyclesNeeded / cpus.size();
    std::cout << "distributing " << cyclesPerCPU << " cycles per CPU ("
        << cpus.size() << ")" << std::endl;

    // start with CPU 0
    unsigned int numCyclesThisCPU = 0, cpuIndex = 0;

    // attempt to schedule even load on each CPU
    auto process_it = processes.begin();

    // until we run out of CPUs...
    while (cpuIndex < cpus.size())
    {
        // until we're at desired load for this cpu (or run out of processes)...
        while (numCyclesThisCPU < cyclesPerCPU && process_it != processes.end())
        {
            numCyclesThisCPU += process_it->cpu();
            cpus[cpuIndex].queue(*process_it);
            ++process_it;
        }

        // we're at desired load now, but there are still more processes
        // move the the next CPU
        ++cpuIndex;
        numCyclesThisCPU = 0;
    }

    // we're out of CPUs now. until we run out of processes, give each one to the
    // CPU with the lightest load.
    while (process_it != processes.end())
    {
        cpuIndex = part1_findLightestLoad(cpus);
        cpus[cpuIndex].queue(*process_it);
        ++process_it;
    }

    // done scheduling
    // execute now
    std::cout << "spinning up all cpus..." << std::flush;
    float secondsTaken = 0.0f;
    for (auto it = cpus.begin(); it != cpus.end(); ++it)
    {
        float secondsThisCPU = it->execute_all();
        if (secondsThisCPU > secondsTaken)
            secondsTaken = secondsThisCPU;
    }

    std::cout << " done\n\ntotal execution time: " << secondsTaken / 1000.0f << " seconds" << std::endl;
}

