#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H
#include <string>
#include <vector>

class UserAccount {
private:
    std::string accountNumber; //Unique account identifier
    std::string password; //User's account password
    double balance; //User's account balance
    std::string name; //User's name
    std::string securityQuestion; // Security question
    std::string securityAnswer;   // Answer to security question

public:
    UserAccount() {};

    UserAccount(const std::string& accNum, const std::string& pwd, const std::string& securityQuestion, const std::string& securityAnswer);

    // Getters method
    std::string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    std::string getName() const { return name; }

    // Account operations
    bool verifyPassword(const std::string& pwd) const;
    bool verifySecurityAnswer(const std::string& answer) const;
    void resetPassword(const std::string& newPassword);

    bool deposit(double amount);
    bool withdraw(double amount);
    

    // Static method to generate unique account numbers
    static std::string generateAccountNumber();

    // Friend class declaration for file operations
    friend class FileHandler;  //Allows FileHandler to access private members

};
#endif
