// ===============================
// ASSIGNMENT 19-11  DVD RENTAL STORE DATABASE
// AUTHOR: Joseph Evans
// DATE: 4/16/2026
// ===============================

#ifndef H_customerType
#define H_customerType

#include <iostream>
#include "personType.h"
#include <string>
#include "binarySearchTree.h"

using namespace std;

/*
    customerType
    ------------
    Represents a single customer in the DVD store system.
    Inherits first/last name from personType and adds:

        - Account number
        - Address
        - Phone number
        - Member-since date
        - A binary search tree of rented DVDs

    The rented DVDs are stored in a BST of strings so that
    insertion, deletion, and lookup are efficient.
*/
class customerType: public personType
{
    // Allows formatted printing using: cout << customerObject;
    friend ostream& operator<<(ostream&, customerType&);

public:
    // Prints: acctNo firstName lastName noOfRentals
    void print();

    // Sets first name, last name, and account number
    void setCustInfo(string first, string last, int acctNo);

    // Adds a DVD title to the customer's rental BST
    void rentDVD(string);

    // Removes a DVD title from the customer's rental BST
    void returnDVD(string);

    // Returns how many DVDs the customer currently has rented
    int getNoOfRentals();

    // Returns the customer's account number
    int getAcctNo();

    // Prints all DVDs rented by this customer (inorder traversal)
    void printRentedDVD();

    // Constructor with parameters
    customerType(string first, string last, int acctNo);

    // Default constructor
    customerType();

    // Comparison operators (compare ONLY by account number)
    bool operator==(const customerType&) const;
    bool operator!=(const customerType&) const;
    bool operator<=(const customerType&) const;
    bool operator<(const customerType&) const;
    bool operator>=(const customerType&) const;
    bool operator>(const customerType&) const;

    // Extended info setters
    void setAddress(string addr);
    void setPhone(string ph);
    void setMemberSince(string ms);

    // Extended info getters
    string getAddress() const;
    string getPhone() const;
    string getMemberSince() const;

    /*
        Prints full customer information in a readable format:
            - ID
            - Name
            - Address
            - Phone (formatted)
            - Member since
            - List of rented DVDs
    */
    void printFullInfo();

private:
    int custAcctNo;                        // Unique account number
    bSearchTreeType<string> rentedDVDTree; // BST storing rented DVD titles

    // Extended customer information
    string address;
    string phone;
    string memberSince;
};

#endif
