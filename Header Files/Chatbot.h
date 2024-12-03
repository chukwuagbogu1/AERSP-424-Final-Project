#ifndef CHATBOT_H
#define CHATBOT_H

#include <string>
#include <map>

class Chatbot {
private:
    std::map<std::string, std::string> responses;

public:
    Chatbot();
    std::string getResponse(const std::string& query);
    void loadResponses();
};

#endif
