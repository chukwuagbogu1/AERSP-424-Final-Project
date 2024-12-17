#include "Transaction.h"
#include <sstream>
#include <iomanip>

//Constructor to create new transaction
Transaction::Transaction(const std::string& accNum, TransactionType type,
    double amount, const std::string& desc)
    : accountNumber(accNum), type(type), amount(amount),
    description(desc), timestamp(std::time(nullptr)) {
}

//Convert transaction to string format for storage
std::string Transaction::toString() const {
    std::stringstream ss;
    //Format: accountnumber|type|amount|timestamp|description
    ss << accountNumber << "|"
        << static_cast<int>(type) << "|"
        << std::fixed << std::setprecision(2) << amount << "|"
        << timestamp << "|"
        << description;
    return ss.str();
}