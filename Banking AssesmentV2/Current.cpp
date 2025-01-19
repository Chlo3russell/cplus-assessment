#include "Current.h"

// Constructor that sets the initial balance
Current::Current(double initialBalance) {
	balance = initialBalance;	
	_typeOfAccount = "Current";

	std::cout << "Thank you for creating your current account.\nInitial balance:\t£" << balance << std::endl;

	 _transactionType = "Initital Deposit";
	addHistory(balance, _transactionType);
}

//Overridden deposit function
void Current::deposit(double amount, std::string& transactionDesc) {
	
	balance += amount;
	addHistory(amount, transactionDesc);
	
	std::cout << "Account balance:\t£" << balance << std::endl;
}

//Overridden withdraw function
void Current::withdraw(double amount, std::string& transactionDesc) {

	if (balance - amount < overdraft) {
		std::cout << "Transaction declined. Overdraft limit exceeded." << std::endl;
		return;
	}
	
	balance -= amount;
	addHistory(-amount, transactionDesc);
	
	std::cout << "Account balance:\t£" << balance << std::endl;
}

void Current::toString() {
	std::cout << "Current Account : £" << balance << std::endl;

	for (auto& log : history) {
		log.toString();
	}
}

//Getters for private values
double Current::getBalance() const {
	return balance;
}

int Current::getOverdraft() const {
	return overdraft;
}
