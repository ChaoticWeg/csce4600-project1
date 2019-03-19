#include <vector>
#include "cpu.hpp"

/* Add a process to this CPU's run queue */
void CPU::queue(const Process &proc)
{
    _processes.push_back(proc);
}

/* Execute all queued processes and return the number of cycles taken in total */
unsigned long long CPU::execute_all() const
{
    unsigned long long result = 0;

    for (auto it = _processes.begin(); it != _processes.end(); ++it)
    {
        result += it->cpu();
    }

    return result;
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

