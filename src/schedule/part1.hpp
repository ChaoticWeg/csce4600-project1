#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "process.hpp"
#include "cpu.hpp"

bool compareProcesses(const Process &l, const Process &r) { return l.cpu() < r.cpu(); }

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
    std::sort(processes.begin(), processes.end(), compareProcesses);

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
    std::cout << "scheduling for CPU " << cpuIndex << "..." << std::flush;

    // attempt to schedule even load on each CPU
    for (auto it = processes.begin(); it != processes.end(); ++it)
    {
        numCyclesThisCPU += it->cpu();

        if (numCyclesThisCPU > cyclesPerCPU && cpuIndex + 1 < cpus.size())
        {
            // move the the next CPU
            cpuIndex++;

            // we've hit the max desired cycles for this CPU
            std::cout << " done: " << numCyclesThisCPU << " cycles\n"
                << "scheduling for CPU " << cpuIndex << "..." << std::flush;

            // numCyclesThisCPU should be reset to initial value
            numCyclesThisCPU = it->cpu();
        }

        cpus[cpuIndex].queue(*it);
    }

    // done scheduling
    std::cout << " done: " << numCyclesThisCPU << " cycles" << std::endl;

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

