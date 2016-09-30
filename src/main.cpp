//Sam Goodrick sdg31@zips.uakron.edu

#include <iostream>
#include "number.hpp"
#include "farith.hpp"

int main()
{
    Number n( 1013 ), m( 203 );


    add<Number, int>( n, m ).Print();
    sub<Number, int>( n, m ).Print();
    mul<Number, int>( n, m ).Print();
    div<Number, int>( n, m ).Print();
    rem<Number, int>( n, m ).Print();
    
    return 0; 
}

