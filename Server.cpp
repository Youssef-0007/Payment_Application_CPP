// server.cpp
#include "server.hpp"
#include <algorithm>
#include <random>

Server::Server() {
    // Initialize test accounts
    accounts = {
        Account("4532789612345678", "John Doe Smith Johnson", 10000.0),
        Account("5489789612345678", "Jane Marie Smith Davis", 20000.0),
        Account("6011789612345678", "Robert James Williams", 15000.0)
    };
}

TransactionState Server::receiveTransactionData(Transaction& transaction) {
    // Validate card
    if (!isValidAccount(transaction.cardData)) {
        transaction.state = TransactionState::DECLINED_INVALID_ACCOUNT;
        return TransactionState::DECLINED_INVALID_ACCOUNT;
    }
    
    // Check if amount is available
    if (!isAmountAvailable(transaction.terminalData.getAmount())) {
        transaction.state = TransactionState::DECLINED_INSUFFICIENT_FUND;
        return TransactionState::DECLINED_INSUFFICIENT_FUND;
    }
    
    // Generate transaction sequence number
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    transaction.transactionSequenceNumber = std::to_string(dis(gen));
    
    // Save transaction
    if (!saveTransaction(transaction)) {
        transaction.state = TransactionState::DECLINED_INVALID_ACCOUNT;
        return TransactionState::DECLINED_INVALID_ACCOUNT;
    }
    
    // Update account balance
    auto it = std::find_if(accounts.begin(), accounts.end(),
        [&](const Account& acc) { return acc.primaryAccountNumber == transaction.cardData.getPAN(); });
    
    if (it != accounts.end()) {
        it->balance -= transaction.amount;
    }
    
    transaction.state = TransactionState::APPROVED;
    return TransactionState::APPROVED;
}

bool Server::isValidAccount(const Card& card) {
    return std::any_of(accounts.begin(), accounts.end(),
        [&](const Account& acc) { return acc.primaryAccountNumber == card.getPAN() && acc.isActive; });
}

bool Server::isAmountAvailable(double amount) {
    auto it = std::find_if(accounts.begin(), accounts.end(),
        [&](const Account& acc) { return acc.balance >= amount; });
    return it != accounts.end();
}

bool Server::saveTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
    return true;
}