//Sam Goodrick sdg31@zips.uakron.edu

#include <iostream>
#include "number.hpp"

int main()
{
    Number n;
    n = 1;
    n << 2;
    n.Print();
    n >> 2;
    n.Print();
    return 0; 
}
