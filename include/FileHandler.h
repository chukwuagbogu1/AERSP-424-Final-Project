#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <map>
#include "UserAccount.h"
#include "Transaction.h"

class FileHandler {
public:
    static void saveAccount(const UserAccount& account);
    static void saveTransaction(const Transaction& transaction);
    static void loadAccounts(std::map<std::string, UserAccount>& accounts);
    static void loadTransactions(std::vector<Transaction>& transactions);
};

#endif