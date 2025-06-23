#include "Stock.h"
#include <iomanip>
#include <stdexcept>
#include <thread>

// Default constructor
Stock::Stock() : symbol(""), companyName(""), currentPrice(0.0), previousPrice(0.0) {}

// Parameterized constructor
Stock::Stock(const std::string& symbol, const std::string& companyName, double currentPrice)
    : symbol(symbol), companyName(companyName), currentPrice(currentPrice), previousPrice(currentPrice) {
    if (currentPrice < 0) {
        throw std::invalid_argument("Stock price cannot be negative");
    }
}

// Copy constructor
Stock::Stock(const Stock& other)
    : symbol(other.symbol), companyName(other.companyName), 
      currentPrice(other.currentPrice), previousPrice(other.previousPrice) {}

// Destructor
Stock::~Stock() {
    // Nothing to clean up for primitive types and std::string
}

// Getters
std::string Stock::getSymbol() const {
    return symbol;
}

std::string Stock::getCompanyName() const {
    return companyName;
}

double Stock::getCurrentPrice() const {
    return currentPrice;
}

double Stock::getPreviousPrice() const {
    return previousPrice;
}

// Setters
void Stock::setCurrentPrice(double price) {
    if (price < 0) {
        throw std::invalid_argument("Stock price cannot be negative");
    }
    previousPrice = currentPrice;
    currentPrice = price;
}

void Stock::setPreviousPrice(double price) {
    if (price < 0) {
        throw std::invalid_argument("Stock price cannot be negative");
    }
    previousPrice = price;
}

void Stock::setCompanyName(const std::string& name) {
    companyName = name;
}

// Utility methods
double Stock::getPriceChange() const {
    return currentPrice - previousPrice;
}

double Stock::getPercentageChange() const {
    if (previousPrice == 0.0) {
        return 0.0;
    }
    return ((currentPrice - previousPrice) / previousPrice) * 100.0;
}

// Assignment operator
Stock& Stock::operator=(const Stock& other) {
    if (this != &other) {
        symbol = other.symbol;
        companyName = other.companyName;
        currentPrice = other.currentPrice;
        previousPrice = other.previousPrice;
    }
    return *this;
}

// Equality operator
bool Stock::operator==(const Stock& other) const {
    return symbol == other.symbol;
}

// Display methods
void Stock::displayInfo() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Symbol: " << symbol << "\n";
    std::cout << "Company: " << companyName << "\n";
    std::cout << "Current Price: $" << currentPrice << "\n";
    std::cout << "Previous Price: $" << previousPrice << "\n";
    std::cout << "Price Change: $" << getPriceChange() << " (" 
              << getPercentageChange() << "%)\n";
}

// Stream output operator
std::ostream& operator<<(std::ostream& os, const Stock& stock) {
    os << stock.symbol << "," << stock.companyName << "," 
       << stock.currentPrice << "," << stock.previousPrice;
    return os;
}