// ===============================
// ASSIGNMENT 19-11  DVD RENTAL STORE DATABASE
// AUTHOR: Joseph Evans
// DATE: 4/16/2026
// ===============================

// Defines a simple class representing a person's name.
// Used as the base class for customerType so that customers
// automatically inherit first/last name functionality.

#ifndef H_personType
#define H_personType

#include <string>
  
using namespace std;

/*
    personType
    ----------
    A lightweight class that stores a first and last name.

    Provides:
        - Printing the full name
        - Setting the name
        - Getting first/last name
        - Comparison operators (alphabetical ordering)

    This class is intentionally simple and acts as a base class
    for customerType, which adds account number and other fields.
*/
class personType
{
public:
    /*
        print
        -----
        Outputs the person's full name in the format:
            FirstName LastName
    */
    void print() const;

    /*
        setName
        -------
        Sets the first and last name.
        Postcondition:
            firstName = first
            lastName  = last
    */
    void setName(string first, string last);

    /*
        getFirstName
        -------------
        Returns the stored first name.
    */
    string getFirstName() const;

    /*
        getLastName
        ------------
        Returns the stored last name.
    */
    string getLastName() const;

    /*
        Constructor
        -----------
        Initializes first and last name.
        Default values are empty strings.
    */
    personType(string first = "", string last = "");

    /*
        Comparison operators
        --------------------
        These compare names alphabetically:
            - Last name first
            - If last names match, compare first names

        These are useful if personType objects are ever stored
        in a sorted structure.
    */
    bool operator==(const personType&) const;
    bool operator!=(const personType&) const;
    bool operator<=(const personType&) const;
    bool operator<(const personType&) const;
    bool operator>=(const personType&) const;
    bool operator>(const personType&) const;

private:
    string firstName; // Stores the first name
    string lastName;  // Stores the last name
};

#endif
