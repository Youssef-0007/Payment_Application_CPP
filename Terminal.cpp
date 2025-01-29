// terminal.cpp
#include "terminal.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

bool Terminal::getTransactionDate() {
    // Get current date
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    // Format date as DD/MM/YYYY
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << ltm->tm_mday << "/"
       << std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon) << "/"
       << (1900 + ltm->tm_year);
    
    transactionDate = ss.str();
    return true;
}

bool Terminal::isCardExpired(const Card& card) {
    // Get card expiry date
    std::string cardExpiry = card.getExpiryDate(); // Format: MM/YY
    
    // Get current date
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentMonth = 1 + ltm->tm_mon;
    int currentYear = (1900 + ltm->tm_year) % 100;
    
    // Parse card expiry
    int cardMonth = std::stoi(cardExpiry.substr(0, 2));
    int cardYear = std::stoi(cardExpiry.substr(3, 2));
    
    // Compare dates
    if (cardYear < currentYear) return true;
    if (cardYear == currentYear && cardMonth < currentMonth) return true;
    
    return false;
}

bool Terminal::getTransactionAmount() {
    std::cout << "Enter transaction amount: ";
    std::cin >> transactionAmount;
    
    // Clear input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return transactionAmount > 0;
}

bool Terminal::isBelowMaxAmount() {
    return transactionAmount <= maxAmount;
}

void Terminal::setMaxAmount(double amount) {
    if (amount > 0) {
        maxAmount = amount;
    }
}