#ifndef INVESTMENT_H
#define INVESTMENT_H

#include "Stock.h"
#include <memory>

class Investment {
private:
    std::shared_ptr<Stock> stock;  // Aggregation - Investment aggregates Stock
    int sharesOwned;
    double purchasePrice;
    double totalInvested;

public:
    // Constructors and Destructor
    Investment();
    Investment(std::shared_ptr<Stock> stock, int shares, double purchasePrice);
    Investment(const Investment& other);  // Copy constructor
    ~Investment();

    // Getters
    std::shared_ptr<Stock> getStock() const;
    int getSharesOwned() const;
    double getPurchasePrice() const;
    double getTotalInvested() const;

    // Setters
    void setSharesOwned(int shares);
    void addShares(int shares, double pricePerShare);
    void removeShares(int shares);

    // Financial calculations
    double getCurrentValue() const;
    double getGainLoss() const;
    double getPercentageReturn() const;

    // Operators
    Investment& operator=(const Investment& other);
    bool operator<(const Investment& other) const;  // For sorting by value

    // Display methods
    void displayInvestment() const;
    friend std::ostream& operator<<(std::ostream& os, const Investment& investment);
};

#endif // INVESTMENT_H