// application.cpp
#include "application.hpp"
#include <iostream>

void Application::appStart() {
    Card card;
    Terminal terminal;
    Transaction transaction;
    
    std::cout << "=== Payment System ===\n\n";
    
    // Get card data
    if (!card.getCardHolderName()) {
        std::cout << "Invalid card holder name!\n";
        return;
    }
    
    if (!card.getCardExpiryDate()) {
        std::cout << "Invalid card expiry date!\n";
        return;
    }
    
    if (!card.getCardPAN()) {
        std::cout << "Invalid card PAN!\n";
        return;
    }
    
    // Get terminal data
    terminal.getTransactionDate();
    
    if (terminal.isCardExpired(card)) {
        std::cout << "Card is expired!\n";
        return;
    }
    
    if (!terminal.getTransactionAmount()) {
        std::cout << "Invalid amount!\n";
        return;
    }
    
    if (!terminal.isBelowMaxAmount()) {
        std::cout << "Amount exceeds maximum limit!\n";
        return;
    }
    
    // Prepare transaction
    transaction.cardData = card;
    transaction.terminalData = terminal;
    transaction.amount = terminal.getAmount();
    
    // Process transaction
    TransactionState result = server.receiveTransactionData(transaction);
    
    // Display result
    switch (result) {
        case TransactionState::APPROVED:
            std::cout << "Transaction approved!\n";
            break;
        case TransactionState::DECLINED_INSUFFICIENT_FUND:
            std::cout << "Transaction declined: Insufficient funds\n";
            break;
        case TransactionState::DECLINED_INVALID_ACCOUNT:
            std::cout << "Transaction declined: Invalid account\n";
            break;
        case TransactionState::DECLINED_EXPIRED_CARD:
            std::cout << "Transaction declined: Expired card\n";
            break;
        case TransactionState::DECLINED_AMOUNT_LIMIT:
            std::cout << "Transaction declined: Amount limit exceeded\n";
            break;
    }
}