#include "process.hpp"

// PRNG
#include <cstdlib>
#include <ctime>

// utilities
#include <sstream>
#include <iostream>

// boost
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

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

Process Process::from_string(const std::string &str)
{
    std::vector<std::string> tokens;
    boost::split(tokens, str, boost::is_any_of(","));

    ProcessTuple tuple = std::make_tuple(
        std::stoi(tokens[0]),
        std::stoi(tokens[1]),
        std::stoi(tokens[2])
    );
    
    return Process::from_tuple(tuple);
}

void Process::read_from_stdin(std::vector<Process> &out_procs)
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

