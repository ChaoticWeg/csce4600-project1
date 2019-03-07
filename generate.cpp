#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "process.hpp"

int printUsage(std::string);

int main(int argc, char **argv)
{
    // bail out if wrong args
    if (argc != 2)
        return printUsage(std::string(argv[0]));

    int numProcesses = boost::lexical_cast<int>(argv[1]);
    std::cerr << "generating " << numProcesses << " processes and dumping to stdout" << std::endl;

    for (int i = 0; i < numProcesses; i++)
    {
        Process proc = Process::generate();
        std::cout << proc.to_string() << ";" << std::flush;
    }

    std::cout << std::endl; // newline and flush
    return 0;
}

int printUsage(std::string name)
{
    std::cerr
            << "generates N simulated processes and dumps to stdout.\n\n"
            << "usage: " << name << " <count>"
            << "\n    <count> - number of processes to generate\n"
            << "\n** note - highly recommended to pipe stdout to a file"
            << std::endl; // newline and flush
    return 1;
}
