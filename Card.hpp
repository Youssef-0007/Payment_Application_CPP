// card.hpp
#pragma once
#include <string>

class Card {
private:
    std::string holderName;
    std::string expiryDate;
    std::string PAN;

public:
    bool getCardHolderName();
    bool getCardExpiryDate();
    bool getCardPAN();
    
    // Getters for validation
    const std::string& getHolderName() const { return holderName; }
    const std::string& getExpiryDate() const { return expiryDate; }
    const std::string& getPAN() const { return PAN; }
};
