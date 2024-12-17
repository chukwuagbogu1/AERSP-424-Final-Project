#ifndef CHATBOT_H
#define CHATBOT_H

#include <string>
#include <map>
//Simple chatbot for handling user queries
class Chatbot {
private:
    //Map of questions to answers
    std::map<std::string, std::string> responses;

public:
    Chatbot(); //Initialize chatbot
    std::string getResponse(const std::string& query); //Get response for user query
    void loadResponses(); //load predefined responses.
};

#endif
