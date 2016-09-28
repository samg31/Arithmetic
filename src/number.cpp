//Sam Goodrick sdg31@zips.uakron.edu

#include "number.hpp"
#include <iostream>
#include <algorithm>
#include <cassert>

#define PRECISION 2048

// calling default constructor on int initializes all 2048 integers to 0
Number::Number()
    :mDigits( new unsigned int[PRECISION]() ), mSigFigs()
{
}

Number& Number::operator=( Number rhs )
{
    for( int i = 0; i < PRECISION; ++i )
	mDigits[i] = rhs.mDigits[i];
}

Number& Number::operator=( int rhs )
{
    int i = 0;
    while( rhs )
    {
	mDigits[i] = rhs % mBase;
	rhs /= mBase;
	++i;
    }
}

Number& Number::operator<<( int rhs )
{
    while( rhs )
    {
	PushFront( 0 );
	--rhs;
    }
}

Number& Number::operator>>( int rhs )
{
    while( rhs )
    {
	int SigBit = FindSigFigs();
	for( int i = 0; i < SigBit; ++i )
	{
	    mDigits[i] = mDigits[i + 1];
	}
	mDigits[SigBit - 1] = 0;
	--rhs;
    }
}

Number& Number::operator+=( const Number& rhs )
{
    int carry = 0;
    int lSigBit = FindSigFigs();
    int rSigBit = rhs.FindSigFigs();

    int i;
    for( i = 0; i < std::max( lSigBit, rSigBit ); ++i )
    {
	int temp = mDigits[i] + rhs.mDigits[i] + carry;
	if( temp < mBase )
	    mDigits[i] = temp;
	else if( temp == mBase )
	{
	    mDigits[i] = 0;
	    carry = 1;
	}
	else if( temp > mBase )
	{
	    mDigits[i] = mBase - temp;
	    carry = temp / mBase;
	}
    }
    mDigits[i] = carry;

    return *this;
}

Number& Number::operator-=( const Number& rhs )
{
    int lSigBit = FindSigFigs();
    int rSigBit = rhs.FindSigFigs();
    int borrow = 0;

    for( int i = 0; i < std::max( lSigBit, rSigBit ); ++i )
    {
	if( mDigits[i] >= ( rhs.mDigits[i] + borrow ) )
	{
	    mDigits[i] -= ( rhs.mDigits[i] + borrow );
	    borrow = 0;
	}
	else
	{
	    mDigits[i] += mBase;
	    mDigits[i] -= ( rhs.mDigits[i] + borrow );
	    borrow = 1;
	}

    }
    
}

bool Number::operator==( Number const& rhs ) const
{
    for( int i = 0; i < PRECISION; ++i )
	if( mDigits[i] != rhs.mDigits[i] )
	    return false;
    return true;
}

bool Number::operator!=( Number const& rhs ) const
{
    return !( *this == rhs );
}

bool Number::operator>( Number const& rhs ) const
{
    int lSigBit = FindSigFigs() - 1;
    int rSigBit = rhs.FindSigFigs() - 1;

    if( lSigBit > rSigBit )
	for( int i = lSigBit; i > 0; --i )
	    if( mDigits[i] > rhs.mDigits[i] )
		return true;
    if( rSigBit > lSigBit )
    	for( int i = rSigBit; i > 0; --i )
	    if( rhs.mDigits[i] > mDigits[i] )
		return false;
		
    return false;
}

bool Number::operator<( Number const& rhs ) const
{
    return !( *this > rhs ) && !( *this == rhs );
}

bool Number::operator>=( Number const& rhs ) const
{
    return !( *this < rhs );
}

bool Number::operator<=( Number const& rhs ) const
{
    return !( *this > rhs );
}

int Number::FindSigFigs() const
{
    for( int i = PRECISION - 1; i >= 0; --i )
	if( mDigits[i] != 0 )
	    return i + 1;
}

void Number::PushFront( int bit )
{
    assert( bit == 0 || bit == 1 );
    
    for( int i = FindSigFigs() - 1; i >= 0; --i )
	mDigits[i + 1] = mDigits[i];
    mDigits[0] = bit;
}

void Number::Print() const
{
    for( int i = FindSigFigs() - 1; i >= 0; --i )
	std::cout << mDigits[i];
    std::cout << std::endl;
}
