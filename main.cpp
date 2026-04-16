// ===============================
// ASSIGNMENT 19-11  DVD RENTAL STORE DATABASE
// AUTHOR: Joseph Evans
// DATE: 4/16/2026
// ===============================

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

#include "customerBinaryTree.h"
#include "customer.h"

// ===============================
// GLOBAL CUSTOMER TREE
// ===============================
//
// customerDB is the main in‑memory database of all customers.
// It is a binary search tree ordered by customer account number.
//
customerBTreeType customerDB;


// ===============================
// DUMMY PLACEHOLDER FUNCTIONS
// (These are not implemented yet)
// ===============================
void dummyListCustomers()      { cout << ">>> [DUMMY] Listing customers...\n"; }
void dummyAddCustomer()        { cout << ">>> [DUMMY] Adding customer...\n"; }
void dummyEditCustomer()       { cout << ">>> [DUMMY] Editing customer...\n"; }
void dummyDeleteCustomer()     { cout << ">>> [DUMMY] Deleting customer...\n"; }
void dummySearchByID()         { cout << ">>> [DUMMY] Searching by Customer ID...\n"; }
void dummySearchByName()       { cout << ">>> [DUMMY] Searching by Customer Name...\n"; }
void dummyRentDVD()            { cout << ">>> [DUMMY] Renting DVD...\n"; }
void dummyReturnDVD()          { cout << ">>> [DUMMY] Returning DVD...\n"; }
void dummyListAllRented()      { cout << ">>> [DUMMY] Listing all rented DVDs...\n"; }


// ===============================
// LOAD CUSTOMERS FROM Customer.txt
// ===============================
//
// Expected format per line:
//   ID First Last Street# StreetName StreetType City State Zip Phone MemberSince
//
// Example:
//   1 John Doe 3102 Bree Street SomeTown ST 00000 1111111111 02/02/2000
//
// This function builds customer objects and inserts them into the BST.
//
void loadCustomersFromCustomerTxt()
{
    ifstream infile("Customer.txt");

    if (!infile)
    {
        cout << "ERROR: Could not open Customer.txt" << endl;
        return;
    }

    int id;
    string first, last;
    string streetNum, streetName, streetType;
    string city, state, zip;
    string phone, memberSince;

    // Read each customer record
    while (infile >> id
                  >> first
                  >> last
                  >> streetNum
                  >> streetName
                  >> streetType
                  >> city
                  >> state
                  >> zip
                  >> phone
                  >> memberSince)
    {
        // Create customer object
        customerType cust(first, last, id);

        // Build full address string
        string address = streetNum + " " + streetName + " " + streetType +
                         ", " + city + ", " + state + " " + zip;

        // Store extended info
        cust.setAddress(address);
        cust.setPhone(phone);
        cust.setMemberSince(memberSince);

        // Insert into BST
        customerDB.insert(cust);
    }

    infile.close();
}


// ===============================
// LOAD DVD RENTALS FROM custDat.txt
// ===============================
//
// Expected format per line:
//   first last acctNo numDVDs dvd1 dvd2 dvd3 ...
//
// Example:
//   John Doe 1 3 Matrix Terminator Shrek
//
// This function finds the matching customer and loads their rentals.
//
void loadDVDsFromCustDat()
{
    ifstream infile("custDat.txt");

    if (!infile)
    {
        cout << "ERROR: Could not open custDat.txt" << endl;
        return;
    }

    string first, last;
    int acctNo;
    int numDVDs;

    // Read each rental record
    while (infile >> first >> last >> acctNo >> numDVDs)
    {
        customerType* cust = customerDB.getCustomerById(acctNo);

        if (cust == nullptr)
        {
            // Customer not found — skip DVD titles
            for (int i = 0; i < numDVDs; ++i)
            {
                string dummy;
                infile >> dummy;
            }
        }
        else
        {
            // Load each DVD title into the customer's rental tree
            for (int i = 0; i < numDVDs; ++i)
            {
                string title;
                infile >> title;
                cust->rentDVD(title);
            }
        }
    }

    infile.close();
}


