#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <map>
#include <vector>
#include "UserAccount.h"
#include "Transaction.h"
class Bank {
private:  //Maps account numbers to UserAccount objects for quick and easy access
    std::map<std::string, UserAccount> accounts;  //stores all transactions across all acocunts
    std::vector<Transaction> transactions;

   
public:
    Bank();
    
    // Account management
    bool createAccount(const std::string& name, const std::string& password, const std::string& securityQuestion, const std::string& securityAnswer);
    UserAccount* login(const std::string& accountNumber, const std::string& password);
    bool resetPassword(const std::string& accountNumber, const std::string& securityAnswer,const std::string& newPassword);
    // Transaction operations
    bool transfer(const std::string& fromAccount, const std::string& toAccount, double amount);
    std::vector<Transaction> getTransactionHistory(const std::string& accountNumber) const;
    
    // Data persistence
    void loadData();
    void saveData() const;
    std::map<std::string, UserAccount>& getAccounts();
};
#endif
