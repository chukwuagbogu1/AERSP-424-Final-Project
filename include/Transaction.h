#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <ctime>
#include <nlohmann/json.hpp>
#include <stdexcept>
// Forward declaration
class FileHandler;
/**
 * Enum representing different types of transactions
 */
enum class TransactionType {
    DEPOSIT,         // Money added to account
    WITHDRAWAL,      // Money removed from account    
    TRANSFER_SENT,   // Money sent to another account
    TRANSFER_RECEIVED // Money received from another account
};
/**
 * Class representing a financial transaction
 */
class Transaction {
private:
    std::string accountNumber;  // Account associated with transaction
    TransactionType type;       // Type of transaction
    double amount;              // Amount of transaction
    std::string date;          // Date of transaction    
    std::string description;    // Description of transaction
    // Helper function to get current date as string
    static std::string getCurrentDate() {
        time_t now = time(nullptr);
        char buffer[26];
        ctime_r(&now, buffer);
        std::string date(buffer);
        return date.substr(0, date.length() - 1); // Remove trailing newline
    }
public:
    // Constructor
    Transaction(const std::string& accNum, 
               TransactionType transType, 
               double transAmount, 
               const std::string& desc = "") 
        : accountNumber(accNum)
        , type(transType)
        , amount(transAmount)
        , date(getCurrentDate())
        , description(desc)
    {
        if (!isValidAmount(transAmount)) {
            throw std::invalid_argument("Invalid transaction amount");
        }
    }
    // Getters
    std::string getAccountNumber() const { return accountNumber; }
    TransactionType getType() const { return type; }
    double getAmount() const { return amount; }
    std::string getDate() const { return date; }
    std::string getDescription() const { return description; }
    // Validation method
    static bool isValidAmount(double amount) {
        return amount > 0 && std::isfinite(amount);
    }
    // String representation for storage
    std::string toString() const;
    // Create from string
    static Transaction fromString(const std::string& str);
};
#endif // TRANSACTION_H
