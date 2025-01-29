// card.cpp
#include "card.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>

bool Card::getCardHolderName() {
    std::cout << "Enter card holder name: ";
    std::getline(std::cin, holderName);
    
    // Remove any leading/trailing spaces
    holderName.erase(0, holderName.find_first_not_of(" "));
    holderName.erase(holderName.find_last_not_of(" ") + 1);
    
    // Validate name length (20-24 characters)
    if (holderName.length() < 20 || holderName.length() > 24) {
        return false;
    }
    
    // Validate that name contains only letters and spaces
    return std::all_of(holderName.begin(), holderName.end(), 
                      [](char c) { return std::isalpha(c) || std::isspace(c); });
}

bool Card::getCardExpiryDate() {
    std::cout << "Enter card expiry date (MM/YY): ";
    std::getline(std::cin, expiryDate);
    
    // Validate format
    if (expiryDate.length() != 5 || expiryDate[2] != '/') {
        return false;
    }
    
    // Extract month and year
    std::string monthStr = expiryDate.substr(0, 2);
    std::string yearStr = expiryDate.substr(3, 2);
    
    // Validate numeric values
    if (!std::all_of(monthStr.begin(), monthStr.end(), ::isdigit) ||
        !std::all_of(yearStr.begin(), yearStr.end(), ::isdigit)) {
        return false;
    }
    
    int month = std::stoi(monthStr);
    return month >= 1 && month <= 12;
}

bool Card::getCardPAN() {
    std::cout << "Enter card PAN: ";
    std::getline(std::cin, PAN);
    
    // Remove any spaces
    PAN.erase(std::remove_if(PAN.begin(), PAN.end(), ::isspace), PAN.end());
    
    // Validate length (16-19 digits)
    if (PAN.length() < 16 || PAN.length() > 19) {
        return false;
    }
    
    // Validate all characters are digits
    if (!std::all_of(PAN.begin(), PAN.end(), ::isdigit)) {
        return false;
    }
    
    // Implement Luhn algorithm for PAN validation
    int sum = 0;
    bool alternate = false;
    for (int i = PAN.length() - 1; i >= 0; i--) {
        int n = PAN[i] - '0';
        if (alternate) {
            n *= 2;
            if (n > 9) {
                n = (n % 10) + 1;
            }
        }
        sum += n;
        alternate = !alternate;
    }
    
    return (sum % 10 == 0);
}
