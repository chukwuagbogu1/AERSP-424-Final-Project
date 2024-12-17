#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <map>
#include "UserAccount.h"
#include "Transaction.h"
//Class to handle file data persistence
class FileHandler {
public:
    static void saveAccount(const UserAccount& account); //save all user accounts to file
    static void saveTransaction(const Transaction& transaction); //save all transactions to file 
    static void loadAccounts(std::map<std::string, UserAccount>& accounts); //load all accounts from storage
    static void loadTransactions(std::vector<Transaction>& transactions); //load alll transactions from storgae
};

#endif