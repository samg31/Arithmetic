#ifndef FARITH_HPP
#define FARITH_HPP

#include "number.hpp"
#include <cassert>

template<typename N, typename D> bool even( N number );
template<typename N, typename D> N add( N num1, N num2 );
template<typename N, typename D> N sub( N num1, N num2 );
template<typename N, typename D> N mul( N num1, N num2 );
template<typename N, typename D> N div( N num1, N num2 );
template<typename N, typename D> N rem( N num1, N num2 );
template<typename N> N lshift( N num1, int amount );
template<typename N> N rshift( N num1, int amount );

template<typename N, typename D>
N add( N num1, N num2 )
{
    assert( num1.mBase == num2.mBase );
    
    D carry = 0;
    int lSigBit = num1.FindSigFigs();
    int rSigBit = num2.FindSigFigs();

    int i;
    for( i = 0; i < std::max( lSigBit, rSigBit ); ++i )
    {
	D temp = num1[i] + num2[i] + carry;
	carry = 0;
	if( temp < num1.mBase )
	    num1[i] = temp;
	else
	{
	    num1[i] = temp - num1.mBase;
	    carry = temp / num1.mBase;
	}
    }
    num1[i] = carry;

    return num1;
}

template<typename N, typename D>
N sub( N num1, N num2 )
{
    assert( num1.mBase == num2.mBase );

    int lSigBit = num1.FindSigFigs();
    int rSigBit = num2.FindSigFigs();
    D borrow = 0;

    for( int i = 0; i < std::max( lSigBit, rSigBit ); ++i )
    {
	if( num1[i] >= ( num2[i] + borrow ) )
	{
	    num1[i] -= ( num2[i] + borrow );
	    borrow = 0;
	}
	else
	{
	    num1[i] += num1.mBase;
	    num1[i] -= ( num2[i] + borrow );
	    borrow = 1;
	}
    }

    return num1;
}

template<typename N, typename D>
N mul( N num1, N num2 )
{
    if( num2 == 1 )
	return num1;
    if( even<N, D>( num2 ) )
	return mul<N, D>( lshift<N>( num1, 1 ),
				 rshift<N>( num2, 1 ) );
    else
	return mul<N, D>( add<N, D>( num1, lshift<N>(num1, 1) ),
		    rshift<N>( num2, 1 ) );

}

template<typename N, typename D>
N div( N num1, N num2 )
{
    if( num1 < num2 )
	return N( 0 );
    else
	return add<N, D>( div<N, D>( sub<N, D>( num1, num2 ), num2 ), N( 1 ) );
    
}

template<typename N, typename D>
bool even( N number )
{
    if( number.mBase % 2 == 0 )
	return( number[0] % 2 == 0 );

    int sig = number.FindSigFigs();
    D temp;
    for( int i = 0; i < sig; ++i )
	temp += number[i];

    return( temp % 2 == 0 );
}

template<typename N, typename D>
N rem( N num1, N num2 )
{
    if( num1 >= lshift<N>( num2, 1 ) )
    {
	num1 = rem<N, D>( num1, lshift<N>( num2, 1 ) );
	if( num1 < num2 )
	    return num1;
    }
    return sub<N, D>( num1, num2 );
}

template<typename N>
N lshift( N num1, int amount )
{
    while( amount )
    {
	num1.PushFront( 0 );
	--amount;
    }
    
    return num1;
}

template<typename N>
N rshift( N num1, int amount )
{
    while( amount )
    {
	int SigBit = num1.FindSigFigs();
	for( int i = 0; i < SigBit; ++i )
	{
	    num1[i] = num1[i + 1];
	}
	num1[SigBit - 1] = 0;
	--amount;
    }

    return num1;
}

#endif
