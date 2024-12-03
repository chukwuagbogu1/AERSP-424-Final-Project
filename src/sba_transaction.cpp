#include "Transaction.h"
#include <ctime>
#include <sstream>
#include <iomanip>
Transaction::Transaction(TransactionType t, double amt, const std::string& desc)
    : type(t), amount(amt), description(desc) {
    // Get current time and format it
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    std::stringstream ss;
    ss << std::setfill('0') 
       << std::setw(2) << ltm->tm_mday << "/"
       << std::setw(2) << 1 + ltm->tm_mon << "/"
       << 1900 + ltm->tm_year << " "
       << std::setw(2) << ltm->tm_hour << ":"
       << std::setw(2) << ltm->tm_min;
    
    date = ss.str();
}
std::string Transaction::toString() const {
    std::stringstream ss;
    ss << static_cast<int>(type) << "|"
       << amount << "|"
       << date << "|"
       << description;
    return ss.str();
}