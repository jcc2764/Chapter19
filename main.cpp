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
#include <algorithm>
#include <cctype>
#include <vector>       
#include <sstream>

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

// Next available ID (determined from Customer.txt)
int nextID = 0;


// ===============================
// FORWARD DECLARATIONS
// ===============================
void addCustomer();
void editCustomer();
void deleteCustomer();
void saveAllData();


// ===============================
// LOAD CUSTOMERS FROM Customer.txt
// ===============================
//
// Expected format per line:
//   ID First Last Street# StreetName StreetType City State Zip Phone MemberSince
// ===============================
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
        customerType cust(first, last, id);

        // Build address (NO COMMAS)
        string address = streetNum + " " + streetName + " " + streetType +
                         " " + city + " " + state + " " + zip;

        cust.setAddress(address);
        cust.setPhone(phone);
        cust.setMemberSince(memberSince);

        customerDB.insert(cust);

        if (id > nextID)
            nextID = id;
    }

    nextID++; // next available ID

    infile.close();
}


// ===============================
// LOAD DVD RENTALS FROM custDat.txt
// ===============================
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

    while (infile >> first >> last >> acctNo >> numDVDs)
    {
        customerType* cust = customerDB.getCustomerById(acctNo);

        if (!cust)
        {
            for (int i = 0; i < numDVDs; ++i)
            {
                string dummy;
                infile >> dummy;
            }
        }
        else
        {
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
void header(const string& title) {
    cout << "====================================================\n";
    cout << "                 " << title << "\n";
    cout << "====================================================\n";
}

void pauseScreen() {
    cout << "\nPress ENTER to continue...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


// ===============================
// FAILSAFE INPUT HELPERS
// ===============================
string getOneWord(const string& prompt)
{
    string input;
    while (true)
    {
        cout << prompt;
        cin >> input;

        if (input.find(' ') == string::npos)
            return input;

        cout << "ERROR: This field must be ONE word.\n";
    }
}

bool isValidState(const string& st)
{
    static const string states[50] = {
        "AL","AK","AZ","AR","CA","CO","CT","DE","FL","GA",
        "HI","ID","IL","IN","IA","KS","KY","LA","ME","MD",
        "MA","MI","MN","MS","MO","MT","NE","NV","NH","NJ",
        "NM","NY","NC","ND","OH","OK","OR","PA","RI","SC",
        "SD","TN","TX","UT","VT","VA","WA","WV","WI","WY"
    };

    for (const string& s : states)
        if (st == s)
            return true;

    return false;
}

string getStateCode()
{
    string st;

    while (true)
    {
        cout << "Enter State (2 letters): ";
        cin >> st;

        if (st.length() == 2)
        {
            st[0] = toupper(st[0]);
            st[1] = toupper(st[1]);

            if (isValidState(st))
                return st;
        }

        cout << "ERROR: Invalid state code.\n";
    }
}

string getZip()
{
    string zip;

    while (true)
    {
        cout << "Enter ZIP (5 digits): ";
        cin >> zip;

        if (zip.length() == 5 &&
            all_of(zip.begin(), zip.end(), ::isdigit))
            return zip;

        cout << "ERROR: ZIP must be exactly 5 digits.\n";
    }
}

string getPhone()
{
    string ph;

    while (true)
    {
        cout << "Enter Phone (10 digits): ";
        cin >> ph;

        if (ph.length() == 10 &&
            all_of(ph.begin(), ph.end(), ::isdigit))
            return ph;

        cout << "ERROR: Phone must be exactly 10 digits.\n";
    }
}

bool isValidDate(const string& d)
{
    if (d.length() != 10) return false;
    if (d[2] != '/' || d[5] != '/') return false;

    string mm = d.substr(0,2);
    string dd = d.substr(3,2);
    string yyyy = d.substr(6,4);

    if (!all_of(mm.begin(), mm.end(), ::isdigit)) return false;
    if (!all_of(dd.begin(), dd.end(), ::isdigit)) return false;
    if (!all_of(yyyy.begin(), yyyy.end(), ::isdigit)) return false;

    int month = stoi(mm);
    int day   = stoi(dd);

    return (month >= 1 && month <= 12 &&
            day >= 1 && day <= 31);
}

string getDate(const string& prompt)
{
    string d;

    while (true)
    {
        cout << prompt;
        cin >> d;

        if (isValidDate(d))
            return d;

        cout << "ERROR: Invalid date format. Use MM/DD/YYYY.\n";
    }
}


// ===============================
// SAVE ALL DATA BACK TO FILES
// ===============================
void saveAllData()
{
    // Save Customer.txt
    ofstream out1("Customer.txt");
    customerDB.saveCustomersToFile(out1);
    out1.close();

    // Save custDat.txt
    ofstream out2("custDat.txt");
    customerDB.saveRentalsToFile(out2);
    out2.close();
}


// ===============================
// ADD CUSTOMER
// ===============================
void addCustomer()
{
    system("clear");
    header("ADD CUSTOMER");

    string first = getOneWord("Enter First Name: ");
    string last  = getOneWord("Enter Last Name: ");

    string streetNum  = getOneWord("Enter Street Number: ");
    string streetName = getOneWord("Enter Street Name: ");
    string streetType = getOneWord("Enter Street Type (e.g., Road, Lane): ");
    string city       = getOneWord("Enter City: ");
    string state      = getStateCode();
    string zip        = getZip();
    string phone      = getPhone();
    string memberSince = getDate("Enter Member Since (MM/DD/YYYY): ");

    string address = streetNum + " " + streetName + " " + streetType +
                     " " + city + " " + state + " " + zip;

    customerType cust(first, last, nextID++);
    cust.setAddress(address);
    cust.setPhone(phone);
    cust.setMemberSince(memberSince);

    customerDB.insert(cust);

    saveAllData();

    cout << "\nCustomer added successfully.\n";
    pauseScreen();
}


// ===============================
// EDIT CUSTOMER (PRE-FILLED)
// ===============================
void editCustomer()
{
    system("clear");
    header("EDIT CUSTOMER");

    int id;
    cout << "Enter Customer ID to edit: ";

    while (!(cin >> id))
    {
        cout << "Invalid ID. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    customerType* cust = customerDB.getCustomerById(id);

    if (!cust)
    {
        cout << "Customer NOT FOUND.\n";
        pauseScreen();
        return;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto getOptional = [&](const string& prompt, const string& current) {
        cout << prompt << " [" << current << "]: ";
        string input;
        getline(cin, input);
        if (input.empty())
            return current;
        return input;
    };

    cout << "\nEditing customer:\n";
    cust->printFullInfo();
    cout << "\n";

    string first = getOptional("Enter New First Name", cust->getFirstName());
    string last  = getOptional("Enter New Last Name", cust->getLastName());

    // Address parsing is crude but works for your format
    string addr = cust->getAddress();
    vector<string> parts;
    string temp;
    stringstream ss(addr);
    while (ss >> temp) parts.push_back(temp);

    string streetNum  = getOptional("Enter New Street Number", parts[0]);
    string streetName = getOptional("Enter New Street Name", parts[1]);
    string streetType = getOptional("Enter New Street Type", parts[2]);
    string city       = getOptional("Enter New City", parts[3]);
    string state      = getOptional("Enter New State", parts[4]);
    string zip        = getOptional("Enter New ZIP", parts[5]);

    string phone      = getOptional("Enter New Phone", cust->getPhone());
    string memberSince = getOptional("Enter New Member Since", cust->getMemberSince());

    string newAddress = streetNum + " " + streetName + " " + streetType +
                        " " + city + " " + state + " " + zip;

    cust->setName(first, last);
    cust->setAddress(newAddress);
    cust->setPhone(phone);
    cust->setMemberSince(memberSince);

    saveAllData();

    cout << "\nCustomer updated successfully.\n";
    pauseScreen();
}


// ===============================
// DELETE CUSTOMER
// ===============================
void deleteCustomer()
{
    system("clear");
    header("DELETE CUSTOMER");

    int id;
    cout << "Enter Customer ID to delete: ";
    while (!(cin >> id)) {
        cout << "Invalid ID. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    customerType* cust = customerDB.getCustomerById(id);

    if (!cust) {
        cout << "Customer NOT FOUND.\n";
        pauseScreen();
        return;
    }

    cout << "\nAre you sure you want to delete this customer? (y/n): ";
    char confirm;
    cin >> confirm;
    if (tolower(confirm) != 'y') {
        cout << "Delete cancelled.\n";
        pauseScreen();
        return;
    }

    // build a proper key using the actual customer info
    customerType key(cust->getFirstName(), cust->getLastName(), id);
    customerDB.deleteNode(key);

    saveAllData();

    cout << "Customer deleted.\n";
    pauseScreen();
}


// ===============================
// MENU DISPLAY FUNCTIONS
// ===============================
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


// ===============================
// CUSTOMER MANAGEMENT LOOP
// ===============================
void customerManagementLoop(bool showListFirst) {
    if (showListFirst) {
        system("clear");
        header("CUSTOMER LIST");

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
        case 1: addCustomer();   break;
        case 2: editCustomer();  break;
        case 3: deleteCustomer();break;
        case 4: break;
        }
    }
}


// ===============================
// MAIN PROGRAM
// ===============================
int main() {

    loadCustomersFromCustomerTxt();
    loadDVDsFromCustDat();

    int choice = 0;

    while (choice != 7) {
        showMainMenu();
        choice = getValidatedChoice(1, 7);

        system("clear");

        switch (choice) {

        case 1:
            customerManagementLoop(true);
            break;

        case 2:
            customerManagementLoop(false);
            break;

        case 3: {
            int s = 0;
            while (s != 3) {
                system("clear");
                showSearchMenu();
                s = getValidatedChoice(1, 3);

                system("clear");
                header("SEARCH CUSTOMERS");

                switch (s) {

                case 1: {
                    int id;
                    cout << "Enter Customer ID: ";

                    while (!(cin >> id)) {
                        cout << "Invalid ID. Enter numeric Customer ID: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    customerType* cust = customerDB.getCustomerById(id);

                    if (!cust)
                        cout << "Customer NOT FOUND\n";
                    else {
                        cout << "\nCustomer Information:\n";
                        cust->printFullInfo();
                    }

                    pauseScreen();
                    break;
                }

                case 2: {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    string name;
                    cout << "Enter Customer Name (First Last): ";
                    getline(cin, name);

                    customerType* cust = customerDB.getCustomerByName(name);

                    if (!cust)
                        cout << "Customer NOT FOUND\n";
                    else {
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

        case 4: {
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

            saveAllData();

            pauseScreen();
            break;
        }

        case 5: {
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

            saveAllData();

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
