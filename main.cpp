#include <iostream>
#include <boost/lexical_cast.hpp>

#include "schedule.hpp"

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <part>" << std::endl;
        return 1;
    }

    int part;

    try
    {
        part = boost::lexical_cast<int>(argv[1]);
    }
    catch (const boost::bad_lexical_cast &)
    {
        std::cerr << "Invalid part number [1-4]: " << argv[1] << std::endl;
        return 1;
    }

    switch (part)
    {
        case 1:
            schedule_Part1();
            break;
        case 2:
            schedule_Part2();
            break;
        case 3:
            schedule_Part3();
            break;
        case 4:
            schedule_Part4();
            break;
        default:
            std::cerr << "Unknown or unimplemented part number: " << argv[1] << std::endl;
            return 1;
    }
    
    return 0;
}

