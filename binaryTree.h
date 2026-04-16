// ===============================
// ASSIGNMENT 19-11  DVD RENTAL STORE DATABASE
// AUTHOR: Joseph Evans
// DATE: 4/16/2026
// ===============================

//Header File Binary Search Tree
#ifndef H_binaryTree
#define H_binaryTree

#include <iostream>

using namespace std; 

/*
    nodeType
    --------
    A single node in a binary tree.

    Contains:
        - info: the stored data (generic type elemType)
        - lLink: pointer to left child
        - rLink: pointer to right child
*/
template <class elemType>
struct nodeType
{ 
    elemType info;
    nodeType<elemType> *lLink;
    nodeType<elemType> *rLink;
};
    
/*
    binaryTreeType
    --------------
    A generic binary tree class that provides:

        - Traversal (inorder, preorder, postorder)
        - Height calculation
        - Node count
        - Leaf count
        - Copying and destruction

    This class does NOT enforce BST ordering rules.
    It is meant to be inherited by bSearchTreeType,
    which adds BST-specific insert/search/delete logic.

    Many functions are virtual because derived classes
    (like bSearchTreeType) must implement them.
*/
template <class elemType>
class binaryTreeType
{
public:
    // Overload assignment operator to deep-copy another tree
    const binaryTreeType<elemType>& operator=
                 (const binaryTreeType<elemType>&); 

    // Returns true if the tree is empty
    bool isEmpty() const;

    // Public traversal functions
    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;

    // Tree statistics
    int treeHeight() const;
    int treeNodeCount() const;
    int treeLeavesCount() const;

    // Deletes all nodes in the tree
    void destroyTree();

    // Pure virtual functions — must be implemented by BST class
    virtual bool search(const elemType& searchItem) const = 0;
    virtual void insert(const elemType& insertItem) = 0;
    virtual void deleteNode(const elemType& deleteItem) = 0;

    // Copy constructor
    binaryTreeType(const binaryTreeType<elemType>& otherTree);

    // Default constructor
    binaryTreeType();   

    // Destructor
    ~binaryTreeType();   

protected:
    nodeType<elemType>  *root;   // Pointer to root node

private:
    // Internal helpers for copying and destroying trees
    void copyTree(nodeType<elemType>* &copiedTreeRoot,
                  nodeType<elemType>* otherTreeRoot);

    void destroy(nodeType<elemType>* &p);

    // Internal recursive traversal helpers
    void inorder(nodeType<elemType> *p) const;
    void preorder(nodeType<elemType> *p) const;
    void postorder(nodeType<elemType> *p) const;

    // Internal helpers for height, node count, and leaf count
    int height(nodeType<elemType> *p) const;
    int max(int x, int y) const;
    int nodeCount(nodeType<elemType> *p) const;
    int leavesCount(nodeType<elemType> *p) const;
};

//
// IMPLEMENTATION SECTION
//

template <class elemType>
binaryTreeType<elemType>::binaryTreeType()
{
    root = nullptr;
}

template <class elemType>
bool binaryTreeType<elemType>::isEmpty() const
{
    return (root == nullptr);
}

template <class elemType>
void binaryTreeType<elemType>::inorderTraversal() const
{
    inorder(root);
}

template <class elemType>
void binaryTreeType<elemType>::preorderTraversal() const
{
    preorder(root);
}

template <class elemType>
void binaryTreeType<elemType>::postorderTraversal() const
{
    postorder(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeHeight() const
{
    return height(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeNodeCount() const
{
    return nodeCount(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeLeavesCount() const
{
    return leavesCount(root);
}

/*
    copyTree
    --------
    Recursively duplicates another tree.

    Used by:
        - Copy constructor
        - Assignment operator
*/
template <class elemType>
void  binaryTreeType<elemType>::copyTree
                       (nodeType<elemType>* &copiedTreeRoot,
                        nodeType<elemType>* otherTreeRoot)
{
    if (otherTreeRoot == nullptr)
        copiedTreeRoot = nullptr;
    else
    {
        // Allocate new node
        copiedTreeRoot = new nodeType<elemType>;
        copiedTreeRoot->info = otherTreeRoot->info;

        // Recursively copy left and right subtrees
        copyTree(copiedTreeRoot->lLink, otherTreeRoot->lLink);
        copyTree(copiedTreeRoot->rLink, otherTreeRoot->rLink);
    }
}

/*
    inorder
    -------
    Left → Node → Right
*/
template <class elemType>
void binaryTreeType<elemType>::inorder
                              (nodeType<elemType> *p) const
{
    if (p != nullptr)
    {
        inorder(p->lLink);
        cout << p->info << endl;
        inorder(p->rLink);
    }
}

/*
    preorder
    --------
    Node → Left → Right
*/
template <class elemType>
void binaryTreeType<elemType>::preorder
                              (nodeType<elemType> *p) const
{
    if (p != nullptr)
    {
        cout << p->info << " ";
        preorder(p->lLink);
        preorder(p->rLink);
    }
}

/*
    postorder
    ---------
    Left → Right → Node
*/
template <class elemType>
void binaryTreeType<elemType>::postorder
                              (nodeType<elemType> *p) const
{
    if (p != nullptr)
    {
        postorder(p->lLink);
        postorder(p->rLink);
        cout << p->info << " ";
    }       
}

/*
    operator=
    ---------
    Deep-copies another binary tree.
*/
template <class elemType>
const binaryTreeType<elemType>& binaryTreeType<elemType>::
        operator=(const binaryTreeType<elemType>& otherTree)
{ 
    if (this != &otherTree) // avoid self-copy
    {
        if (root != nullptr)
            destroy(root);  // delete existing tree

        if (otherTree.root == nullptr)
            root = nullptr;
        else
            copyTree(root, otherTree.root);
    }

    return *this; 
}

/*
    destroy
    -------
    Recursively deletes all nodes in the tree.
*/
template <class elemType>
void  binaryTreeType<elemType>::destroy(nodeType<elemType>* &p)
{
    if (p != nullptr)
    {
        destroy(p->lLink);
        destroy(p->rLink);
        delete p;
        p = nullptr;
    }
}

template <class elemType>
void  binaryTreeType<elemType>::destroyTree()
{
    destroy(root);
}

/*
    Copy constructor
*/
template <class elemType>
binaryTreeType<elemType>::binaryTreeType
                (const binaryTreeType<elemType>& otherTree)
{
    if (otherTree.root == nullptr)
        root = nullptr;
    else
        copyTree(root, otherTree.root);
}

/*
    Destructor
*/
template <class elemType>
binaryTreeType<elemType>::~binaryTreeType()
{
    destroy(root);
}

/*
    height
    ------
    Returns height of tree rooted at p.
*/
template<class elemType>
int binaryTreeType<elemType>::height
                             (nodeType<elemType> *p) const
{
    if (p == nullptr)
        return 0;
    else
        return 1 + max(height(p->lLink), height(p->rLink));
}

template <class elemType>
int binaryTreeType<elemType>::max(int x, int y) const
{
    return (x >= y ? x : y);
}

/*
    nodeCount
    ---------
    Returns total number of nodes in the tree.
*/
template<class elemType>
int binaryTreeType<elemType>::nodeCount(nodeType<elemType> *p) const
{
    if (p == nullptr)
        return 0;
    else
        return 1 + nodeCount(p->lLink) + nodeCount(p->rLink);
}

#endif
