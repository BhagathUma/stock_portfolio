#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <iostream>

class Stock {
private:
    std::string symbol;
    std::string companyName;
    double currentPrice;
    double previousPrice;

public:
    // Constructors and Destructor
    Stock();
    Stock(const std::string& symbol, const std::string& companyName, double currentPrice);
    Stock(const Stock& other);  // Copy constructor
    ~Stock();

    // Getters (const methods for encapsulation)
    std::string getSymbol() const;
    std::string getCompanyName() const;
    double getCurrentPrice() const;
    double getPreviousPrice() const;

    // Setters
    void setCurrentPrice(double price);
    void setPreviousPrice(double price);
    void setCompanyName(const std::string& name);

    // Utility methods
    double getPriceChange() const;
    double getPercentageChange() const;

    // Operators
    Stock& operator=(const Stock& other);
    bool operator==(const Stock& other) const;

    // I/O operations
    void displayInfo() const;
    friend std::ostream& operator<<(std::ostream& os, const Stock& stock);
};

#endif // STOCK_H