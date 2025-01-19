#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include "Account.h"
#include "Current.h"
#include "Savings.h"
#include "Transaction.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <Windows.h>

/// <summary>
/// Checks through a vector to see whether the account specified exists. 
/// </summary>
/// <returns>It returns the bool true if the account exists and false if it doesn't </returns>
template <typename AccountList, typename AccountType>
bool doesAccountExist(const AccountList& accountList, const AccountType& accountType) {
	for (const auto& account : accountList) {
		if (account->getType() == accountType) {
			return true;
		}
	}
	return false; 
}

/// <summary>
/// Dynamically checks whether an account can be cast down into a child class
/// </summary>
/// <returns> It returns a pointer to the base class if it can be cast down, if not it returns a null pointer</returns>
template <typename T>
T* getAccountType(const Account* accountToCheck) {
	return dynamic_cast<T*>(const_cast<Account*>(accountToCheck));
}

/// <summary>
/// Gets a user string and trys to convert it to a variety of number types (commonly int or double)
/// </summary>
/// <returns> It returns a -1 if any of the inputs are invalid, which is reflected in the code </returns>
template <typename T>
T safeStringToNum(const std::string& input) {
	try {
		double value = std::stod(input);

		if (value < 0) {
			std::cerr << "Error: Negative values are not allowed." << std::endl;
			return -1;
		}
		return value;
	}
	catch (const std::invalid_argument&) {
		std::cerr << "Invalid input. Expected a number, but received '" << input << "'." << std::endl;
	}
	return -1;
}


