#ifndef BANK_H
#define BANK_H
#include <map>
#include "UserAccount.h"
class Bank {
private:
    std::map<std::string, UserAccount> accounts;
    static Bank* instance;
    Bank() {} // Private constructor for singleton
public:
    static Bank* getInstance();

    // Account operations
    std::string createAccount(const std::string& password);
    UserAccount* getAccount(const std::string& accountNumber);
    bool transfer(const std::string& fromAcc, const std::string& toAcc, double amount);

    // File operations
    void loadAccounts();
    void saveAccounts() const;
};
#endif
