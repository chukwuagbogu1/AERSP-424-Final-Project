#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

enum class TransactionType {
    DEPOSIT,    //Money added to account
    WITHDRAWAL, //Money removed from account    
    TRANSFER_SENT,      //Money sent to another account
    TRANSFER_RECEIVED  //Money received from another account
};
class Transaction {
private:
    std::string accountNumber; // Account aassociated with transaction
    TransactionType type;  //Type of transaction
    double amount; //Amount of transaction
    std::string date;  //Date of transaction    
    std::string description;  //Description of transaction
public:
    Transaction(const std::string& accNum, TransactionType type, double amount, 
               const std::string& desc = "");

    // Getters
    std::string getAccountNumber() const { return accountNumber; }
    TransactionType getType() const { return type; }
    double getAmount() const { return amount; }
    std::string getDate() const { return date; }
    std::string getDescription() const { return description; }

    Transaction(TransactionType t, double amt, const std::string& desc);

    // String representation for file storage
    std::string toString() const;

    //Friend class declaration
    friend class FileHandler;  // Allows FileHandler to access private members
 
};

#endif
