#include "UserAccount.h"
#include <random>
#include <sstream>
UserAccount::UserAccount(const std::string& name, const std::string& password)
    : name(name), password(password), balance(0.0) {
    accountNumber = generateAccountNumber();
}
bool UserAccount::verifyPassword(const std::string& inputPassword) const {
    return password == inputPassword;
}
void UserAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}
bool UserAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}
std::string UserAccount::generateAccountNumber() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 9);

    std::stringstream ss;
    for (int i = 0; i < 10; ++i) {
        ss << dis(gen);
    }
    return ss.str();
}