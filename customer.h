#ifndef H_customerType
#define H_customerType

#include <iostream>
#include "personType.h"
#include <string>
#include "binarySearchTree.h"
  
using namespace std;

class customerType: public personType
{ 
   friend ostream& operator<<(ostream&,  customerType&);
	  //overload stream insertion operator
public:
	void print();
	  //Output account number, first name, last name, and 
	  //number of rentals, in the form:
	  //acctNo firstName lastName noOfRentals
	void setCustInfo(string first, string last, int acctNo);
	  //set firstName, lastName, and account number 
	  //according to the parameters
	  //firstName = first; lastName = last; 
	void rentDVD(string);
	  //This function rents a DVD to the customer
	void returnDVD(string);
	  //This function renturns a DVD to the customer

	int getNoOfRentals();
	  //This function returns the number of
	  //DVDs rented by the customer.
	int getAcctNo();
	  //This function returns the account number of
	  //the customer.

	void printRentedDVD();

	customerType(string first, string last, int acctNo);
	  //constructor with parameters
	  //set firstName and lastName according to the parameters
	  //firstName = first; lastName = last;
  	customerType(); 
  	 //default constructor;
  	 //intialize firstName and lastName, and custAcctNo 
  	 //Postcondition: firstName = ""; lastName = "";
	 //		  custAcctNo = 0;

		//overload operators for comparisons 
	bool operator==(const customerType&) const;
	bool operator!=(const customerType&) const;
	bool operator<=(const customerType&) const;
	bool operator<(const customerType&) const;
	bool operator>=(const customerType&) const;
	bool operator>(const customerType&) const;
     
private:
	int custAcctNo; // store account number
	bSearchTreeType<string> rentedDVDTree;
};

#endif