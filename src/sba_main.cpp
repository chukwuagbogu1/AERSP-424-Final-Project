#include <iostream>
#include <string>
#include <limits>
#include "Bank.h"
#include "Chatbot.h"
#include <sba_bank2.cpp>s
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void displayMenu() {
    std::cout << "\nBanking System Menu\n"
        << "1. Create Account\n"
        << "2. Login\n"
        << "3. Chat with Assistant\n"
        << "4. Exit\n"
        << "Enter your choice: ";
}
void displayLoggedInMenu() {
    std::cout << "\nAccount Menu\n"
        << "1. Check Balance\n"
        << "2. Deposit\n"
        << "3. Withdraw\n"
        << "4. Transfer\n"
        << "5. Transaction History\n"
        << "6. Logout\n"
        << "Enter your choice: ";
}
int main() {
    Bank bank;
    Chatbot chatbot;

    while (true) {
        clearScreen();
        displayMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            std::string name, password;
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            std::cout << "Enter password: ";
            std::getline(std::cin, password);

            if (bank.createAccount(name, password)) {
                std::cout << "Account created successfully!\n";
            }
            break;
        }
        case 2: {
            std::string accountNumber, password;
            std::cout << "Enter account number: ";
            std::getline(std::cin, accountNumber);
            std::cout << "Enter password: ";
            std::getline(std::cin, password);

            UserAccount* account = bank.login(accountNumber, password);
            if (account) {
                bool loggedIn = true;
                while (loggedIn) {
                    clearScreen();
                    std::cout << "Welcome, " << account->getName() << "!\n";
                    displayLoggedInMenu();

                    int subChoice;
                    std::cin >> subChoice;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    switch (subChoice) {
                    case 1:
                        std::cout << "Current balance: $" << account->getBalance() << "\n";
                        break;
                    case 2: {
                        double amount;
                        std::cout << "Enter amount to deposit: $";
                        std::cin >> amount;
                        account->deposit(amount);
                        std::cout << "Deposit successful!\n";
                        break;
                    }
                    case 3: {
                        double amount;
                        std::cout << "Enter amount to withdraw: $";
                        std::cin >> amount;
                        if (account->withdraw(amount)) {
                            std::cout << "Withdrawal successful!\n";
                        }
                        else {
                            std::cout << "Insufficient funds!\n";
                        }
                        break;
                    }
                    case 4: {
                        std::string toAccount;
                        double amount;
                        std::cout << "Enter recipient's account number: ";
                        std::getline(std::cin, toAccount);
                        std::cout << "Enter amount to transfer: $";
                        std::cin >> amount;

                        if (bank.transfer(accountNumber, toAccount, amount)) {
                            std::cout << "Transfer successful!\n";
                        }
                        else {
                            std::cout << "Transfer failed!\n";
                        }
                        break;
                    }
                    case 5: {
                        auto history = bank.getTransactionHistory(accountNumber);
                        std::cout << "\nTransaction History:\n";
                        for (const auto& trans : history) {
                            std::cout << "Date: " << std::ctime(&trans.getTimestamp())
                                << "Type: " << static_cast<int>(trans.getType())
                                << " Amount: $" << trans.getAmount()
                                << " Description: " << trans.getDescription() << "\n";
                        }
                        break;
                    }
                    case 6:
                        loggedIn = false;
                        break;
                    }
                    if (loggedIn) {
                        std::cout << "\nPress Enter to continue...";
                        std::cin.get();
                    }
                }
            }
            else {
                std::cout << "Invalid account number or password!\n";
            }
            break;
        }
        case 3: {
            std::string query;
            std::cout << "Chat with our assistant (type 'exit' to return to main menu)\n";
            while (true) {
                std::cout << "\nYou: ";
                std::getline(std::cin, query);
                if (query == "exit") break;
                std::cout << "Assistant: " << chatbot.getResponse(query) << "\n";
            }
            break;
        }
        case 4:
            std::cout << "Thank you for using our banking system!\n";
            return 0;
        }

        if (choice != 4) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }

    return 0;
}