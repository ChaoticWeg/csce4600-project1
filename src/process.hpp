#pragma once

#include <tuple>
#include <string>

// cpu range
#define PROC_MIN_CPU 10
#define PROC_MAX_CPU 50000000

// mem range
#define PROC_MIN_MEM 250
#define PROC_MAX_MEM 8000000

// typedefs
typedef std::tuple<int, int, int> ProcessTuple;

class Process
{
private:
    static int lastPid;
    static bool seeded;

    static void seed();

    static int gen_int(int, int);

    inline static int gen_cpu() { return gen_int(PROC_MIN_CPU, PROC_MAX_CPU); }
    inline static int gen_mem() { return gen_int(PROC_MIN_MEM, PROC_MAX_MEM); }

    int _pid, _cpu, _mem;

    Process(int p, int c, int m) : _pid(p), _cpu(c), _mem(m) {};


public:
    static Process generate();
    static Process from_tuple(const ProcessTuple &);
    static Process from_string(const std::string &);

    inline int pid() { return _pid; }
    inline int cpu() { return _cpu; }
    inline int mem() { return _mem; }

    ProcessTuple as_tuple();
    std::string to_string();
};

