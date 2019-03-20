#pragma once

#include <vector>
#include <climits>
#include <algorithm>

#include "cpu.hpp"
#include "process.hpp"

namespace SchedulingUtils
{
    unsigned long findLightestLoad(const std::vector<CPU> &cpus)
    {
        unsigned long result = cpus.size();
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

    bool boolAscending(const Process &l, const Process &r) { return l.cpu() < r.cpu(); }
    bool boolDescending(const Process &l, const Process &r) { return l.cpu() > r.cpu(); }

    bool floatsAscending(const float &l, const float &r) { return l < r; }

    void sortAscending(std::vector<Process> &procs)
    {
        std::sort(procs.begin(), procs.end(), boolAscending);
    }

    void sortDescending(std::vector<Process> &procs)
    {
        std::sort(procs.begin(), procs.end(), boolDescending);
    }

    unsigned int sumCyclesNeeded(std::vector<Process> procs)
    {
        unsigned int result = 0;
        std::for_each(procs.begin(), procs.end(),
            [&](Process p){ result += p.cpu(); });
        return result;
    }

    void analyzeQueues(std::vector<CPU> &cpus, float &rt, float &wt)
    {
        unsigned int totalProcs = 0; // total number of processes
        float totalRt = 0;           // total running time in seconds
        float totalWt = 0;           // total wait time in seconds

        // calculate total running time and wait time
        for (CPU &cpu : cpus) {
            float cpuRt = 0; // running time for this cpu
            while (cpu.queue_size() > 0) {
                totalProcs++;
                totalWt += cpuRt;
                cpuRt += cpu.execute_one(); // sum running time for cpu
            }
            totalRt += cpuRt;
        }

        // calculate average running time and wait times
        rt = (totalRt / totalProcs) * 1000;
        wt = (totalWt / totalProcs) * 1000;
    }
}

