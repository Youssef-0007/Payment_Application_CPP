// server.hpp
#pragma once
#include <vector>
#include "card.hpp"
#include "terminal.hpp"

enum class TransactionState {
    APPROVED,
    DECLINED_INSUFFICIENT_FUND,
    DECLINED_INVALID_ACCOUNT,
    DECLINED_EXPIRED_CARD,
    DECLINED_AMOUNT_LIMIT
};

struct Account {
    std::string primaryAccountNumber;
    std::string holderName;
    double balance;
    bool isActive;
    
    Account(const std::string& pan, const std::string& name, double bal)
        : primaryAccountNumber(pan), holderName(name), balance(bal), isActive(true) {}
};

struct Transaction {
    Card cardData;
    Terminal terminalData;
    TransactionState state;
    double amount;
    std::string transactionSequenceNumber;
};

class Server {
private:
    std::vector<Account> accounts;
    std::vector<Transaction> transactions;
    
    bool isValidAccount(const Card& card);
    bool isAmountAvailable(double amount);
    bool saveTransaction(const Transaction& transaction);

public:
    Server();  // Constructor will initialize the test accounts
    TransactionState receiveTransactionData(Transaction& transaction);
};