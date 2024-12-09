#include "Bank.h"
#include "FileHandler.h"
Bank::Bank() {
    loadData();
}
bool Bank::createAccount(const std::string& name, const std::string& password) {
    UserAccount newAccount(name, password);
    accounts[newAccount.getAccountNumber()] = newAccount;
    saveData();
    return true;
}
UserAccount* Bank::login(const std::string& accountNumber, const std::string& password) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end() && it->second.verifyPassword(password)) {
        return &it->second;
    }
    return nullptr;
}
bool Bank::transfer(const std::string& fromAccount, const std::string& toAccount, double amount) {
    auto fromIt = accounts.find(fromAccount);
    auto toIt = accounts.find(toAccount);

    if (fromIt != accounts.end() && toIt != accounts.end()) {
        if (fromIt->second.withdraw(amount)) {
            toIt->second.deposit(amount);

            // Record transactions
            transactions.emplace_back(fromAccount, TransactionType::TRANSFER_SENT, amount,
                "Transfer to " + toAccount);
            transactions.emplace_back(toAccount, TransactionType::TRANSFER_RECEIVED, amount,
                "Transfer from " + fromAccount);

            saveData();
            return true;
        }
    }
    return false;
}
std::vector<Transaction> Bank::getTransactionHistory(const std::string& accountNumber) const {
    std::vector<Transaction> history;
    for (const auto& transaction : transactions) {
        if (transaction.getAccountNumber() == accountNumber) {
            history.push_back(transaction);
        }
    }
    return history;
}
void Bank::loadData() {
    FileHandler::loadAccounts(accounts);
    FileHandler::loadTransactions(transactions);
}
void Bank::saveData() const {
    for (const auto& account : accounts) {
        FileHandler::saveAccount(account.second);
    }
    for (const auto& transaction : transactions) {
        FileHandler::saveTransaction(transaction);
    }
}