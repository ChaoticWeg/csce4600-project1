#include <iostream>
#include <vector>

#include "process.hpp"

void read_processes_from_stdin(std::vector<Process> &);

int main()
{
    std::vector<Process> processes;
    read_processes_from_stdin(processes);

    for (auto it = processes.begin(); it != processes.end(); ++it)
    {
        Process p = *it;
        std::cout << "PID: " << p.pid() << " ; CPU: " << p.cpu()
            << " ; RAM: " << p.mem() << std::endl;
    }
    
    return 0;
}

void read_processes_from_stdin(std::vector<Process> &out_procs)
{
    out_procs.clear();

    for (std::string raw; std::getline(std::cin, raw, ';');)
    {
        // newline means done -- empty string is not likely
        if (raw.compare("\n") == 0) break;
        if (raw.compare("") == 0) break;

        out_procs.push_back(Process::from_string(raw));
    }
}

