 #include "FileHandler.h"
#include <fstream>
#include <sstream>

//Save account detail to file
void FileHandler::saveAccount(const UserAccount& account) {
    std::ofstream file("accounts.txt", std::ios::app);
    if (file.is_open()) {
        //write account data in pipe-delimited format
        file << account.accountNumber << "|"
            << account.name << "|"
            << account.password << "|"
            << account.balance << "|"
            << account.securityQuestion << "|"
            << account.securityAnswer << "\n";
        file.close();
    }
}

//Save transaction records to file
void FileHandler::saveTransaction(const Transaction& transaction) {
    std::ofstream file("transactions.txt", std::ios::app);
    if (file.is_open()) {
        //Write transaction datat as string
        file << transaction.toString() << "\n";
        file.close();
    }
}

//Laod accounts from storage file
void FileHandler::loadAccounts(std::map<std::string, UserAccount>& accounts) {
    std::ifstream file("accounts.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string accNum, name, password, securityQuestion, securityAnswer;
        double balance;
        
        std::getline(ss, accNum, '|');
        std::getline(ss, name, '|');
        std::getline(ss, password, '|');
        ss >> balance;
        ss.ignore(); // Skip the delimiter
        std::getline(ss, securityQuestion, '|');
        std::getline(ss, securityAnswer);

        UserAccount account(name, password, securityQuestion, securityAnswer);
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
        //Parse pipe-delimited account data
        std::getline(ss, accNum, '|');
        std::getline(ss, typeStr, '|');
        std::getline(ss, amountStr, '|');
        std::getline(ss, timestampStr, '|');
        std::getline(ss, desc);
        
        //Convert string data to appropriate types
        TransactionType type = static_cast<TransactionType>(std::stoi(typeStr));
        double amount = std::stod(amountStr);
        std::time_t timestamp = std::stoull(timestampStr);

        //Create and store transaction object
        Transaction transaction(accNum, type, amount, desc);
        transaction.timestamp = timestamp;
        transactions.push_back(transaction);
    }
}