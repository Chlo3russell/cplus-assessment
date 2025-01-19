#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Account.h"
#include "InterestEarning.h"

class Savings : public Account, public InterestEarning {
public:
	// Constructors
	explicit Savings(double, bool); // constructor for ISA savings account
	explicit Savings(double);
	// Destructor
	~Savings() = default;
	// Public methods
	void deposit(double amount, std::string& type) override;
	void withdraw(double amount, std::string& type) override;

	double getBalance() const;

	void computeInterest(int years);
	void toString() override;



private:
	//Private variables
	double interestRate;
	bool isa = false;






};

