#ifndef BANK_H
#define BANK_H

#include <map>
#include <vector>
#include "UserAccount.h"
#include "Transaction.h"
class Bank {
private:
    std::map<std::string, UserAccount> accounts;
    std::vector<Transaction> transactions;

   
public:
    Bank();
    
    // Account management
    bool createAccount(const std::string& name, const std::string& password);
    UserAccount* login(const std::string& accountNumber, const std::string& password);
    
    // Transaction operations
    bool transfer(const std::string& fromAccount, const std::string& toAccount, double amount);
    std::vector<Transaction> getTransactionHistory(const std::string& accountNumber) const;
    
    // Data persistence
    void loadData();
    void saveData() const;
};
#endif
