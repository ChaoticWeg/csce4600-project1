#include <iostream>
#include <vector>

#include "process.hpp"
#include "cpu.hpp"

void read_processes_from_stdin(std::vector<Process> &);

void getCPUs_Part1(std::vector<CPU> &);
void getCPUs_Part2(std::vector<CPU> &);
void getCPUs_Part3(std::vector<CPU> &);
void getCPUs_Part4(std::vector<CPU> &);

int main()
{
    std::vector<Process> processes;
    read_processes_from_stdin(processes);

    std::vector<CPU> cpus;
    getCPUs_Part3(cpus);

    for (auto it = cpus.begin(); it != cpus.end(); ++it)
    {
        std::cout << "CPU: " << it->hz() << " Hz ; " << it->ram() << " B RAM" << std::endl;
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

/* Get CPUs for part 1 */
void getCPUs_Part1(std::vector<CPU> &out_cpus)
{
    out_cpus.clear();
    
    int num_cpus = 5;
    for (int i = 0; i < num_cpus; ++i)
    {
        out_cpus.push_back(CPU(0, 0));
    }
}

/* Get CPUs for part 2 */
void getCPUs_Part2(std::vector<CPU> &out_cpus)
{
    out_cpus.clear();
    
    out_cpus.push_back(CPU(0, 2000000000L));
    out_cpus.push_back(CPU(0, 4000000000L));
    out_cpus.push_back(CPU(0, 4000000000L));
    out_cpus.push_back(CPU(0, 8000000000L));
}

/* Get CPUs for part 3 */
void getCPUs_Part3(std::vector<CPU> &out_cpus)
{
    out_cpus.clear();
    
    out_cpus.push_back(CPU(2000000000L, 8000000000L));
    out_cpus.push_back(CPU(3000000000L, 8000000000L));
    out_cpus.push_back(CPU(3000000000L, 8000000000L));
    out_cpus.push_back(CPU(4000000000L, 8000000000L));
}

/* Get CPUs for part 4 -- identical to part 3 */
void getCPUs_Part4(std::vector<CPU> &out_cpus)
{
    getCPUs_Part3(out_cpus);
}

