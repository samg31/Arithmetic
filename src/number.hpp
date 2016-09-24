//Sam Goodrick, sdg31@zips.uakron.edu

#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <memory>

class Number
{
private:
    std::unique_ptr<int[]> mDigits;
    int mSigFigs;
public:
    // CONSTRUCTORS
    Number();

    // NON CONST OPERATORS
    Number& operator=( Number rhs );
    //assignment operator that takes an int and converts into a bit array
    Number& operator=( int rhs );
    Number& operator<<( int rhs );

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