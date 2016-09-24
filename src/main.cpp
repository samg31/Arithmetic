//Sam Goodrick sdg31@zips.uakron.edu

#include <iostream>
#include "number.hpp"

int main()
{
    Number n;
    n = 1;
    n << 7;
    std::cout << n.FindSigFigs() << std::endl;
    n.Print();
    return 0; 
}
