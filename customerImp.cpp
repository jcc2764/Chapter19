#include <iostream>
#include <string>
#include "customer.h"

using namespace std;
 
void customerType::print()
{
	cout << custAcctNo << " ";
	personType::print();
	cout << " " << rentedDVDTree.treeNodeCount() << endl;
}

void customerType::setCustInfo(string first, string last,
							   int acctNo)
{
	personType::setName(first,last); 
	custAcctNo = acctNo;
}
 
void customerType::rentDVD(string title)
{
	rentedDVDTree.insert(title);
}   

void customerType::returnDVD(string title)
{
	rentedDVDTree.deleteNode(title);
}

int customerType::getNoOfRentals()
{
	return rentedDVDTree.treeNodeCount();
}

int customerType::getAcctNo()
{
	return custAcctNo; 
}

customerType::customerType(string first, string last, 
						   int acctNo)
				:personType(first,last)
{
	custAcctNo = acctNo;
}

customerType::customerType()
{
	custAcctNo = 0;
}

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

ostream& operator<<(ostream& os,  customerType& cust)
{
	os << cust.custAcctNo << " " << cust.getFirstName()
	   << " " << cust.getLastName()
	   << " " << cust.rentedDVDTree.treeNodeCount() << endl;

	return os;
} 

void customerType::printRentedDVD()
{ 
	rentedDVDTree.inorderTraversal();
}