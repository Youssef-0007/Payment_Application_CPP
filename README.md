# Payment Processing System

## Project Description
This is a C++ implementation of a payment processing system that simulates card transactions between a card holder, terminal (ATM), and server. The system currently implements the SALE transaction type, with infrastructure prepared for future implementation of REFUND, Pre-Authorization, and VOID transactions.

## System Architecture

### Components
1. **Card Module**: Handles card-related operations and data
2. **Terminal Module**: Manages transaction input and preliminary validation
3. **Server Module**: Processes transactions and maintains the account database
4. **Application Module**: Orchestrates the interaction between all components

### Workflow
1. Card information is collected (holder name, expiry date, PAN)
2. Terminal validates card expiry and collects transaction amount
3. Server validates the account and processes the transaction
4. Transaction result is returned to the terminal

## Object-Oriented Design Principles Used

### 1. Encapsulation
- All modules encapsulate their data and expose only necessary interfaces
- Private member variables with public methods for controlled access
- Clear separation between internal implementation and public interface

### 2. Single Responsibility Principle
- Each class has a single, well-defined responsibility:
  - Card: Manages card data
  - Terminal: Handles transaction input and validation
  - Server: Processes transactions and manages accounts
  - Application: Controls program flow

### 3. Design Patterns

#### Factory Method Pattern
- Used in transaction creation to ensure proper initialization and validation

#### State Pattern
- Transaction states are managed using an enumeration (TransactionState)
- Allows for clear state transitions and error handling

#### Repository Pattern
- Server class implements a repository pattern for account and transaction storage

## Technical Implementation

### Data Structures
- Vector containers for account and transaction storage
- Custom structures for Account and Transaction data
- String handling for card and account information

### Validation
- Multiple validation layers:
  1. Card level (format validation)
  2. Terminal level (expiry and amount validation)
  3. Server level (account and balance validation)

### Error Handling
- Robust error checking at each step
- Clear error states and messages
- Transaction rollback capability

## Testing Scenarios
1. Successful transaction
2. Maximum amount exceeded
3. Insufficient funds
4. Expired card
5. Invalid card number

## Future Enhancements
1. Implementation of additional transaction types (REFUND, Pre-Authorization, VOID)
2. Database integration for persistent storage
3. Enhanced security features
4. Transaction logging and reporting
5. User interface improvements

## Building and Running
```bash
# Compile the project
g++ -std=c++17 main.cpp card.cpp terminal.cpp server.cpp application.cpp -o payment_system

# Run the application
./payment_system
```
