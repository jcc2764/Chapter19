#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
using namespace std;

/*
============================================================
   DVD STORE PROGRAM — USER INTERFACE SHELL (NO BACKEND)
   -----------------------------------------------------
   This file contains ONLY the menu system and placeholder
   ("dummy") functions. No real customer or DVD logic is
   implemented here yet.

============================================================
*/


// ==========================================================
// DUMMY FUNCTION DEFINITIONS
// ----------------------------------------------------------
// These functions are placeholders. They simulate actions
// such as listing customers, adding customers, renting DVDs,
// etc. The real program will replace these with actual logic.
// ==========================================================
void dummyListCustomers()      { cout << ">>> [DUMMY] Listing customers...\n"; }
void dummyAddCustomer()        { cout << ">>> [DUMMY] Adding customer...\n"; }
void dummyEditCustomer()       { cout << ">>> [DUMMY] Editing customer...\n"; }
void dummyDeleteCustomer()     { cout << ">>> [DUMMY] Deleting customer...\n"; }
void dummySearchByID()         { cout << ">>> [DUMMY] Searching by Customer ID...\n"; }
void dummySearchByName()       { cout << ">>> [DUMMY] Searching by Customer Name...\n"; }
void dummyRentDVD()            { cout << ">>> [DUMMY] Renting DVD...\n"; }
void dummyReturnDVD()          { cout << ">>> [DUMMY] Returning DVD...\n"; }
void dummyListAllRented()      { cout << ">>> [DUMMY] Listing all rented DVDs...\n"; }


// ==========================================================
// INPUT VALIDATION HELPER
// ----------------------------------------------------------
// Ensures the user enters a valid numeric menu choice within
// the allowed range. Prevents infinite loops and bad input.
// ==========================================================
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


// ==========================================================
// UI HELPERS
// ----------------------------------------------------------
// header()      → Prints a formatted title bar
// pauseScreen() → Waits for user to press ENTER
// ==========================================================
void header(const string& title) {
    cout << "====================================================\n";
    cout << "                 " << title << "\n";
    cout << "====================================================\n";
}

void pauseScreen() {
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


// ==========================================================
// MENU DISPLAY FUNCTIONS
// ----------------------------------------------------------
// These functions ONLY print menu options. They do not
// perform any actions. The main loop handles user choices.
// ==========================================================
void showMainMenu() {
    system("clear");   // Clears console (Linux/Mac). On Windows use "cls".
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

void showCustomerListMenu() {
    header("CUSTOMER MANAGEMENT");
    cout << "1. Add Customer\n";
    cout << "2. Edit Customer\n";
    cout << "3. Delete Customer\n";
    cout << "4. Back to Main Menu\n";
    cout << "====================================================\n";
}

void showSearchMenu() {
    header("SEARCH CUSTOMERS");
    cout << "1. Search by Customer ID\n";
    cout << "2. Search by Customer Name\n";
    cout << "3. Back to Main Menu\n";
    cout << "====================================================\n";
}


// ==========================================================
// CUSTOMER MANAGEMENT LOOP
// ----------------------------------------------------------
// Handles the submenu for Add/Edit/Delete operations.
// The parameter showListFirst determines whether the
// customer list should be displayed before showing options.
// ==========================================================
void customerManagementLoop(bool showListFirst) {
    if (showListFirst) {
        system("clear");
        header("CUSTOMER LIST");
        dummyListCustomers();   // Placeholder for real list
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
        case 4: break; // Return to main menu
        }
        if (sub != 4) pauseScreen();
    }
}


// ==========================================================
// MAIN PROGRAM LOOP
// ----------------------------------------------------------
// Controls the entire UI. Each menu option currently calls
// a dummy function. Later, these will be replaced with real
// BST-based customer and DVD operations.
// ==========================================================
int main() {
    int choice = 0;

    while (choice != 7) {
        showMainMenu();
        choice = getValidatedChoice(1, 7);

        system("clear");

        switch (choice) {

        case 1:   // List customers, then open management menu
            customerManagementLoop(true);
            break;

        case 2:   // Open management menu without listing first
            customerManagementLoop(false);
            break;

        case 3: { // Search submenu
            int s = 0;
            while (s != 3) {
                system("clear");
                showSearchMenu();
                s = getValidatedChoice(1, 3);

                system("clear");
                header("SEARCH CUSTOMERS");

                switch (s) {
                case 1: dummySearchByID();   break;
                case 2: dummySearchByName(); break;
                case 3: break;
                }
                if (s != 3) pauseScreen();
            }
            break;
        }

        case 4: { // Rent DVD (dummy)
            header("RENT DVD");

            int id;
            string title;

            cout << "Enter Customer ID: ";
            while (!(cin >> id)) {
                cout << "Invalid ID. Enter numeric Customer ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter DVD Title: ";
            getline(cin, title);

            cout << "\nYou entered:\n";
            cout << "  Customer ID: " << id << "\n";
            cout << "  DVD Title  : " << title << "\n\n";

            dummyRentDVD();
            pauseScreen();
            break;
        }

        case 5: { // Return DVD (dummy)
            header("RETURN DVD");

            int id;
            string title;

            cout << "Enter Customer ID: ";
            while (!(cin >> id)) {
                cout << "Invalid ID. Enter numeric Customer ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter DVD Title: ";
            getline(cin, title);

            cout << "\nYou entered:\n";
            cout << "  Customer ID: " << id << "\n";
            cout << "  DVD Title  : " << title << "\n\n";

            dummyReturnDVD();
            pauseScreen();
            break;
        }

        case 6:   // List all rented DVDs (dummy)
            header("ALL RENTED DVDs");
            dummyListAllRented();
            pauseScreen();
            break;

        case 7:
            cout << "Exiting...\n";
            break;
        }
    }

    return 0;
}
