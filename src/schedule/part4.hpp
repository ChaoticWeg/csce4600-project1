#pragma once

#include <vector>

#include "process.hpp"
#include "cpu.hpp"

#include "common.hpp"

void part4_scheduleOne(const Process &p, std::vector<CPU> &cpus)
{
    unsigned int i_cpu = SchedulingUtils::findShortestWait(p, cpus);
    cpus[i_cpu].queue(p);
}

void part4_scheduleAll(std::vector<Process> &procs, std::vector<CPU> &cpus)
{
    SchedulingUtils::sortAscending(procs);
    std::for_each(procs.begin(), procs.end(), [&](Process p) { part4_scheduleOne(p, cpus); });
}

void schedule_Part4()
{
    std::vector<Process> processes;
    Process::read_from_stdin(processes);

    std::vector<CPU> cpus;
    getCPUs_Part4(cpus);

    unsigned int i_cpu = 0;
    std::for_each(cpus.begin(), cpus.end(), [&](CPU c) {
        std::cout << "CPU " << i_cpu++ << ": "
            << c.hz() / 1000000000 << " GHz; "
            << c.ram() / 1000000 << " MB RAM"
            << std::endl;
    });

    part4_scheduleAll(processes, cpus);

    float rt, wt;
    SchedulingUtils::analyzeQueues(cpus, rt, wt);

    std::cout << "\navg runtime: " << rt << "\navg wait time: " << wt << std::endl;
}

