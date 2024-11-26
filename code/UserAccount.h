#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H
#include <string>
#include <vector>
#include "Transaction.h"
class UserAccount {
private:
    std::string accountNumber;
    std::string password;
    double balance;
    std::vector<Transaction> transactionHistory;
public:
    UserAccount(const std::string& accNum, const std::string& pwd);

    // Getters
    std::string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    const std::vector<Transaction>& getTransactionHistory() const { return transactionHistory; }

    // Account operations
    bool verifyPassword(const std::string& pwd) const;
    bool deposit(double amount);
    bool withdraw(double amount);
    void addTransaction(const Transaction& transaction);

    // File operations
    void saveToFile() const;
    static UserAccount loadFromFile(const std::string& accNum);
};
#endif
