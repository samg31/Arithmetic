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

Number::Number( const Number& rhs )
    :mDigits( new unsigned int[PRECISION]() )
{
    for( int i = 0; i < PRECISION; ++i )
    {
	mDigits[i] = rhs.mDigits[i];
    }
}

Number::Number( int value )
    :mDigits( new unsigned int[PRECISION]() )
{
    int i = 0;
    while( value )
    {
	mDigits[i] = value % mBase;
	value /= mBase;
	++i;
    }    
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

Number& Number::operator=( Number rhs )
{
    for( int i = 0; i < PRECISION; ++i )
	mDigits[i] = rhs.mDigits[i];
    return *this;
}

unsigned int& Number::operator[]( const int index )
{
    return mDigits[index];
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
	carry = 0;
	if( temp < mBase )
	    mDigits[i] = temp;
	else
	{
	    mDigits[i] = temp - mBase;
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

    return *this;
}

bool Number::operator==( Number const& rhs ) const
{
    for( int i = 0; i < PRECISION; ++i )
	if( mDigits[i] != rhs.mDigits[i] )
	    return false;
    return true;
}

bool Number::operator==( int rhs ) const
{
    Number n;
    n = rhs;
    int lSigBit = FindSigFigs();
    int rSigBit = n.FindSigFigs();
    for( int i = 0; i < std::max( lSigBit, rSigBit ); ++i )
	if( mDigits[i] != n.mDigits[i] ) return false;
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

    if( lSigBit >= rSigBit )
    {
	for( int i = lSigBit; i > 0; --i )
	    if( mDigits[i] > rhs.mDigits[i] )
		return true;
    }
    else if( rSigBit > lSigBit )
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

const unsigned int Number::operator[]( int index ) const
{
    return mDigits[index];
}

int Number::FindSigFigs() const
{
    for( int i = PRECISION - 1; i >= 0; --i )
	if( mDigits[i] != 0 )
	    return i + 1;
    return 1;
}

Number Number::BaselessDiv2()
{
    int sig = FindSigFigs();
    int carry = 0;
    Number n;

    for( int i = sig - 1; i >= 0; --i )
    {
	int temp = mDigits[i] + mBase*carry;
	n.mDigits[i] = temp / 2;
	if( temp % 2 == 0 )
	    carry = 0;
	else
	    carry = 1;
    }
    return n;
}

Number Number::BaselessMul2()
{
    int sig = FindSigFigs();
    Number n;

    for( int i = sig - 1; i >= 0; --i )
    {
	n.mDigits[i] = mDigits[i] * 2;
	if( n.mDigits[i] >= mBase )
	{
	    n.mDigits[i] -= mBase;
	    ++n.mDigits[i + 1];
	}
    }

    return n;
}

Number Number::Mul( Number n, int x )
{
    if( x == 1 ) return n;
    //if( !(x % 2) ) add( n += n, n.BaselessDiv2() );
    else n;
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
