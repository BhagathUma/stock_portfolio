#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "Investment.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <memory>

class Portfolio {
private:
    std::vector<Investment> investments;  // Composition - Portfolio composes Investment objects
    std::string portfolioName;
    double totalInitialInvestment;

    // Private helper methods
    std::vector<Investment>::iterator findInvestment(const std::string& symbol);
    std::vector<Investment>::const_iterator findInvestment(const std::string& symbol) const;

public:
    // Constructors and Destructor
    Portfolio();
    Portfolio(const std::string& name);
    Portfolio(const Portfolio& other);  // Copy constructor
    ~Portfolio();

    // Getters
    std::string getPortfolioName() const;
    size_t getInvestmentCount() const;
    double getTotalInitialInvestment() const;

    // Setters
    void setPortfolioName(const std::string& name);

    // Investment management
    bool addInvestment(const Investment& investment);
    bool removeInvestment(const std::string& symbol);
    bool updateStockPrice(const std::string& symbol, double newPrice);
    Investment* getInvestment(const std::string& symbol);
    const Investment* getInvestment(const std::string& symbol) const;

    // Portfolio calculations
    double getCurrentValue() const;
    double getTotalGainLoss() const;
    double getPercentageReturn() const;

    // STL Algorithm usage
    void sortInvestmentsByValue(bool ascending = false);
    void sortInvestmentsBySymbol();
    Investment getTopPerformer() const;
    Investment getWorstPerformer() const;

    // Portfolio analysis
    std::vector<Investment> getTopPerformers(size_t count) const;
    std::vector<Investment> getLosers() const;
    double getAverageReturn() const;

    // Display methods
    void displayPortfolio() const;
    void displaySummary() const;
    void displayDetailedReport() const;

    // File I/O operations
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    bool exportToCSV(const std::string& filename) const;

    // Operators
    Portfolio& operator=(const Portfolio& other);
    Investment& operator[](size_t index);
    const Investment& operator[](size_t index) const;

    // Iterator support for STL algorithms
    std::vector<Investment>::iterator begin();
    std::vector<Investment>::iterator end();
    std::vector<Investment>::const_iterator begin() const;
    std::vector<Investment>::const_iterator end() const;
};

#endif // PORTFOLIO_H