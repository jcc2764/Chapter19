// ===============================
// ASSIGNMENT 19-11  DVD RENTAL STORE DATABASE
// AUTHOR: Joseph Evans
// DATE: 4/16/2026
// ===============================

#ifndef H_customerBTreeType
#define H_customerBTreeType

#include <string>
#include "binarySearchTree.h"
#include "customer.h"

using namespace std;

/*
    customerBTreeType
    -----------------
    A binary search tree specialized for storing customerType objects.

    The BST ordering is based on customer account number because
    customerType overloads comparison operators (<, >, ==, etc.)
    to compare ONLY by account number.

    This class adds higher‑level operations specific to the DVD store:
        - Search by ID
        - Search by full name (case‑insensitive)
        - Rent/return DVDs for a customer
        - Print all customers who currently have rentals
*/
class customerBTreeType: public bSearchTreeType<customerType>
{
public:

    /*
        custSearchId
        ------------
        Returns true if a customer with the given account number exists.
    */
    bool custSearchId(int id);

    /*
        custRentDVD
        -----------
        Finds the customer by ID and adds a DVD title to their rental list.
        If the ID does not exist, prints an error message.
    */
    void custRentDVD(int id, string title);

    /*
        custReturnDVD
        -------------
        Finds the customer by ID and removes a DVD title from their rental list.
        If the ID does not exist, prints an error message.
    */
    void custReturnDVD(int id, string title);

    /*
        custGetNoOfRentals
        -------------------
        Returns how many DVDs the customer with the given ID has rented.
        If the customer does not exist, returns -1.
    */
    int custGetNoOfRentals(int id);

    /*
        rentedDVDsInfo
        --------------
        Performs an inorder traversal of the BST and prints full info
        ONLY for customers who currently have at least one rental.
    */
    void rentedDVDsInfo();

    /*
        getCustomerById
        ----------------
        Returns a pointer to the customer with the given ID,
        or nullptr if not found.
    */
    customerType* getCustomerById(int id);

    /*
        getCustomerByName
        ------------------
        Searches the entire BST for a customer whose full name matches
        the given string (case‑insensitive).
        Returns a pointer to the customer or nullptr if not found.
    */
    customerType* getCustomerByName(const string& fullName);

private:

    /*
        findCustomer
        ------------
        Internal helper that performs a BST search by account number.
        Returns a pointer to the matching customer or nullptr.
    */
    customerType* findCustomer(int id);
};

#endif