int main()
{
	//Ensures correct formatting
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);

	std::vector <std::string> parameters;
	std::string userCommand;
	std::vector <Account*> listOfAccounts;

	std::string* type = new std::string();

	Account* activeAccount = nullptr;

	std::cout << "~~~ Welcome to LincBank! ~~~" << std::endl; //welcome message
	std::cout << "Type...\n- Open - create a new account (1) Current, (2) Savings, (3) ISA, then your deposit."
		"\n- View - view the balance of a selected account or if no index is provided all accounts."
		"\n- Withdraw - withdraw money from the active account."
		"\n- Deposit - deposit money into the active  account."
		"\n- Transfer - to send money between accounts."
		"\n- Project - to calculate the amount of interest you will earn on the active savings account."
		"\n- Search - to search through your transactions by a given value on the active account."
		"\n- Exit - safetly closing the application"<< std::endl;

	while (userCommand != "exit")
	{
		parameters.clear(); // clear ready for next command

		while (parameters.empty()) {
			std::cout << std::endl << ">>> ";
			std::getline(std::cin, userCommand);

			char* cstr = new char[userCommand.length() + 1];
			strcpy(cstr, userCommand.c_str());

			char* token;
			token = strtok(cstr, " ");

			while (token != NULL)
			{
				parameters.push_back(token);
				token = strtok(NULL, " ");
			}
		}

		std::string command = parameters[0];
		std::cout << "Command: " << command << std::endl;

		if (command.compare("options") == 0)
		{
			std::cout << "Type...\n- Open - create a new account (1) Current, (2) Savings, (3) ISA. >> open <accountType> <depositAmount>"
				"\n- View - view the balance of a selected account. >> View or >> View <accountIndex>"
				"\n- Withdraw - withdraw money. >> Withdraw <withdrawalAmount>"
				"\n- Deposit - deposit money. >> Deposit <depositAmount>"
				"\n- Transfer - to send money between accounts. >> Transfer <TransferringFrom> <TransferringTo> <transactionValue>"
				"\n- Project - to calculate the amount of interest. >> Project <amountOfYears>"
				"\n- Search - to search through your transactions. >> Search <transactionValue>"
				"\n- Exit - safetly closing the application" << std::endl;
		}
		else if (command.compare("open") == 0)
		{
			//Checks that there is the correct amount of variables
			if (parameters.size() < 3) {
				std::cout << "Please define your new account with all variables." << std::endl;
				continue;
			}
			//Uses a template function to ensure that erronous inputs are handled correctly
			double deposit = safeStringToNum<double>(parameters[2]);
			int accountType = safeStringToNum<int>(parameters[1]);

			if (deposit == -1 || accountType == -1) {
				// -1 denotes an invalid user entry so it should cancel the option
				continue;
			}
			//Goes through the account types and creates specified account type
			if ((accountType == 1) && (!doesAccountExist(listOfAccounts, "Current"))) {
				listOfAccounts.push_back(dynamic_cast<Account*>(new Current(deposit)));
			}
			else if ((accountType == 2) && (deposit > 0)) {
				listOfAccounts.push_back(dynamic_cast<Account*>(new Savings(deposit)));
			}
			else if ((accountType == 3) && (!doesAccountExist(listOfAccounts, "Isa")) && (deposit >= 1000)) {
				bool isIsaAcc = false;
				listOfAccounts.push_back(dynamic_cast<Account*>(new Savings(deposit, isIsaAcc)));
			}
			else {
				std::cout << "You are only allowed 1 Current Account, and 1 Isa account with a minimum deposit of £1000" << std::endl;
			}
			//Assigns the most recent account as the active account
			activeAccount = listOfAccounts.back();
			
		}
		else if (command.compare("view") == 0)
		{
			//Checking that the acount list isn't empty
			if (listOfAccounts.empty()) {
				std::cout << "No accounts to show." << std::endl;
				continue;
			}
			// Lambda to print account history
			auto printAccountDetails = [](Account* account, int displayIndex) {
				if (auto* currentAccount = dynamic_cast<Current*>(account)) {
					std::cout << "Account " << displayIndex << ": ";
					currentAccount->toString();
				}
				else if (auto* savingsAccount = dynamic_cast<Savings*>(account)) {
					std::cout << "Account " << displayIndex << ": ";
					savingsAccount->toString();
				}
				else {
					std::cout << "Unknown account type at index " << displayIndex << ".\n";
				}
			};
			//View a specific account
			if (parameters.size() > 1) {
				int indexOfAccount = safeStringToNum<int>(parameters[1]) - 1;

				if (indexOfAccount >= 0 && indexOfAccount < listOfAccounts.size()) {
					Account* account = listOfAccounts[indexOfAccount];
					activeAccount = account;

					printAccountDetails(account, indexOfAccount + 1);
				}
				else {
					std::cout << "Invalid account index: " << (indexOfAccount + 1) << "." << std::endl;
				}
			}
			else {
				//Printing all accounts
				for (int i = 0; i < listOfAccounts.size(); i++) {
					printAccountDetails(listOfAccounts[i], i + 1);
				}
			}
		}
		else if (command.compare("withdraw") == 0)
		{
			//Checks that there is the correct amount of variables
			if (parameters.size() < 2) {
				std::cout << "Please enter the amount you would like to withdraw." << std::endl;
				continue;
			}
			*type = "Withdraw";
			double amount = safeStringToNum<double>(parameters[1]);
			//Checking to ensure its a valid amount
			if (amount <= -1) {
				continue;
			}
			//Ensuring an account has been created
			if (!activeAccount) {
				std::cout << "No active account, please create or select one.\n";
				continue;
			}
			//Withdraws the specified amount
			if ((activeAccount->getType()) == "Current") {
				Current* currentAccount = dynamic_cast<Current*>(activeAccount);
				currentAccount->withdraw(amount, *type);
			}
			else {
				Savings* currentAccount = dynamic_cast<Savings*>(activeAccount);
				currentAccount->withdraw(amount, *type);
			}
			
		}
		else if (command.compare("deposit") == 0)
		{
			//Checks that there is the correct amount of variables
			if (parameters.size() < 2) {
				std::cout << "Please enter the amount you would like to deposit." << std::endl;
				continue;
			}
			*type = "Deposit";
			double amount = safeStringToNum<double>(parameters[1]);
			//Checking to ensure its a valid amount
			if (amount <= -1) {
				continue;
			}
			//Ensuring an account has been created
			if (!activeAccount) {
				std::cout << "No active account, please create or select one.\n";
				continue;
			}
			//Depositing the amount
			if ((activeAccount->getType()) == "Current") {
				Current* currentAccount = dynamic_cast<Current*>(activeAccount);
				currentAccount->deposit(amount, *type);
			}
			else {
				Savings* currentAccount = dynamic_cast<Savings*>(activeAccount);
				currentAccount->deposit(amount, *type);
			}
		}
		else if (command.compare("transfer") == 0)
		{
			//Checks that there is the correct amount of variables
			if (parameters.size() < 4) {
				std::cout << "Please enter the account you want to tranfer money into and from." << std::endl;
				continue;
			}
			//Validating all the inputs
			int transferFrom = (safeStringToNum<int>(parameters[1])) - 1;
			int transferTo = (safeStringToNum<int>(parameters[2])) - 1;
			double amount = safeStringToNum<double>(parameters[3]);
			//Checks that the strings were succesfully changed
			if (transferFrom < 0 || transferTo < 0 || amount < 0) {
				continue;
			}
			if (listOfAccounts.size() < 2) {
				std::cout << "Not enough accounts to do a bank transfer." << std::endl;
				continue;
			}
			if (transferFrom == transferTo) {
				std::cout << "Cannot transfer money into the same account" << std::endl;
				continue;
			}

			*type = "Transfer to account " + std::to_string(transferTo);
	
			Account* sourceAccount = listOfAccounts[transferFrom];
			//Creates a bool that checks the account has sufficient funds
			bool sufficientFunds = false;

			if (auto* currentAccount = dynamic_cast<Current*>(sourceAccount)) {
				if ((currentAccount->getBalance() - amount) >= currentAccount->getOverdraft()) {
					currentAccount->withdraw(amount, *type);
					sufficientFunds = true;
				}
				else {
					std::cout << "Insufficient funds in the Current account!" << std::endl;
				}
			}
			else if (auto* savingsAccount = dynamic_cast<Savings*>(sourceAccount)) {
				if ((savingsAccount->getBalance() - amount) >= 0) {
					savingsAccount->withdraw(amount, *type);
					sufficientFunds = true;
				}
				else {
					std::cout << "Insufficient funds in the Savings account!" << std::endl;
				}
			}
			//Only continues if the last transaction was succesful
			if (sufficientFunds) {

				Account* targetAccount = listOfAccounts[transferTo];
				*type = "Transfer from account " + std::to_string(transferFrom);

				if (auto* currentAccount = dynamic_cast<Current*>(targetAccount)) {
					currentAccount->deposit(amount, *type);
				}
				else if (auto* savingsAccount = dynamic_cast<Savings*>(targetAccount)) {
					savingsAccount->deposit(amount, *type);
				}
				else {
					std::cout << "Unknown account type." << std::endl;
				}
			}
		}

		else if (command.compare("project") == 0)
		{
			//Checks that there is the correct amount of variables
			if (parameters.size() < 2) {
				std::cout << "Please enter the amount of years you would like to compute the interest to." << std::endl;
				continue;
			}
			int years = safeStringToNum<int>(parameters[1]);
			//Checks that the string was succesfully changed to an int
			if (years < 0) {
				continue;
			}
			//Checks the account type, and then computes the interest
			if (auto* currentAccount = dynamic_cast<Current*>(activeAccount)) {
				std::cout << "Cannot project interest on a current account" << std::endl;
			}
			else if(auto* savingsAccount = dynamic_cast<Savings*>(activeAccount)) {
				savingsAccount->computeInterest(years);
			}
			else {
				std::cout << "Unknown account type." << std::endl;
			}
		}
		else if (command.compare("search") == 0)
		{
			//Checks that there is the correct amount of variables
			if (parameters.size() < 2) {
				std::cout << "Please enter the amount you would like to search for." << std::endl;
				continue;
			}
			double amountToSearchFor = safeStringToNum<double>(parameters[1]);
			//Checks that the string was succesfully changed to an double
			if (amountToSearchFor < 0) {
				continue;
			}
			//Checks that there is an active account
			if (!activeAccount) {
				std::cout << "No active account, please create or select one.\n";
				continue;
			}
			activeAccount->searchForTransaction(amountToSearchFor);
		}
	}
	//Releasing memory
	for (auto acccount : listOfAccounts) {
		delete acccount;
	}

	delete type;

	std::cout << "Press any key to quit...";
	std::getchar();
}
