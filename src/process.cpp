#include "process.hpp"

// PRNG
#include <cstdlib>
#include <ctime>

// utilities
#include <sstream>

int Process::lastPid = 0;
bool Process::seeded = false;

void Process::seed()
{
    // prevent re-seeding
    if (seeded) return;

    srand(time(NULL));
    seeded = true;
}

Process Process::generate()
{
    // seed if necessary
    if (!seeded) seed();

    int pid = ++lastPid;
    int cpu = gen_cpu();
    int mem = gen_mem();

    return Process(pid, cpu, mem);
}

int Process::gen_int(int min, int max)
{
    return (rand() % max) + min;
}

Process Process::from_tuple(const ProcessTuple &t)
{
    return Process(std::get<0>(t), std::get<1>(t), std::get<2>(t));
}

ProcessTuple Process::as_tuple()
{
    return ProcessTuple(_pid, _cpu, _mem);
}

std::string Process::to_string()
{
    std::stringstream ss;
    ss << _pid << "," << _cpu << "," << _mem;
    return ss.str();
}

