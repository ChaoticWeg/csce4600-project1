#include <iostream>

#include "process.hpp"

int main()
{
    for (std::string raw; std::getline(std::cin, raw, ';');)
    {
        // newline means done -- empty string is not likely
        if (raw.compare("\n") == 0) break;
        if (raw.compare("") == 0) break;

        std::cout << raw << std::endl;
    }

    return 0;
}

