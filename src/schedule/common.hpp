#pragma once

#include <vector>
#include <climits>
#include <algorithm>

#include "cpu.hpp"
#include "process.hpp"

namespace SchedulingUtils
{
    unsigned int findLightestLoad(const std::vector<CPU> &cpus)
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

    bool boolAscending(const Process &l, const Process &r) { return l.cpu() < r.cpu(); }
    bool boolDescending(const Process &l, const Process &r) { return l.cpu() > r.cpu(); }

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
}

