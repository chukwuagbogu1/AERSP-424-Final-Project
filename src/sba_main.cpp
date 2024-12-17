#include <iostream>
#include <string>
#include <limits>
#include "Bank.h"
#include "Chatbot.h"

//Clear console screen based on operating system
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
//Display main menu option to user
void displayMenu() {
    std::cout << "\nWelcome to A-VK Bank\n\n"
        <<"Home Menu\n"
        << "1. Create Account\n"
        << "2. Login\n"
        << "3. Reset Password\n"
        << "4. Chat with Assistant\n"
        << "5. Exit\n"
        <<"\n\n\n\n\n"
        <<"Disclaimer: Investment involves risk. There is always the potential of losing money\nwhen you invest in securities.\n"
        <<"Asset allocation, diversification, and rebalancing do not ensure a profit or protect\nagainst loss in declining markets.\n\n"
        <<"Though A-VK Bank, their affiliates and advisor may not be qualified to provide legal,\ntax or accounting advice, YOU CAN TRUST US BRO!\n"
        <<"Clients should please consult presenters for any money transfer issues, and direct all\nC++ questions to Prof. Miller and his trusted TAs. We don't have time for that here\n\n"
        <<"A-VK Bank offers a broad range of brokerage, investment advisory (including financial\nplanning) and other services.\n"
        <<"We try to safeguard accounts from Scams, Phishing, and all sorts of malicious activity \nincluding but not limited to Nigerian Princes, but for a fee of course\n\n"
        <<"Insurance and annuity products are offered through A-VK Life Agency, a licensed\ninsurance agency and wholly owned and distributed by Frosty Diamond Corp.\n"
        <<"While we offer insurance, ours is a DividedHealthCare Life coverage\n" 
        <<"Names of our CEOs and Board of Trustees are sealed records and shall remain so until\na certain time has passed.\n"
        <<"\n\n"
        <<"Investment, insurance, and annuity products: \n"
        <<"Are Not FDIC Insured\n"
        <<"Are *Definitely* Not Bank Guaranteed\n"
        <<"Will Lose Value\n"
        <<"Are Not Deposits\n"
        <<"Are Not Insured by Any Federal Government Agency\n"
        <<"Are Not a Condition to Any Banking Service or Activity\n"
        <<"Are Not Usable at Your local McDonald's for fear of Breach of Identity\n\n"
        <<"After reading and understanding all of the above, please\n"
        << "Enter your choice: ";
}

// Display menu options for logged-in users
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
    // Initialize bank and chatbot systems
    Bank bank;
    Chatbot chatbot;

    // Main application loop
    while (true) {
        clearScreen();
        displayMenu();

        // Get user menu choice
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            // Account Creation
            std::string name, password, securityQuestion, securityAnswer;
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            std::cout << "Enter security question: ";
            std::getline(std::cin, securityQuestion);
            std::cout << "Enter security answer: ";
            std::getline(std::cin, securityAnswer);
            
            // Create account and show result
            if (bank.createAccount(name, password, securityQuestion, securityAnswer)) {
                std::cout << "Account created successfully!\n";
            }
            else {
                std::cout << "Failed to create account.\n";
            }
            break;
        }
        case 2: {
            //Login process
            std::string accountNumber, password;
            std::cout << "Enter account number: ";
            std::getline(std::cin, accountNumber);
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            
            //User's attempt to log in
            UserAccount* account = bank.login(accountNumber, password);
            if (account) {
                bool loggedIn = true;
                //Logged in user menu loop
                while (loggedIn) {
                    clearScreen();
                    std::cout << "Welcome, " << account->getName() << "!\n";
                    displayLoggedInMenu();

                    int subChoice;
                    std::cin >> subChoice;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    switch (subChoice) {
                    case 1: //Check balance
                        std::cout << "Current balance: $" << account->getBalance() << "\n";
                        break;
                    case 2: { //Deposit money
                        double amount;
                        std::cout << "Enter amount to deposit: $";
                        std::cin >> amount;
                        account->deposit(amount);
                        std::cout << "Deposit successful!\n";
                        break;
                    }
                    case 3: {
                        //Withdraw money
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
                        //Transfer money
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
                        //Transaction History
                        auto history = bank.getTransactionHistory(accountNumber);
                        std::cout << "\nTransaction History:\n";
                        for (const auto& trans : history) {
                            std::cout << "Date: " << trans.getDate() << std::endl
                                << "Type: " << static_cast<int>(trans.getType())
                                << " Amount: $" << trans.getAmount()
                                << " Description: " << trans.getDescription() << "\n";
                        }
                        break;
                    }
                    case 6:
                        //Logout
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
            //Password reset
            std::string accountNumber, securityAnswer, newPassword;
            std::cout << "Enter account number: ";
            std::getline(std::cin, accountNumber);
            std::cout << "Enter security answer: ";
            std::getline(std::cin, securityAnswer);
            std::cout << "Enter new password: ";
            std::getline(std::cin, newPassword);

            //Attempt password reset
            if (bank.resetPassword(accountNumber, securityAnswer, newPassword)) {
                std::cout << "Password reset successful!\n";
            }
            else {
                std::cout << "Password reset failed. Invalid account number or security answer.\n";
            }
            break;
        }
        case 4: {
            //Chat Assistant
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
        case 5: //Exit application
            std::cout << "Thank you for A-VK banking system!\n";
            return 0;
        }

        if (choice != 5) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }

    return 0;
}