// ===============================
// INPUT VALIDATION HELPER
// ===============================
//
// Ensures user enters a valid integer within a range.
//
int getValidatedChoice(int min, int max) {
    int choice;

    while (true) {
        cout << "Enter choice: ";

        if (cin >> choice && choice >= min && choice <= max)
            return choice;

        cout << "\nInvalid input. Please enter a number between "
             << min << " and " << max << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// ===============================
// UI HELPERS
// ===============================

// Prints a formatted header bar
void header(const string& title) {
    cout << "====================================================\n";
    cout << "                 " << title << "\n";
    cout << "====================================================\n";
}

// Pauses screen until user presses ENTER
void pauseScreen() {
    cout << "\nPress ENTER to continue...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


// ===============================
// MENU DISPLAY FUNCTIONS
// ===============================

// Main menu
void showMainMenu() {
    system("clear");
    header("DVD STORE SYSTEM");
    cout << "1. List Customers\n";
    cout << "2. Add / Edit / Delete Customers\n";
    cout << "3. Search For Customer\n";
    cout << "4. Rent DVD\n";
    cout << "5. Return DVD\n";
    cout << "6. List All Rented DVDs\n";
    cout << "7. Exit\n";
    cout << "====================================================\n";
}

// Customer management submenu
void showCustomerListMenu() {
    header("CUSTOMER MANAGEMENT");
    cout << "1. Add Customer\n";
    cout << "2. Edit Customer\n";
    cout << "3. Delete Customer\n";
    cout << "4. Back to Main Menu\n";
    cout << "====================================================\n";
}

// Search submenu
void showSearchMenu() {
    header("SEARCH CUSTOMERS");
    cout << "1. Search by Customer ID\n";
    cout << "2. Search by Customer Name\n";
    cout << "3. Back to Main Menu\n";
    cout << "====================================================\n";
}


// ===============================
// CUSTOMER MANAGEMENT LOOP
// ===============================
//
// If showListFirst = true, prints the customer list before showing menu.
//
void customerManagementLoop(bool showListFirst) {
    if (showListFirst) {
        system("clear");
        header("CUSTOMER LIST");

        // Column headers
        cout << left
             << setw(5)  << "ID"
             << setw(12) << "First"
             << setw(15) << "Last"
             << setw(45) << "Address"
             << setw(15) << "Phone"
             << setw(15) << "MemberSince"
             << setw(8)  << "Rentals"
             << endl;

        cout << "-----------------------------------------------------------------------------------------------" << endl;

        // Print all customers (inorder traversal)
        customerDB.inorderTraversal();
        cout << endl;
    }

    int sub = 0;
    while (sub != 4) {
        showCustomerListMenu();
        sub = getValidatedChoice(1, 4);

        system("clear");
        header("CUSTOMER MANAGEMENT");

        switch (sub) {
        case 1: dummyAddCustomer();   break;
        case 2: dummyEditCustomer();  break;
        case 3: dummyDeleteCustomer();break;
        case 4: break;
        }
        if (sub != 4) pauseScreen();
    }
}


// ===============================
// MAIN PROGRAM
// ===============================
int main() {

    // Load customer database first
    loadCustomersFromCustomerTxt();

    // Load DVD rentals second
    loadDVDsFromCustDat();

    int choice = 0;

    while (choice != 7) {
        showMainMenu();
        choice = getValidatedChoice(1, 7);

        system("clear");

        switch (choice) {

        case 1: {   // List Customers, then management
            customerManagementLoop(true);
            break;
        }

        case 2: {   // Directly open Customer Management (no list first)
            customerManagementLoop(false);
            break;
        }

        case 3: {   // Search For Customer
            int s = 0;
            while (s != 3) {
                system("clear");
                showSearchMenu();
                s = getValidatedChoice(1, 3);

                system("clear");
                header("SEARCH CUSTOMERS");

                switch (s) {

                case 1: { // Search by Customer ID
                    int id;
                    cout << "Enter Customer ID: ";

                    // Validate numeric input
                    while (!(cin >> id)) {
                        cout << "Invalid ID. Enter numeric Customer ID: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    customerType* cust = customerDB.getCustomerById(id);

                    if (cust == nullptr)
                    {
                        cout << "Customer NOT FOUND\n";
                    }
                    else
                    {
                        cout << "\nCustomer Information:\n";
                        cust->printFullInfo();
                    }

                    pauseScreen();
                    break;
                }

                case 2: { // Search by Customer Name
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    string name;
                    cout << "Enter Customer Name (First Last): ";
                    getline(cin, name);

                    customerType* cust = customerDB.getCustomerByName(name);

                    if (cust == nullptr)
                    {
                        cout << "Customer NOT FOUND\n";
                    }
                    else
                    {
                        cout << "\nCustomer Information:\n";
                        cust->printFullInfo();
                    }

                    pauseScreen();
                    break;
                }

                case 3:
                    break;
                }
            }
            break;
        }

        case 4: {   // Rent DVD
            header("RENT DVD");

            int id;
            string title;

            cout << "Enter Customer ID: ";
            while (!(cin >> id)) {
                cout << "Invalid ID. Enter numeric Customer ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter DVD Title: ";
            getline(cin, title);

            customerDB.custRentDVD(id, title);

            pauseScreen();
            break;
        }

        case 5: {   // Return DVD
            header("RETURN DVD");

            int id;
            string title;

            cout << "Enter Customer ID: ";
            while (!(cin >> id)) {
                cout << "Invalid ID. Enter numeric Customer ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter DVD Title: ";
            getline(cin, title);

            customerDB.custReturnDVD(id, title);

            pauseScreen();
            break;
        }

        case 6:
            header("ALL RENTED DVDs");
            customerDB.rentedDVDsInfo();
            pauseScreen();
            break;

        case 7:
            cout << "Exiting...\n";
            break;
        }
    }

    return 0;
}
