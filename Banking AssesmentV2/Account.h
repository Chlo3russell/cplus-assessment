#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <string>
#include "Transaction.h"

// Forward declaration
class Transaction;  
// Abstract class
class Account
{

public:
	//Destructor
	virtual ~Account() = default;
	//Public methods
	std::string getType();
	void searchForTransaction(double);

protected:
	//Shared properties
	double balance = 0.0;
	std::string _typeOfAccount;
	std::string _transactionType;
	//Virtual methods to overriden
	virtual void deposit(double amount, std::string&) = 0;
	virtual void withdraw(double amount, std::string&) = 0;
	virtual void toString() = 0;

	void addHistory(double amount, std::string& description);
	std::vector<Transaction> history;

};

   