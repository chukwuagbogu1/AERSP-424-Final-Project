#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <ctime>

//Defiining all types of banking transactions
enum class TransactionType {
    DEPOSIT, //Add money to account
    WITHDRAWAL, //Remove money from account
    TRANSFER_SENT, //Send money to another account
    TRANSFER_RECEIVED //Receive money from another account
};

class FileHandler;

//Class to record and manage individual transactions
class Transaction {
private:
    std::string accountNumber; //Account ID
    TransactionType type;  //Account type
    double amount; // Money amount
    std::time_t timestamp;  //Time of transaction
    std::string description;  //Additional details

public:
    //create new transaction
    Transaction(const std::string& accNum, TransactionType type, double amount,
        const std::string& desc = "");

    // Getters for transaction details
    std::string getAccountNumber() const { return accountNumber; }
    TransactionType getType() const { return type; }
    double getAmount() const { return amount; }
    std::time_t getTimestamp() const { return timestamp; }
    std::string getDescription() const { return description; }
    std::string getDate() const { return std::ctime(&timestamp); }

    //Convert transaction to string for storage
    // String representation for file storage
    std::string toString() const;

    friend class FileHandler;
};
#endif