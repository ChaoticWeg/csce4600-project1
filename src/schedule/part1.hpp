#pragma once

#include <vector>

#include "process.hpp"
#include "cpu.hpp"

void schedule_Part1()
{
    std::vector<Process> processes;
    Process::read_from_stdin(processes);
}

