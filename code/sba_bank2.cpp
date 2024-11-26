#include "Bank.h"
#include <random>
#include <sstream>
#include <filesystem>
Bank* Bank::instance = nullptr;
Bank* Bank::getInstance() {
    if (instance == nullptr) {
        instance = new Bank();
        instance->loadAccounts();
    }
    return instance;
}
std::string Bank::createAccount(const std::string& password) {
    // Generate unique account number
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000000, 99999999);
    
    std::string accountNumber;
    do {
        accountNumber = std::to_string(dis(gen));
    } while (accounts.find(accountNumber) != accounts.end());
    
    UserAccount newAccount(accountNumber, password);
    accounts[accountNumber] = newAccount;
    newAccount.saveToFile();
    
    return accountNumber;
}
UserAccount* Bank::getAccount(const std::string& accountNumber) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        return &(it->second);
    }
    return nullptr;
}
bool Bank::transfer(const std::string& fromAcc, const std::string& toAcc, double amount) {
    UserAccount* from = getAccount(fromAcc);
    UserAccount* to = getAccount(toAcc);
    
    if (!from || !to || amount <= 0 || amount > from->getBalance()) {
        return false;
    }
    
    // Perform transfer
    if (from->withdraw(amount)) {
        if (to->deposit(amount)) {
            Transaction transSent(TransactionType::TRANSFER_SENT, amount, 
                                "Transfer to " + toAcc);
            Transaction transReceived(TransactionType::TRANSFER_RECEIVED, amount, 
                                   "Transfer from " + fromAcc);
            
            from->addTransaction(transSent);
            to->addTransaction(transReceived);
            
            from->saveToFile();
            to->saveToFile();
            return true;
        }
        // If deposit fails, rollback withdrawal
        from->deposit(amount);
    }
    return false;
}
void Bank::loadAccounts() {
    namespace fs = std::filesystem;
    std::string path = "accounts/";
    
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ".txt") {
            std::string accNum = entry.path().stem().string();
            accounts[accNum] = UserAccount::loadFromFile(accNum);
        }
    }
}
void Bank::saveAccounts() const {
    for (const auto& pair : accounts) {
        pair.second.saveToFile();
    }
}