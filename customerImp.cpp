// ===============================
// ASSIGNMENT 19-11  DVD RENTAL STORE DATABASE
// AUTHOR: Joseph Evans
// DATE: 4/16/2026
// ===============================

#include <iostream>
#include <string>
#include "customer.h"
#include <iomanip>

using namespace std;

/*
    formatPhone
    -----------
    Utility function to convert a raw 10‑digit phone number
    (e.g., "9845557733") into a formatted version:
        (984)555-7733

    If the string is not exactly 10 digits, it is returned unchanged.
*/
static string formatPhone(const string& ph)
{
    if (ph.length() != 10)
        return ph;  // fallback if bad data

    return "(" + ph.substr(0,3) + ")" +
           ph.substr(3,3) + "-" +
           ph.substr(6,4);
}

/*
    print
    -----
    Prints a compact summary of the customer:
        acctNo firstName lastName numberOfRentals
*/
void customerType::print()
{
    cout << custAcctNo << " ";
    personType::print();
    cout << " " << rentedDVDTree.treeNodeCount() << endl;
}

/*
    setCustInfo
    -----------
    Sets the customer's first name, last name, and account number.
*/
void customerType::setCustInfo(string first, string last, int acctNo)
{
    personType::setName(first,last);
    custAcctNo = acctNo;
}

/*
    rentDVD
    -------
    Inserts a DVD title into the customer's rental BST.
*/
void customerType::rentDVD(string title)
{
    rentedDVDTree.insert(title);
}

/*
    returnDVD
    ---------
    Removes a DVD title from the customer's rental BST.
*/
void customerType::returnDVD(string title)
{
    rentedDVDTree.deleteNode(title);
}

/*
    getNoOfRentals
    --------------
    Returns how many DVDs the customer currently has rented.
*/
int customerType::getNoOfRentals()
{
    return rentedDVDTree.treeNodeCount();
}

/*
    getAcctNo
    ---------
    Returns the customer's account number.
*/
int customerType::getAcctNo()
{
    return custAcctNo;
}

/*
    Constructor with parameters
    ---------------------------
    Initializes the customer's name and account number.
*/
customerType::customerType(string first, string last, int acctNo)
                :personType(first,last)
{
    custAcctNo = acctNo;
}

/*
    Default constructor
    -------------------
    Initializes account number to 0.
*/
customerType::customerType()
{
    custAcctNo = 0;
}

/*
    Comparison operators
    --------------------
    All comparisons are based ONLY on account number.
    This allows customerType to be stored in a BST.
*/
bool customerType::operator==(const customerType& right) const
{
    return(custAcctNo == right.custAcctNo);
}

bool customerType::operator!=(const customerType& right) const
{
    return(custAcctNo != right.custAcctNo);
}

bool customerType::operator<=(const customerType& right) const
{
    return(custAcctNo <= right.custAcctNo);
}

bool customerType::operator<(const customerType& right) const
{
    return(custAcctNo < right.custAcctNo);
}

bool customerType::operator>=(const customerType& right) const
{
    return(custAcctNo >= right.custAcctNo);
}

bool customerType::operator>(const customerType& right) const
{
    return(custAcctNo > right.custAcctNo);
}

/*
    operator<<
    ----------
    Prints a formatted row for the customer list screen.

    Columns:
        ID | First | Last | Address | Phone | MemberSince | Rentals
*/
ostream& operator<<(ostream& os, customerType& cust)
{
    os << left
       << setw(5)  << cust.getAcctNo()
       << setw(12) << cust.getFirstName()
       << setw(15) << cust.getLastName()
       << setw(45) << cust.getAddress()
       << setw(15) << formatPhone(cust.getPhone())   // formatted phone
       << setw(15) << cust.getMemberSince()
       << setw(8)  << cust.getNoOfRentals()
       << endl;

    return os;
}

/*
    printRentedDVD
    --------------
    Prints all DVDs rented by this customer using inorder traversal.
*/
void customerType::printRentedDVD()
{
    rentedDVDTree.inorderTraversal();
}

/*
    Setters for extended customer information
*/
void customerType::setAddress(string addr)
{
    address = addr;
}

void customerType::setPhone(string ph)
{
    phone = ph;
}

void customerType::setMemberSince(string ms)
{
    memberSince = ms;
}

/*
    Getters for extended customer information
*/
string customerType::getAddress() const
{
    return address;
}

string customerType::getPhone() const
{
    return phone;
}

string customerType::getMemberSince() const
{
    return memberSince;
}

/*
    printFullInfo
    -------------
    Prints a detailed, readable customer profile:

        - ID
        - Name
        - Address
        - Phone (formatted)
        - Member since
        - List of rented DVDs (if any)

    Used by:
        - Search by ID
        - Search by Name
        - Rented DVDs report
*/
void customerType::printFullInfo()
{
    cout << "Customer ID     : " << custAcctNo << endl;

    cout << "Customer Name   : ";
    personType::print();
    cout << endl;

    cout << "Customer Address: " << address << endl;

    // Use formatted phone number here as well
    cout << "Customer Phone  : " << formatPhone(phone) << endl;

    cout << "Member Since    : " << memberSince << endl;

    cout << "        DVD Rented" << endl;
    cout << "       -----------" << endl;

    // If no DVDs rented, print "None"
    if (rentedDVDTree.treeNodeCount() == 0)
    {
        cout << "None" << endl;
    }
    else
    {
        cout << endl;
        printRentedDVD();
        cout << endl;
    }
}
