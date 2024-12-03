#include "FileHandler.h"
#include <fstream>
#include <sstream>
void FileHandler::saveAccount(const UserAccount& account) {
    std::ofstream file("accounts.txt", std::ios::app);
    if (file.is_open()) {
        file << account.accountNumber << "|"
             << account.name << "|"
             << account.password << "|"
             << account.balance << "\n";
        file.close();
    }
}
void FileHandler::saveTransaction(const Transaction& transaction) {
    std::ofstream file("transactions.txt", std::ios::app);
    if (file.is_open()) {
        file << transaction.toString() << "\n";
        file.close();
    }
}
void FileHandler::loadAccounts(std::map<std::string, UserAccount>& accounts) {
    std::ifstream file("accounts.txt");
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string accNum, name, password;
        double balance;
        
        std::getline(ss, accNum, '|');
        std::getline(ss, name, '|');
        std::getline(ss, password, '|');
        ss >> balance;
        
        UserAccount account(name, password);
        account.accountNumber = accNum;
        account.balance = balance;
        accounts[accNum] = account;
    }
}
void FileHandler::loadTransactions(std::vector<Transaction>& transactions) {
    std::ifstream file("transactions.txt");
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string accNum, typeStr, amountStr, timestampStr, desc;
        
        std::getline(ss, accNum, '|');
        std::getline(ss, typeStr, '|');
        std::getline(ss, amountStr, '|');
        std::getline(ss, timestampStr, '|');
        std::getline(ss, desc);
        
        TransactionType type = static_cast<TransactionType>(std::stoi(typeStr));
        double amount = std::stod(amountStr);
        std::time_t timestamp = std::stoull(timestampStr);
        
        Transaction transaction(accNum, type, amount, desc);
        transaction.timestamp = timestamp;
        transactions.push_back(transaction);
    }
}