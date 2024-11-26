#include <iostream>
#include <string>
#include <limits>
#include "Bank.h"
#include "Chatbot.h"
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void displayMenu() {
    std::cout << "\n=== Banking Service Menu ===\n"
              << "1. Create new account\n"
              << "2. Login to existing account\n"
              << "3. Chat with support bot\n"
              << "4. Exit\n"
              << "Enter your choice: ";
}
void displayLoggedInMenu() {
    std::cout << "\n=== Account Menu ===\n"
              << "1. Check balance\n"
              << "2. View transaction history\n"
              << "3. Deposit/Withdraw\n"
              << "4. Transfer money\n"
              << "5. Logout\n"
              << "Enter your choice: ";
}
void handleNewAccount() {
    std::string password;
    std::cout << "Enter password for new account: ";
    std::cin >> password;
    
    std::string accountNumber = Bank::getInstance()->createAccount(password);
    std::cout << "Account created successfully!\n"
              << "Your account number is: " << accountNumber << "\n"
              << "Please save this number for future reference.\n";
}
void handleLogin() {
    std::string accountNumber, password;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    std::cout << "Enter password: ";
    std::cin >> password;
    
    UserAccount* account = Bank::getInstance()->getAccount(accountNumber);
    if (account && account->verifyPassword(password)) {
        bool logout = false;
        while (!logout) {
            displayLoggedInMenu();
            int choice;
            std::cin >> choice;
            
            switch (choice) {
                case 1: // Check balance
                    std::cout << "Current balance: $" << account->getBalance() << std::endl;
                    break;
                    
                case 2: // View transaction history
                    std::cout << "\nTransaction History:\n";
                    for (const auto& trans : account->getTransactionHistory()) {
                        std::cout << trans.toString() << std::endl;
                    }
                    break;
                    
                case 3: { // Deposit/Withdraw
                    std::cout << "1. Deposit\n2. Withdraw\nChoice: ";
                    int subChoice;
                    std::cin >> subChoice;
                    
                    double amount;
                    std::cout << "Enter amount: $";
                    std::cin >> amount;
                    
                    if (subChoice == 1) {
                        if (account->deposit(amount)) {
                            std::cout << "Deposit successful!\n";
                        } else {
                            std::cout << "Invalid amount for deposit.\n";
                        }
                    } else if (subChoice == 2) {
                        if (account->withdraw(amount)) {
                            std::cout << "Withdrawal successful!\n";
                        } else {
                            std::cout << "Insufficient funds or invalid amount.\n";
                        }
                    }
                    break;
                }
                
                case 4: { // Transfer money
                    std::string targetAccount;
                    double amount;
                    
                    std::cout << "Enter target account number: ";
                    std::cin >> targetAccount;
                    std::cout << "Enter amount to transfer: $";
                    std::cin >> amount;
                    
                    if (Bank::getInstance()->transfer(accountNumber, targetAccount, amount)) {
                        std::cout << "Transfer successful!\n";
                    } else {
                        std::cout << "Transfer failed. Please check account number and amount.\n";
                    }
                    break;
                }
                
                case 5: // Logout
                    logout = true;
                    break;
                
                default:
                    std::cout << "Invalid choice.\n";
            }
        }
    } else {
        std::cout << "Invalid account number or password.\n";
    }
}
void handleChatbot() {
    Chatbot chatbot;
    std::string query;
    
    std::cout << "Chat with our support bot (type 'exit' to return to main menu)\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    while (true) {
        std::cout << "\nYou: ";
        std::getline(std::cin, query);
        
        if (query == "exit") break;
        
        std::cout << "Bot: " << chatbot.getResponse(query) << std::endl;
    }
}
int main() {
    // Create accounts directory if it doesn't exist
    system("mkdir -p accounts");
    
    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                handleNewAccount();
                break;
            case 2:
                handleLogin();
                break;
            case 3:
                handleChatbot();
                break;
            case 4:
                std::cout << "Thank you for using our banking service!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}