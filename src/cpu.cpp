#include "cpu.hpp"

/* Add a process to this CPU's run queue */
void CPU::queue(const Process &proc)
{
    _processes.push_back(proc);
}

/* Execute all queued processes and return the number of cycles taken in total */
long int CPU::execute_all()
{
    long int result = 0;

    for (auto it = _processes.begin(); it != _processes.end(); ++it)
    {
        result += it->cpu();
    }

    return result;
}

