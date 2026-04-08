#ifndef H_customerBTreeType
#define H_customerBTreeType

#include "binarySearchTree.h"
#include "customer.h"

// Create a class in customerBinaryTree.h that is derived from bSearchTreeType
class customerBTreeType : public bSearchTreeType<customerType>
{
public:
    // Searches tree for cusotmer using acct ID & returns
    // true if found, false if not found.
    bool custSearchId(int id);

    // Find customer by ID and removes the DVD from their rentedDVDTree.
    void custReturnDVD(int id, string title);

    // Find customer by ID and adds the DVD to their rentedDVDTree.
    void custRentDVD(int id, string title);

    // Shows number of DVDs the customer is current renting.
    int custGetNoOfRentals(int id);

    // Shows all DVDs rented by each customer.
    void rentedDVDsInfo();
};

#endif