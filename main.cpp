#include <iostream>
#include <vector>

#include "process.hpp"
#include "cpu.hpp"
#include "schedule.hpp"

int main()
{
    std::vector<Process> procs;
    Process::read_from_stdin(procs);

    for (auto it = procs.begin(); it != procs.end(); ++it)
    {
        std::cout << "PID " << it->pid() << ": "
            << it->cpu() << " cycles, " << it->mem() << " bytes"
            << std::endl;
    }

    return 0;
}

