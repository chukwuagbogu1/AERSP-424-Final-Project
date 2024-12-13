#include "Chatbot.h"
#include <fstream>
#include <algorithm>
Chatbot::Chatbot() {
    loadResponses();
}
std::string Chatbot::getResponse(const std::string& query) {
    // Convert query to lowercase for case-insensitive matching
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
    
    auto it = responses.find(lowerQuery);
    if (it != responses.end()) {
        return it->second;
    }
    return "I'm sorry, I don't understand that question. Please try asking something else.";
}
void Chatbot::loadResponses() {
    responses = {
        {"balance", "To check your balance, Log in from the home menu and then option 1 from the account menu."},
        {"transfer", "To transfer money, Log in from the home menu and then option 4 from the account menu."},
        {"deposit", "To deposit money,  Log in from the home menu and then option 2 from the account menu."},
        {"withdraw", "To withdraw money,  Log in from the home menu and then option 3 from the account menu."},
        {"help", "Available commands: balance, transfer, deposit, withdraw"},
        {"pay", "Sorry this feature is unavailable and is in development." },
        {"history", "To view your transaction history, select option 2 from the home menu and then option 5 from the account menu." },
        {"create", "To create an account, select option 1 from the home menu." },
        {"security", "Secure?? What's that?" },
        {"fees", "A LOT!You don't even know what is going on! HAHA." },
        {"Issues", "If you're encountering issues with the app, delete the computer." },
        {"reset", "To reset your password, select option 3 from the home menu." },
        {"notifications", "Why??? We won't disturb you I swear. Don't think of doing it." },
        {"contact", "For additional assistance:\n- Use the chat assistant\n- Contact your local branch\n- Email: support@bank-o-matic.com"},
        {"hours", "Our online banking system is available 24/7. You can perform transactions at any time."},
        {"minimum", "There is no minimum balance requirement for basic accounts."},
        { "password", "If you've forgotten your password:\n1. Select option 3 from the main menu\n2. Enter your account number\n3. Answer your security question\n4. Set your new password" },
        {"security", "We take security seriously:\n- All passwords are securely stored\n- Security questions are required for password resets\n- Regular security audits are performed"},
    };
}

