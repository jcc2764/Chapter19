// ===============================
// ASSIGNMENT 19-11  DVD RENTAL STORE DATABASE
// AUTHOR: Joseph Evans
// DATE: 4/16/2026
// ===============================

//Header File Binary Search Tree
#ifndef H_binarySearchTree
#define H_binarySearchTree
#include <iostream>
#include "binaryTree.h"

using namespace std;

/*
    bSearchTreeType
    ----------------
    A binary search tree built on top of binaryTreeType.

    This class adds:
        - search()
        - insert()
        - deleteNode()

    The ordering of the tree depends entirely on the comparison
    operators (<, >, ==, etc.) defined for elemType.

    In your program:
        elemType = customerType
    and customerType compares ONLY by account number.
*/
template <class elemType>
class bSearchTreeType: public binaryTreeType<elemType>
{
public:

    /*
        search
        ------
        Determines whether searchItem exists in the BST.

        Traverses the tree using standard BST rules:
            - If searchItem < current → go left
            - If searchItem > current → go right
            - If equal → found
    */
    bool search(const elemType& searchItem) const;

    /*
        insert
        ------
        Inserts insertItem into the BST.

        If a duplicate is found (same key), insertion is aborted.
        Otherwise, a new node is created and placed in the correct
        position based on BST ordering.
    */
    void insert(const elemType& insertItem);

    /*
        deleteNode
        ----------
        Removes deleteItem from the BST.

        Handles all three deletion cases:
            1. Node is a leaf
            2. Node has one child
            3. Node has two children (replace with inorder predecessor)
    */
    void deleteNode(const elemType& deleteItem);

private:

    /*
        deleteFromTree
        --------------
        Internal helper used by deleteNode().

        Removes the node pointed to by p and reconnects the tree
        appropriately depending on the deletion case.
    */
    void deleteFromTree(nodeType<elemType>* &p);
};


//
// IMPLEMENTATION SECTION
//

template <class elemType>
bool bSearchTreeType<elemType>::search(const elemType& searchItem) const
{
    nodeType<elemType> *current;
    bool found = false;

    if (this->root == nullptr)
        cout << "Cannot search an empty tree." << endl;
    else
    {
        current = this->root;

        // Standard BST search loop
        while (current != nullptr && !found)
        {
            if (current->info == searchItem)
                found = true;                 // Match found
            else if (current->info > searchItem)
                current = current->lLink;     // Go left
            else
                current = current->rLink;     // Go right
        }
    }

    return found;
}

template <class elemType>
void bSearchTreeType<elemType>::insert(const elemType& insertItem)
{
    nodeType<elemType> *current;        // Traverses the tree
    nodeType<elemType> *trailCurrent = nullptr; // Parent pointer
    nodeType<elemType> *newNode;        // New node to insert

    // Create the new node
    newNode = new nodeType<elemType>;
    newNode->info = insertItem;
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;

    // If tree is empty, new node becomes root
    if (this->root == nullptr)
        this->root = newNode;
    else
    {
        current = this->root;

        // Traverse until insertion point is found
        while (current != nullptr)
        {
            trailCurrent = current;

            if (current->info == insertItem)
            {
                // Duplicate found — abort insertion
                cout << "The item to be inserted is already "
                     << "in the tree -- duplicates are not allowed."
                     << endl;
                return;
            }
            else if (current->info > insertItem)
                current = current->lLink;  // Go left
            else
                current = current->rLink;  // Go right
        }

        // Insert new node as left or right child
        if (trailCurrent->info > insertItem)
            trailCurrent->lLink = newNode;
        else
            trailCurrent->rLink = newNode;
    }
}

template <class elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType& deleteItem)
{
    nodeType<elemType> *current;       // Traverses the tree
    nodeType<elemType> *trailCurrent;  // Parent pointer
    bool found = false;

    if (this->root == nullptr)
        cout << "Cannot delete from an empty tree." << endl;
    else
    {
        current = this->root;
        trailCurrent = this->root;

        // Search for the node to delete
        while (current != nullptr && !found)
        {
            if (current->info == deleteItem)
                found = true;  // Node found
            else
            {
                trailCurrent = current;

                if (current->info > deleteItem)
                    current = current->lLink;  // Go left
                else
                    current = current->rLink;  // Go right
            }
        }

        if (current == nullptr)
            cout << "The item to be deleted is not in the tree." << endl;
        else if (found)
        {
            // If deleting the root
            if (current == this->root)
                deleteFromTree(this->root);
            else if (trailCurrent->info > deleteItem)
                deleteFromTree(trailCurrent->lLink);
            else
                deleteFromTree(trailCurrent->rLink);
        }
        else
            cout << "The item to be deleted is not in the tree." << endl;
    }
}

template <class elemType>
void bSearchTreeType<elemType>::deleteFromTree(nodeType<elemType>* &p)
{
    nodeType<elemType> *current;       // Used for traversal
    nodeType<elemType> *trailCurrent;  // Parent pointer
    nodeType<elemType> *temp;          // Node to delete

    if (p == nullptr)
        cout << "Error: The node to be deleted does not exist." << endl;

    // Case 1: Node is a leaf
    else if (p->lLink == nullptr && p->rLink == nullptr)
    {
        temp = p;
        p = nullptr;
        delete temp;
    }

    // Case 2: Node has only right child
    else if (p->lLink == nullptr)
    {
        temp = p;
        p = temp->rLink;
        delete temp;
    }

    // Case 3: Node has only left child
    else if (p->rLink == nullptr)
    {
        temp = p;
        p = temp->lLink;
        delete temp;
    }

    // Case 4: Node has two children
    else
    {
        // Find inorder predecessor (rightmost node in left subtree)
        current = p->lLink;
        trailCurrent = nullptr;

        while (current->rLink != nullptr)
        {
            trailCurrent = current;
            current = current->rLink;
        }

        // Replace p's info with predecessor's info
        p->info = current->info;

        // Remove predecessor node
        if (trailCurrent == nullptr)
            p->lLink = current->lLink;
        else
            trailCurrent->rLink = current->lLink;

        delete current;
    }
}

#endif
