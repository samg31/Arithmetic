//Sam Goodrick, sdg31@zips.uakron.edu

#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <memory>

class Number
{
private:
    std::unique_ptr<unsigned int[]> mDigits;
    int mSigFigs;
public:
    const int mBase = 2;
    
    // CONSTRUCTORS
    Number();
    Number( const Number& rhs );
    Number( int value );
   
    // NON CONST OPERATORS
    //assignment operator that takes an int and converts into a bit array
    Number& operator=( int rhs );
    Number& operator=( Number rhs );
    unsigned int& operator[]( const int index );

    // ARITHMETIC OPERATORS
    Number& operator+=( const Number& rhs );
    Number& operator-=( const Number& rhs );
    Number& operator*=( const Number& rhs );
    Number& operator/=( const Number& rhs );
    Number& operator<<( int rhs );
    Number& operator>>( int rhs );

    // CONST OPERATORS
    bool operator==( Number const& rhs ) const;
    bool operator==( int rhs ) const;
    bool operator!=( Number const& rhs ) const;
    bool operator>( Number const& rhs ) const;
    bool operator<( Number const& rhs ) const;
    bool operator>=( Number const& rhs ) const;
    bool operator<=( Number const& rhs ) const;
    const unsigned int operator[]( int index ) const;
    
    // FUNCTIONS THAT RETURN A VALUE
    int FindSigFigs() const;
    Number& Sub( Number rhs );
    Number BaselessDiv2();
    Number BaselessMul2();
    Number Mul( Number n, int x );

    // FUNCTIONS THAT RETURN VOID
    void PushFront( int bit );
    void Print() const;
};

#endif
