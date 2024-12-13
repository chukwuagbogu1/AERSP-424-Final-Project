#include "UserAccount.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <iostream>

UserAccount::UserAccount(const std::string& name, const std::string& password, const std:: string& securityQuestion, const std::string& securityAnswer)
    : name(name), password(password), balance(100.0) {
    accountNumber = generateAccountNumber();
    // Log account creation for debugging
    std::cout << "New account created - Name: " << name << ", Account Number: " << accountNumber << std::endl;
}

bool UserAccount::verifyPassword(const std::string& inputPassword) const {
    return password == inputPassword;
}

bool UserAccount::verifySecurityAnswer(const std::string& answer) const {
    return securityAnswer == answer;
}
void UserAccount::resetPassword(const std::string& newPassword) {
    password = newPassword;
    std::cout << "Password reset successful for account: " << accountNumber << std::endl;
}

bool UserAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Deposited " << amount << " to account " << accountNumber << std::endl;
        return true;
    }
    return false;
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
        std::cout << "Withdrawn " << amount << " from account " << accountNumber << std::endl;
        return true;
    }
    return false;
}
std::string UserAccount::generateAccountNumber() {
    // Use current time as seed for more uniqueness
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::system_clock::to_time_t(now);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9999);

    //Combine timestamp and random number for uniqueness
    std::stringstream ss;
    ss << std::setw(6) << std::setfill('0') << (timestamp % 1000000);
    ss << std::setw(4) << std::setfill('0') << dis(gen);


    std::string

        generatedNumber =
        ss.str();
    std::cout << "Generated account number: " << generatedNumber << std::endl;

    return generatedNumber;
}