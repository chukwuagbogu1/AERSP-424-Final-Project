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
        {"balance", "To check your balance, select option 2 from the main menu."},
        {"transfer", "To transfer money, select option 4 from the main menu."},
        {"deposit", "To deposit money, select option 3 from the main menu."},
        {"withdraw", "To withdraw money, select option 3 from the main menu."},
        {"help", "Available commands: balance, transfer, deposit, withdraw"}
    };
}