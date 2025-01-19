#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include "Account.h"

class Transaction
{
public:
	//Constructor
	Transaction(std::string transactionType, double amount);
	//Destructor
	~Transaction() = default;
	
	void toString() const; // changing the desc, timestamp and the value into a string
	
	double getValue() const;

private:
	std::string desc; // description of the transaction
	time_t timestamp; // date and time of the transaction
	double value; // value of transaction
};

