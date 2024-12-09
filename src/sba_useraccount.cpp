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
bool UserAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
    return balance;
}
/**
 * \brief Withdraw money from the account.
 *
 * If the amount is positive and does not exceed the current balance, the
 * balance is reduced by the amount and true is returned. Otherwise, false is
 * returned.
 *
 * \param amount Positive amount of money to withdraw.
 * \return True if the withdrawal is successful, false otherwise.
 */
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