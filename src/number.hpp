//Sam Goodrick, sdg31@zips.uakron.edu

#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <memory>

class Number
{
private:
    std::unique_ptr<unsigned int[]> mDigits;
    int mSigFigs;
    const int mBase = 2;
public:
    // CONSTRUCTORS
    Number();

    // NON CONST OPERATORS
    Number& operator=( Number rhs );
    //assignment operator that takes an int and converts into a bit array
    Number& operator=( int rhs );
    Number& operator<<( int rhs );
    Number& operator>>( int rhs );

    // ARITHMETIC OPERATORS
    Number& operator+=( const Number& rhs );
    Number& operator-=( const Number& rhs );

    // CONST OPERATORS
    bool operator==( Number const& rhs ) const;
    bool operator!=( Number const& rhs ) const;
    bool operator>( Number const& rhs ) const;
    bool operator<( Number const& rhs ) const;
    bool operator>=( Number const& rhs ) const;
    bool operator<=( Number const& rhs ) const;

    // FUNCTIONS THAT RETURN A VALUE
    int FindSigFigs() const;

    // FUNCTIONS THAT RETURN VOID
    void PushFront( int bit );
    void Print() const;
};

#endif
