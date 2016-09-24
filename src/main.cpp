//Sam Goodrick sdg31@zips.uakron.edu

#include <iostream>
#include "number.hpp"

int main()
{
    Number n;
    Number m;
    n = 128;
    m = 127;
    std::cout << (m > n) << std::endl;
    std::cout << (m >= n) << std::endl;
    std::cout << (m < n) << std::endl;
    std::cout << (m <= n) << std::endl;
}
