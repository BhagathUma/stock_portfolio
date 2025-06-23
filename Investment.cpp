#include "Investment.h"
#include <iomanip>
#include <thread>

#include <stdexcept>

// Default constructor
Investment::Investment() : stock(nullptr), sharesOwned(0), purchasePrice(0.0), totalInvested(0.0) {}

// Parameterized constructor
Investment::Investment(std::shared_ptr<Stock> stock, int shares, double purchasePrice)
    : stock(stock), sharesOwned(shares), purchasePrice(purchasePrice) {
    if (!stock) {
        throw std::invalid_argument("Stock pointer cannot be null");
    }
    if (shares < 0) {
        throw std::invalid_argument("Number of shares cannot be negative");
    }
    if (purchasePrice < 0) {
        throw std::invalid_argument("Purchase price cannot be negative");
    }
    totalInvested = shares * purchasePrice;
}

// Copy constructor
Investment::Investment(const Investment& other)
    : stock(other.stock), sharesOwned(other.sharesOwned), 
      purchasePrice(other.purchasePrice), totalInvested(other.totalInvested) {}

// Destructor
Investment::~Investment() {
    // shared_ptr automatically handles cleanup
}

// Getters
std::shared_ptr<Stock> Investment::getStock() const {
    return stock;
}

int Investment::getSharesOwned() const {
    return sharesOwned;
}

double Investment::getPurchasePrice() const {
    return purchasePrice;
}

double Investment::getTotalInvested() const {
    return totalInvested;
}

// Setters
void Investment::setSharesOwned(int shares) {
    if (shares < 0) {
        throw std::invalid_argument("Number of shares cannot be negative");
    }
    sharesOwned = shares;
}

void Investment::addShares(int shares, double pricePerShare) {
    if (shares <= 0) {
        throw std::invalid_argument("Number of shares to add must be positive");
    }
    if (pricePerShare < 0) {
        throw std::invalid_argument("Price per share cannot be negative");
    }

    // Calculate weighted average purchase price
    double newInvestment = shares * pricePerShare;
    double newTotalShares = sharesOwned + shares;

    if (newTotalShares > 0) {
        purchasePrice = (totalInvested + newInvestment) / newTotalShares;
    }

    sharesOwned += shares;
    totalInvested += newInvestment;
}

void Investment::removeShares(int shares) {
    if (shares <= 0) {
        throw std::invalid_argument("Number of shares to remove must be positive");
    }
    if (shares > sharesOwned) {
        throw std::invalid_argument("Cannot remove more shares than owned");
    }

    double proportionRemoved = static_cast<double>(shares) / sharesOwned;
    totalInvested *= (1.0 - proportionRemoved);
    sharesOwned -= shares;
}

// Financial calculations
double Investment::getCurrentValue() const {
    if (!stock) {
        return 0.0;
    }
    return sharesOwned * stock->getCurrentPrice();
}

double Investment::getGainLoss() const {
    return getCurrentValue() - totalInvested;
}

double Investment::getPercentageReturn() const {
    if (totalInvested == 0.0) {
        return 0.0;
    }
    return (getGainLoss() / totalInvested) * 100.0;
}

// Assignment operator
Investment& Investment::operator=(const Investment& other) {
    if (this != &other) {
        stock = other.stock;
        sharesOwned = other.sharesOwned;
        purchasePrice = other.purchasePrice;
        totalInvested = other.totalInvested;
    }
    return *this;
}

// Less than operator for sorting
bool Investment::operator<(const Investment& other) const {
    return getCurrentValue() < other.getCurrentValue();
}

// Display method
void Investment::displayInvestment() const {
    if (!stock) {
        std::cout << "Invalid investment (no stock data)\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Symbol: " << stock->getSymbol() << "\n";
    std::cout << "Company: " << stock->getCompanyName() << "\n";
    std::cout << "Shares Owned: " << sharesOwned << "\n";
    std::cout << "Purchase Price: $" << purchasePrice << "\n";
    std::cout << "Current Price: $" << stock->getCurrentPrice() << "\n";
    std::cout << "Total Invested: $" << totalInvested << "\n";
    std::cout << "Current Value: $" << getCurrentValue() << "\n";
    std::cout << "Gain/Loss: $" << getGainLoss() << " (" 
              << getPercentageReturn() << "%)\n";
}

// Stream output operator
std::ostream& operator<<(std::ostream& os, const Investment& investment) {
    if (investment.stock) {
        os << investment.stock->getSymbol() << "," 
           << investment.sharesOwned << "," 
           << investment.purchasePrice << "," 
           << investment.totalInvested;
    }
    return os;
}