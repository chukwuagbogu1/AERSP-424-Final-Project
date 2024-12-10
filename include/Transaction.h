#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <ctime>
enum class TransactionType {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER_SENT,
    TRANSFER_RECEIVED
};

class FileHandler;

class Transaction {
private:
    std::string accountNumber;
    TransactionType type;
    double amount;
    std::time_t timestamp;
    std::string description;

public:
    Transaction(const std::string& accNum, TransactionType type, double amount,
        const std::string& desc = "");

    // Getters
    std::string getAccountNumber() const { return accountNumber; }
    TransactionType getType() const { return type; }
    double getAmount() const { return amount; }
    std::time_t getTimestamp() const { return timestamp; }
    std::string getDescription() const { return description; }
    std::string getDate() const { return std::ctime(&timestamp); }


    // String representation for file storage
    std::string toString() const;

    friend class FileHandler;
};
#endif