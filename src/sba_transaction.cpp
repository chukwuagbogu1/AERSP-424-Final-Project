#include "Transaction.h"
#include <sstream>
std::string Transaction::toString() const {
    std::stringstream ss;
    ss << accountNumber << "|"
       << static_cast<int>(type) << "|"
       << amount << "|"
       << date << "|"
       << description;
    return ss.str();
}
Transaction Transaction::fromString(const std::string& str) {
    std::stringstream ss(str);
    std::string accNum, dateStr, desc;
    int typeInt;
    double amt;
    
    std::getline(ss, accNum, '|');
    ss >> typeInt;
    ss.ignore(); // Skip the delimiter
    ss >> amt;
    ss.ignore();
    std::getline(ss, dateStr, '|');
    std::getline(ss, desc);
    return Transaction(accNum, 
                      static_cast<TransactionType>(typeInt),
                      amt,
                      desc);
}
