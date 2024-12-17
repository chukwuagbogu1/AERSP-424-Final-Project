#include "Bank.h"
#include "FileHandler.h"

// Initializes bank and load existing data
Bank::Bank() {
    loadData();
}

//Create new account with security details
//Returns false if account with the same name exists
bool Bank::createAccount(const std::string& name, const std::string& password, const std::string& securityQuestion, const std::string& securityAnswer) {
    // Check if an account with this name already exists
    for (const auto& pair : accounts) {
        if (pair.second.getName() == name) {
            std::cout << "An account with this name already exist. Please enter a different name or exit to the main menu and log in with the account number associated with this name" << std::endl;
            return false; // Account with this name already exists
        }
    }

    //Create and store new account
    UserAccount newAccount(name, password, securityQuestion, securityAnswer);

    std::string accountNum =
        newAccount.getAccountNumber()
        ;
    accounts[accountNum] = newAccount;

    // Log the account creation and number for debugging
    std::cout << "Created account with number: " << accountNum << std::endl;


    saveData();
    return true;
}

bool Bank::resetPassword(const std::string& accountNumber, const std::string& securityAnswer,
    const std::string& newPassword) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end() && it->second.verifySecurityAnswer(securityAnswer)) {
        it->second.resetPassword(newPassword);
        saveData();
        return true;
    }
    return false;
}
//Authenticate user and return account pointer if successful
UserAccount* Bank::login(const std::string& accountNumber, const std::string& password) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end() && it->second.verifyPassword(password)) {
        return &it->second;
    }
    return nullptr;
}

//Transfer money between accounts
//Returns false if either account not found or insufficient funds
bool Bank::transfer(const std::string& fromAccount, const std::string& toAccount, double amount) {
    auto fromIt = accounts.find(fromAccount);
    auto toIt = accounts.find(toAccount);

    if (fromIt != accounts.end() && toIt != accounts.end()) {
        if (fromIt->second.withdraw(amount)) {
            toIt->second.deposit(amount);

            // Record transactions for both accounts
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

//Get all transactions for specific account
std::vector<Transaction> Bank::getTransactionHistory(const std::string& accountNumber) const {
    std::vector<Transaction> history;
    for (const auto& transaction : transactions) {
        if (transaction.getAccountNumber() == accountNumber) {
            history.push_back(transaction);
        }
    }
    return history;
}

//Load accounts and transactions from storage
void Bank::loadData() {
    FileHandler::loadAccounts(accounts);
    FileHandler::loadTransactions(transactions);
}

//Save current state to persistent storage
void Bank::saveData() const {
    for (const auto& account : accounts) {
        FileHandler::saveAccount(account.second);
    }
    for (const auto& transaction : transactions) {
        FileHandler::saveTransaction(transaction);
    }
}
//Get all accounts (admin access)
std::map<std::string, UserAccount>& Bank::getAccounts() {
    return accounts;
}