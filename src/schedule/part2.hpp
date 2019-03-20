#pragma once

#include <vector>
#include <algorithm>
#include <climits>

#include "process.hpp"
#include "cpu.hpp"

void part2_scheduleOne(const Process &p, std::vector<CPU> &cpus)
{
    // CPUs that will support the memory requirement of the process
    std::vector<int> compatibleCpuIndexes;
    for (unsigned int i = 0; i < cpus.size(); ++i)
    {
        if (cpus[i].ram() >= (unsigned int) p.mem())
            compatibleCpuIndexes.push_back(i);
    }

    // find the CPU with the lightest load
    unsigned int targetCpuIndex = cpus.size();
    unsigned long long currentLightestLoad = ULLONG_MAX;
    std::for_each(compatibleCpuIndexes.begin(), compatibleCpuIndexes.end(),
            [&](unsigned int i) {
        if (cpus[i].peek_cycles() < currentLightestLoad)
        {
            targetCpuIndex = i;
            currentLightestLoad = cpus[i].peek_cycles();
        }
    });

    // queue the process on this CPU
    cpus[targetCpuIndex].queue(p);
}

void part2_scheduleAll(std::vector<Process> &procs, std::vector<CPU> &cpus)
{
    SchedulingUtils::sortAscending(procs);
    std::for_each(procs.begin(), procs.end(), [&](Process p) {
        part2_scheduleOne(p, cpus);
    });
}

void schedule_Part2()
{
    std::vector<Process> processes;
    Process::read_from_stdin(processes);

    std::vector<CPU> cpus;
    getCPUs_Part2(cpus);

    for (unsigned int i = 0; i < cpus.size(); ++i)
    {
        std::cout << "CPU " << i << ": "
            << cpus[i].hz() / 1000000000 << " GHz; "
            << cpus[i].ram() / 1000000 << " MB RAM" << std::endl;
    }

    part2_scheduleAll(processes, cpus);

    float run_time, wait_time;
    SchedulingUtils::analyzeQueues(cpus, run_time, wait_time);

    std::cout << "\nrun time: " << run_time << " ms"
        "\nwait time: " << wait_time << " ms" << std::endl;
}

