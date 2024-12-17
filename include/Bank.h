#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <map>
#include <vector>
#include "UserAccount.h"
#include "Transaction.h"

//Main class handling all banking operations
class Bank {
private:  //Store accounts with account number as key
    std::map<std::string, UserAccount> accounts;  //List of all transactions performed
    std::vector<Transaction> transactions;

   
public: //Initialize bank system
    Bank();
    
    // Account management. Create new user account with security details 
    bool createAccount(const std::string& name, const std::string& password, const std::string& securityQuestion, const std::string& securityAnswer);
    //Authenticate user and return account pointer 
    UserAccount* login(const std::string& accountNumber, const std::string& password);
    //Resets password using security answer
    bool resetPassword(const std::string& accountNumber, const std::string& securityAnswer,const std::string& newPassword);
    // Transaction operations. Transfers money between accounts
    bool transfer(const std::string& fromAccount, const std::string& toAccount, double amount);
    //Get list of transactions for specific amount
    std::vector<Transaction> getTransactionHistory(const std::string& accountNumber) const;
    
    // Data persistence
    void loadData(); //Load accounts and transactions from storage
    void saveData() const; //Save current state to storage
    std::map<std::string, UserAccount>& getAccounts(); // Get all accounts (for admin purposes)
};
#endif
