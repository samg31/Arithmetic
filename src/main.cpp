//Sam Goodrick sdg31@zips.uakron.edu

#include <iostream>
#include "number.hpp"

int main()
{
    Number n, m;
    n = 17;
    m = 2;
    n -= m;
    n.Print();
    return 0; 
}

