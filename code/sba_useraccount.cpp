#include "UserAccount.h"
#include <fstream>
#include <iostream>
UserAccount::UserAccount(const std::string& accNum, const std::string& pwd)
    : accountNumber(accNum), password(pwd), balance(0.0) {}
bool UserAccount::verifyPassword(const std::string& pwd) const {
    return password == pwd;
}
bool UserAccount::deposit(double amount) {
    if (amount <= 0) return false;
    
    balance += amount;
    Transaction trans(TransactionType::DEPOSIT, amount, "Deposit");
    addTransaction(trans);
    saveToFile();
    return true;
}
bool UserAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    
    balance -= amount;
    Transaction trans(TransactionType::WITHDRAWAL, amount, "Withdrawal");
    addTransaction(trans);
    saveToFile();
    return true;
}
void UserAccount::addTransaction(const Transaction& transaction) {
    transactionHistory.push_back(transaction);
}
void UserAccount::saveToFile() const {
    std::string filename = "accounts/" + accountNumber + ".txt";
    std::ofstream file(filename);
    
    if (file.is_open()) {
        file << accountNumber << std::endl;
        file << password << std::endl;
        file << balance << std::endl;
        
        for (const auto& trans : transactionHistory) {
            file << trans.toString() << std::endl;
        }
        file.close();
    }
}
UserAccount UserAccount::loadFromFile(const std::string& accNum) {
    std::string filename = "accounts/" + accNum + ".txt";
    std::ifstream file(filename);
    
    std::string acc, pwd;
    double bal;
    
    if (file.is_open()) {
        std::getline(file, acc);
        std::getline(file, pwd);
        file >> bal;
        
        UserAccount account(acc, pwd);
        account.balance = bal;
        
        // Load transactions
        std::string line;
        while (std::getline(file, line)) {
            // Parse and add transactions
            // Implementation details omitted for brevity
        }
        
        file.close();
        return account;
    }
    
    return UserAccount("", ""); // Return empty account if file not found
}