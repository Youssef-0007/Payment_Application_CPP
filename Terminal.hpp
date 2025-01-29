// terminal.hpp
#pragma once
#include "card.hpp"
#include <string>

class Terminal {
private:
    double maxAmount;
    std::string transactionDate;
    double transactionAmount;

public:
    Terminal() : maxAmount(5000.0), transactionAmount(0.0) {}
    
    bool getTransactionDate();
    bool isCardExpired(const Card& card);
    bool getTransactionAmount();
    bool isBelowMaxAmount();
    void setMaxAmount(double amount);
    
    double getAmount() const { return transactionAmount; }
};