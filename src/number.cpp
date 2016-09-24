//Sam Goodrick sdg31@zips.uakron.edu

#include "number.hpp"
#include <algorithm>
#include <iostream>

constexpr int PRECISION = 2048;

// calling default constructor on int initializes all  2048 integers to 0
Number::Number()
    :mDigits( new int[PRECISION]() ), mSigFigs()
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
	mDigits[i] = rhs % 2;
	rhs /= 2;
	++i;
    }
}

Number& Number::operator<<( int rhs )
{
    while( rhs )
    {
	
	--rhs;
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
    int lSigBit = FindSigFigs();
    int rSigBit = rhs.FindSigFigs();

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
    for( int i = PRECISION - 1; i > 0; --i )
	if( mDigits[i] != 0 )
	    return i;
}
