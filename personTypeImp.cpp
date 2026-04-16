// ===============================
// ASSIGNMENT 19-11  DVD RENTAL STORE DATABASE
// AUTHOR: Joseph Evans
// DATE: 4/16/2026
// ===============================

// Implements the personType class defined in personType.h.
// Provides basic name storage and comparison functionality.

#include <iostream>
#include <string>
#include "personType.h"

using namespace std;

/*
    print
    -----
    Outputs the person's full name in the format:
        FirstName LastName
*/
void personType::print() const
{
    cout << firstName << " " << lastName;
}

/*
    setName
    -------
    Sets the first and last name.
*/
void personType::setName(string first, string last)
{
    firstName = first;
    lastName = last; 
}

/*
    getFirstName
    -------------
    Returns the stored first name.
*/
string personType::getFirstName() const
{
    return firstName;
}

/*
    getLastName
    ------------
    Returns the stored last name.
*/
string personType::getLastName() const
{
    return lastName;
}

/*
    Constructor
    -----------
    Initializes first and last name.
*/
personType::personType(string first, string last)
{
    firstName = first;
    lastName = last;
}

/*
    operator==
    ----------
    Returns true if both first and last names match.
*/
bool personType::operator==(const personType& right) const
{
    return(firstName == right.firstName &&
           lastName == right.lastName);
}

/*
    operator!=
    ----------
    Returns true if either first or last name differs.
*/
bool personType::operator!=(const personType& right) const
{
    return(firstName != right.firstName ||
           lastName != right.lastName);
}

/*
    operator<=
    ----------
    Alphabetical comparison:
        this < right  OR  this == right
*/
bool personType::operator<=(const personType& right) const
{
    return(*this < right || *this == right);
}

/*
    operator<
    ---------
    Alphabetical ordering:
        - Compare last names first
        - If last names match, compare first names
*/
bool personType::operator<(const personType& right) const
{
    return((lastName < right.lastName) ||
           (lastName == right.lastName &&
            firstName < right.firstName));
}

/*
    operator>=
    ----------
    Alphabetical comparison:
        this > right  OR  this == right
*/
bool personType::operator>=(const personType& right) const
{
    return(*this > right || *this == right);
}

/*
    operator>
    ---------
    Alphabetical ordering (reverse of operator<)
*/
bool personType::operator>(const personType& right) const
{
    return((lastName > right.lastName) ||
           (lastName == right.lastName &&
            firstName > right.firstName));
}
