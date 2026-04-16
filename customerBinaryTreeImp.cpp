// ===============================
// ASSIGNMENT 19-11  DVD RENTAL STORE DATABASE
// AUTHOR: Joseph Evans
// DATE: 4/16/2026
// ===============================

#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "customerBinaryTree.h"

using namespace std;

/*
    toLowerStr
    ----------
    Converts a string to lowercase.
    Used for case‑insensitive name searching.
*/
static string toLowerStr(string s)
{
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c){ return static_cast<char>(tolower(c)); });
    return s;
}

/*
    findCustomer
    ------------
    Internal helper that performs a BST search using the
    customer's account number.

    Comparison is based ONLY on account number because
    customerType overloads comparison operators accordingly.

    Returns:
        - pointer to customerType if found
        - nullptr if not found
*/
customerType* customerBTreeType::findCustomer(int id)
{
    nodeType<customerType>* current = this->root;

    // Create a temporary customer object used only for comparison.
    customerType key;
    key.setCustInfo("", "", id);

    // Standard BST search loop
    while (current != nullptr)
    {
        if (current->info == key)
            return &(current->info);   // Found the customer

        else if (current->info > key)
            current = current->lLink;  // Move left

        else
            current = current->rLink;  // Move right
    }

    return nullptr; // Not found
}

/*
    custSearchId
    ------------
    Returns true if a customer with the given ID exists.
*/
bool customerBTreeType::custSearchId(int id)
{
    return (findCustomer(id) != nullptr);
}

/*
    custRentDVD
    -----------
    Finds a customer by ID and adds a DVD title to their rental list.
    Prints an error if the ID does not exist.
*/
void customerBTreeType::custRentDVD(int id, string title)
{
    customerType* cust = findCustomer(id);

    if (cust == nullptr)
    {
        cout << "Customer ID not found." << endl;
        return;
    }

    cust->rentDVD(title);
}

/*
    custReturnDVD
    -------------
    Finds a customer by ID and removes a DVD title from their rental list.
    Prints an error if the ID does not exist.
*/
void customerBTreeType::custReturnDVD(int id, string title)
{
    customerType* cust = findCustomer(id);

    if (cust == nullptr)
    {
        cout << "Customer ID not found." << endl;
        return;
    }

    cust->returnDVD(title);
}

/*
    custGetNoOfRentals
    -------------------
    Returns the number of DVDs rented by the customer with the given ID.
    If the customer does not exist, prints an error and returns -1.
*/
int customerBTreeType::custGetNoOfRentals(int id)
{
    customerType* cust = findCustomer(id);

    if (cust == nullptr)
    {
        cout << "Customer ID not found." << endl;
        return -1;
    }

    return cust->getNoOfRentals();
}

/*
    rentedDVDsInfo
    --------------
    Performs an inorder traversal of the BST and prints full info
    ONLY for customers who currently have at least one rental.

    Uses a manual stack to avoid recursion.
*/
void customerBTreeType::rentedDVDsInfo()
{
    nodeType<customerType>* stack[1000];
    int top = -1;
    nodeType<customerType>* current = this->root;

    // Manual inorder traversal
    while (current != nullptr || top >= 0)
    {
        // Traverse left subtree
        while (current != nullptr)
        {
            stack[++top] = current;
            current = current->lLink;
        }

        // Visit node
        current = stack[top--];

        if (current->info.getNoOfRentals() > 0)
        {
            current->info.printFullInfo();
            cout << "----------------------------------------" << endl;
        }

        // Traverse right subtree
        current = current->rLink;
    }
}

/*
    getCustomerById
    ----------------
    Public wrapper for findCustomer.
*/
customerType* customerBTreeType::getCustomerById(int id)
{
    return findCustomer(id);
}

/*
    searchByNameHelper
    ------------------
    Recursive helper for searching by full name.

    Performs an inorder traversal and compares the lowercase
    "First Last" string to the target lowercase name.

    Stops early if a match is found.
*/
static void searchByNameHelper(nodeType<customerType>* p,
                               const string& targetLower,
                               customerType*& result)
{
    if (p == nullptr || result != nullptr)
        return;

    // Search left subtree
    searchByNameHelper(p->lLink, targetLower, result);

    if (result == nullptr)
    {
        // Build full name for comparison
        string fullName = p->info.getFirstName() + " " + p->info.getLastName();

        if (toLowerStr(fullName) == targetLower)
        {
            result = &(p->info);
            return;
        }
    }

    // Search right subtree
    searchByNameHelper(p->rLink, targetLower, result);
}

/*
    getCustomerByName
    ------------------
    Searches the entire BST for a customer whose full name matches
    the given string (case‑insensitive).

    Returns:
        - pointer to customerType if found
        - nullptr if not found
*/
customerType* customerBTreeType::getCustomerByName(const string& fullName)
{
    string targetLower = toLowerStr(fullName);
    customerType* result = nullptr;

    searchByNameHelper(this->root, targetLower, result);

    return result;
}

// ===============================
// SAVE CUSTOMER BASIC DATA
// ===============================
static void saveCustHelper(nodeType<customerType>* p, ofstream& out)
{
    if (!p) return;

    saveCustHelper(p->lLink, out);

    // Address is already stored as one string in customerType
    out << p->info.getAcctNo() << " "
        << p->info.getFirstName() << " "
        << p->info.getLastName() << " "
        << p->info.getAddress() << " "
        << p->info.getPhone() << " "
        << p->info.getMemberSince() << "\n";

    saveCustHelper(p->rLink, out);
}

void customerBTreeType::saveCustomersToFile(ofstream& out)
{
    saveCustHelper(this->root, out);
}

// ===============================
// SAVE CUSTOMER RENTAL DATA
// ===============================
static void saveRentHelper(nodeType<customerType>* p, ofstream& out)
{
    if (!p) return;

    saveRentHelper(p->lLink, out);

    out << p->info.getFirstName() << " "
        << p->info.getLastName() << " "
        << p->info.getAcctNo() << " "
        << p->info.getNoOfRentals() << " ";

    // redirect cout temporarily so printRentedDVD writes into the file
    std::streambuf* oldBuf = cout.rdbuf(out.rdbuf());
    p->info.printRentedDVD();   // prints titles separated by spaces
    cout.rdbuf(oldBuf);

    out << "\n";

    saveRentHelper(p->rLink, out);
}

void customerBTreeType::saveRentalsToFile(ofstream& out)
{
    saveRentHelper(this->root, out);
}
