#include <vector>
#include <algorithm>

#include "cpu.hpp"

/* Add a process to this CPU's run queue */
void CPU::queue(const Process &proc)
{
    _processes.push_back(proc);
    _numCycles += proc.cpu();
}

/* Execute all queued processes and return the number of seconds taken in total */
float CPU::execute_all() const
{
    return remaining_time();
}

/**
 * Executes the process at the front of the queue, then increments the next PID.
 *
 * @return The amount of time in seconds the process took to run.
 */
float CPU::execute_one()
{
    Process p = this->_processes[this->_nextPid];
    this->_nextPid++;
    return p.cpu() / (this->_hz * 1.0f);
}

/* Get the amount of time remaining until the next job can be started */
float CPU::remaining_time() const
{
    float result = 0;
    std::for_each(_processes.begin(), _processes.end(), [&](Process p) {
        float timeThisJob = p.cpu() / (_hz * 1.0f);
        result += timeThisJob;
    });
    return result;
}

/**
 * @return Number of processes remaining in the queue
 */
unsigned long CPU::queue_size() const {
    return this->_processes.size() - _nextPid;
}

/* Get CPUs for part 1 */
void getCPUs_Part1(std::vector<CPU> &out_cpus)
{
    out_cpus.clear();
    
    int num_cpus = 5;
    for (int i = 0; i < num_cpus; ++i)
    {
        out_cpus.push_back(CPU(2000000000L, 0));
    }
}


/* Get CPUs for part 2 */
void getCPUs_Part2(std::vector<CPU> &out_cpus)
{
    out_cpus.clear();
    
    out_cpus.push_back(CPU(2000000000L, 2000000000L));
    out_cpus.push_back(CPU(2000000000L, 2000000000L));
    out_cpus.push_back(CPU(2000000000L, 4000000000L));
    out_cpus.push_back(CPU(2000000000L, 4000000000L));
    out_cpus.push_back(CPU(2000000000L, 8000000000L));
}

/* Get CPUs for part 3 */
void getCPUs_Part3(std::vector<CPU> &out_cpus)
{
    out_cpus.clear();
    
    out_cpus.push_back(CPU(2000000000L, 8000000000L));
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

