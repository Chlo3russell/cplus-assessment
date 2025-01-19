#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include "Account.h"
#include "Transaction.h"


class Current : public Account {
public:
	//Constructor
	explicit Current(double initialBalance);
	//Destructor
	~Current() = default;

	void deposit(double amount, std:: string& description) override;
	void withdraw(double amount, std::string& description) override;

	double getBalance() const;
	int getOverdraft() const;

	void toString() override;




private:

	
	int overdraft = -500;

};



