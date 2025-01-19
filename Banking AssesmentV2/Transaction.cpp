#include "Transaction.h"

//Constructor
Transaction::Transaction(std::string transactionType, double amount) 
	: desc(transactionType), value(amount){
	time(&timestamp);
}

void Transaction::toString() const {
	std::cout << "-- " << desc << ": £" << std::fixed << std::setprecision(2) << value
		<< " on " << std::ctime(&timestamp);
}

//Getters for private values
double Transaction::getValue() const {
	return value;
}










