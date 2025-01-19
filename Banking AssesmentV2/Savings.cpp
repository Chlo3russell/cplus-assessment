#include "Savings.h"

//Constructors
Savings::Savings(double initialBalance) {
	balance = initialBalance;
	_typeOfAccount = "Savings";
	interestRate = 0.00085;

	std::cout << "Thank you for creating your Savings account\nAccount balance of:\t£" << initialBalance << std::endl;

	_transactionType = "Initital Deposit";
	addHistory(balance, _transactionType);
}

Savings::Savings(double initialBalance, bool) {
	balance = initialBalance;
	_typeOfAccount = "Isa";
	interestRate = 0.015;
	isa = true;

	std::cout << "Thank you for creating your ISA savings account\nAccount balance of:\t£" << initialBalance << std::endl;

	_transactionType = "Initital Deposit";
	addHistory(balance, _transactionType);
}

//Overridden deposit function
void Savings::deposit(double amount, std::string& transactionDesc) {
		
	balance += amount;
	addHistory(amount, transactionDesc);
	
	std::cout << "Account balance:\t£" << balance << std::endl;
}

//Overridden withdraw function
void Savings::withdraw(double amount, std::string& transactionDesc) {

	if (_typeOfAccount == "Savings")
	{
		if (balance - amount < 0) {
			std::cout << "Insufficient funds. Transaction cancelled." << std::endl;
			return;
		}
	} else {
		if (balance - amount < 1500) {
			std::cout << "Withdrawal would reduce balance below ISA limit. Transaction cancelled." << std::endl;
			return;
		}
	}

	balance -= amount;
	addHistory(-amount, transactionDesc);

	std::cout << "Account balance:\t£" << balance << std::endl;
}

void Savings::toString() {
	std::cout << _typeOfAccount << " Account: £" << balance << std::endl;

	for (auto& log : history) {
		log.toString();
	}
}

//Showing the projected balance of the account
void Savings::computeInterest(int years) {
	if (years <= 0) {
		std::cerr << "Invalid number of years. Please enter a positive value." << std::endl;
		return;
	}

	double monthlyRate = (1 + (interestRate / 12));
	float projectedBalance = pow(monthlyRate, 12 * years) * balance;

	std::cout << "Projected balance: £" << projectedBalance << std::endl;
}
//Getters for private values
double Savings::getBalance() const {
	return balance;
}
