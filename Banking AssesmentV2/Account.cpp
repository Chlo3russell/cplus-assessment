#include "Account.h"

std::string Account::getType() {
	return _typeOfAccount;
}


//Searching for a specific transaction
void Account::searchForTransaction(double amountToSearchFor) {
	bool found = false;

	for (const auto log : history) {
		if (log.getValue() == amountToSearchFor) {
			std::cout << "Transaction Found!" << std::endl;
			log.toString();
			found = true;
		}
	}
	if (!found) {
		std::cout << "Transaction Not Found!" << std::endl;
	}

}

//Adding a transaction to the history vector
void Account::addHistory(double amount, std::string& transactionDesc) {
	history.emplace_back(transactionDesc, amount);
}

