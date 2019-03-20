#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "schedule/common.hpp"
#include "process.hpp"
#include "cpu.hpp"

void part1_scheduleOne(const Process &p, std::vector<CPU> &cpus,
    unsigned int &i_cpu, const unsigned int &desiredLoad)
{
    // if this CPU can take another process, queue it up
    if (cpus[i_cpu].peek_cycles() < desiredLoad)
    {
        cpus[i_cpu].queue(p);
        return;
    }

    // if this CPU can't take another process, move on to the next one
    ++i_cpu;

    // if there are no more CPUs, pick the one with the lightest load
    if (i_cpu >= cpus.size())
    {
        i_cpu = SchedulingUtils::findLightestLoad(cpus);
    }

    // we now have our CPU. queue it up
    cpus[i_cpu].queue(p);
}

void part1_scheduleAll(std::vector<Process> &procs, std::vector<CPU> &cpus)
{
    SchedulingUtils::sortDescending(procs);

    unsigned int totalLoad = 0;
    std::for_each(procs.begin(), procs.end(), [&](Process p) { totalLoad += p.cpu(); });

    unsigned int desiredLoadPerCPU = totalLoad / cpus.size();
    
    unsigned int i_cpu = 0;
    std::for_each(procs.begin(), procs.end(), [&](Process p) {
        part1_scheduleOne(p, cpus, i_cpu, desiredLoadPerCPU);
    });
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
    std::cout << cpus.size() << " CPUs, each @ " << cpus[0].hz() / 1000000000
        << " GHz\n" << std::endl;

    // sort processes by CPU load (descending)
    SchedulingUtils::sortDescending(processes);

    // calculate cycles needed and cycles desired per cpu
    unsigned int totalNumCyclesNeeded = SchedulingUtils::sumCyclesNeeded(processes);
    unsigned int cyclesPerCPU = totalNumCyclesNeeded / cpus.size();

    std::cout << totalNumCyclesNeeded << " cycles total, "
        << "distributing " << cyclesPerCPU << " cycles per CPU ("
        << cpus.size() << ")" << std::endl;

    // schedule
    part1_scheduleAll(processes, cpus);

    // "execute"
    std::cout << "\nspinning up all cpus..." << std::flush;

    // (we don't care about this part)
    std::cout << " complete" << std::endl;

    // analyze queues
    float run_time, wait_time;
    SchedulingUtils::analyzeQueues(cpus, run_time, wait_time);

    // print analysis
    std::cout << "\navg runtime: " << run_time << " ms\navg wait time: " << wait_time << " ms" << std::endl;
}

