#pragma once

#include <vector>
#include <climits>

#include "cpu.hpp"

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
}

