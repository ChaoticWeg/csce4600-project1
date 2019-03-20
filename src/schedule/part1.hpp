#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "schedule/common.hpp"
#include "process.hpp"
#include "cpu.hpp"

bool part1_compareProcesses(const Process &l, const Process &r) { return l.cpu() > r.cpu(); }

void schedule_Part1()
{
    // read processes from stdin
    std::vector<Process> processes;
    Process::read_from_stdin(processes);

    // get CPUs for part 1
    std::vector<CPU> cpus;
    getCPUs_Part1(cpus);

    // header
    std::cout << cpus.size() << " CPUs, each @ " << cpus[0].hz() / 1000000000
        << " GHz\n" << std::endl;

    // running totals and averages etc
    unsigned int totalNumCyclesNeeded = 0;
    unsigned int cyclesPerCPU;

    // sort processes by CPU load ascending
    std::sort(processes.begin(), processes.end(), part1_compareProcesses);

    // count up number of cycles needed in total
    std::for_each(processes.begin(), processes.end(),
        [&](Process p){ totalNumCyclesNeeded += p.cpu(); });

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
        cpuIndex = SchedulingUtils::findLightestLoad(cpus);
        cpus[cpuIndex].queue(*process_it);
        ++process_it;
    }

    // done scheduling
    // execute now
    std::cout << "\nspinning up all cpus..." << std::flush;

    // (we don't care about this part)
    std::cout << " complete" << std::endl;

    // get a vector containing runtime for each cpu
    // (this makes calculations easier and less taxing later)
    std::vector<float> runtimes; runtimes.reserve(cpus.size());
    std::transform(cpus.begin(), cpus.end(), std::back_inserter(runtimes),
        [](CPU c){ return c.execute_all(); });

    // sort the runtimes from low to high
    std::sort(runtimes.begin(), runtimes.end(),
        [](const float &l, const float &r){ return l < r; });


    // get execution time (time for longest-running cpu to finish
    float runtime = runtimes.back(); runtimes.pop_back();
    std::cout << "execution time: " << runtime << "ms" << std::endl;
    
    // calculate waiting time
    // (that is, the amount of time each other cpu spent waiting)
    float waitingTime = 0.0f;
    std::for_each(runtimes.begin(), runtimes.end(), [&](float f) { waitingTime += runtime - f; }); 
    std::cout << "waiting time: " << waitingTime << "ms" << std::endl;
}

