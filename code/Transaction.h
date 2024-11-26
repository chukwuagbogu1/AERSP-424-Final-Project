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
class Transaction {
private:
    TransactionType type;
    double amount;
    std::string date;
    std::string description;
public:
    Transaction(TransactionType t, double amt, const std::string& desc);

    // Getters
    TransactionType getType() const { return type; }
    double getAmount() const { return amount; }
    std::string getDate() const { return date; }
    std::string getDescription() const { return description; }

    // String representation
    std::string toString() const;
};
#endif
