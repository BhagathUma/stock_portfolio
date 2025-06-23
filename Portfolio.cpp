#include "Portfolio.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <thread>
#include <numeric>
#include <algorithm>
#include <stdexcept>

// Default constructor
Portfolio::Portfolio() : portfolioName("My Portfolio"), totalInitialInvestment(0.0) {}

// Parameterized constructor
Portfolio::Portfolio(const std::string& name) : portfolioName(name), totalInitialInvestment(0.0) {}

// Copy constructor
Portfolio::Portfolio(const Portfolio& other)
    : investments(other.investments), portfolioName(other.portfolioName), 
      totalInitialInvestment(other.totalInitialInvestment) {}

// Destructor
Portfolio::~Portfolio() {
    // STL containers automatically handle cleanup
}

// Private helper methods
std::vector<Investment>::iterator Portfolio::findInvestment(const std::string& symbol) {
    return std::find_if(investments.begin(), investments.end(),
        [&symbol](const Investment& inv) {
            return inv.getStock() && inv.getStock()->getSymbol() == symbol;
        });
}

std::vector<Investment>::const_iterator Portfolio::findInvestment(const std::string& symbol) const {
    return std::find_if(investments.begin(), investments.end(),
        [&symbol](const Investment& inv) {
            return inv.getStock() && inv.getStock()->getSymbol() == symbol;
        });
}

// Getters
std::string Portfolio::getPortfolioName() const {
    return portfolioName;
}

size_t Portfolio::getInvestmentCount() const {
    return investments.size();
}

double Portfolio::getTotalInitialInvestment() const {
    return totalInitialInvestment;
}

// Setters
void Portfolio::setPortfolioName(const std::string& name) {
    portfolioName = name;
}

// Investment management
bool Portfolio::addInvestment(const Investment& investment) {
    if (!investment.getStock()) {
        return false;
    }

    // Check if investment already exists
    auto it = findInvestment(investment.getStock()->getSymbol());
    if (it != investments.end()) {
        // Merge with existing investment
        try {
            it->addShares(investment.getSharesOwned(), investment.getPurchasePrice());
            totalInitialInvestment += investment.getTotalInvested();
            return true;
        } catch (const std::exception&) {
            return false;
        }
    } else {
        // Add new investment
        investments.push_back(investment);
        totalInitialInvestment += investment.getTotalInvested();
        return true;
    }
}

bool Portfolio::removeInvestment(const std::string& symbol) {
    auto it = findInvestment(symbol);
    if (it != investments.end()) {
        totalInitialInvestment -= it->getTotalInvested();
        investments.erase(it);
        return true;
    }
    return false;
}

bool Portfolio::updateStockPrice(const std::string& symbol, double newPrice) {
    auto it = findInvestment(symbol);
    if (it != investments.end() && it->getStock()) {
        try {
            it->getStock()->setCurrentPrice(newPrice);
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }
    return false;
}

Investment* Portfolio::getInvestment(const std::string& symbol) {
    auto it = findInvestment(symbol);
    return (it != investments.end()) ? &(*it) : nullptr;
}

const Investment* Portfolio::getInvestment(const std::string& symbol) const {
    auto it = findInvestment(symbol);
    return (it != investments.end()) ? &(*it) : nullptr;
}
// Portfolio calculations
double Portfolio::getCurrentValue() const {
    return std::accumulate(investments.begin(), investments.end(), 0.0,
        [](double sum, const Investment& inv) {
            return sum + inv.getCurrentValue();
        });
}

double Portfolio::getTotalGainLoss() const {
    return getCurrentValue() - totalInitialInvestment;
}

double Portfolio::getPercentageReturn() const {
    if (totalInitialInvestment == 0.0) {
        return 0.0;
    }
    return (getTotalGainLoss() / totalInitialInvestment) * 100.0;
}

// STL Algorithm usage
void Portfolio::sortInvestmentsByValue(bool ascending) {
    if (ascending) {
        std::sort(investments.begin(), investments.end(),
            [](const Investment& a, const Investment& b) {
                return a.getCurrentValue() < b.getCurrentValue();
            });
    } else {
        std::sort(investments.begin(), investments.end(),
            [](const Investment& a, const Investment& b) {
                return a.getCurrentValue() > b.getCurrentValue();
            });
    }
}

void Portfolio::sortInvestmentsBySymbol() {
    std::sort(investments.begin(), investments.end(),
        [](const Investment& a, const Investment& b) {
            return a.getStock()->getSymbol() < b.getStock()->getSymbol();
        });
}

Investment Portfolio::getTopPerformer() const {
    if (investments.empty()) {
        throw std::runtime_error("Portfolio is empty");
    }

    auto it = std::max_element(investments.begin(), investments.end(),
        [](const Investment& a, const Investment& b) {
            return a.getPercentageReturn() < b.getPercentageReturn();
        });
    return *it;
}

Investment Portfolio::getWorstPerformer() const {
    if (investments.empty()) {
        throw std::runtime_error("Portfolio is empty");
    }

    auto it = std::min_element(investments.begin(), investments.end(),
        [](const Investment& a, const Investment& b) {
            return a.getPercentageReturn() < b.getPercentageReturn();
        });
    return *it;
}

// Portfolio analysis
std::vector<Investment> Portfolio::getTopPerformers(size_t count) const {
    std::vector<Investment> sorted_investments = investments;

    std::sort(sorted_investments.begin(), sorted_investments.end(),
        [](const Investment& a, const Investment& b) {
            return a.getPercentageReturn() > b.getPercentageReturn();
        });

    size_t actual_count = std::min(count, sorted_investments.size());
    return std::vector<Investment>(sorted_investments.begin(), 
                                   sorted_investments.begin() + actual_count);
}

std::vector<Investment> Portfolio::getLosers() const {
    std::vector<Investment> losers;

    std::copy_if(investments.begin(), investments.end(), 
                 std::back_inserter(losers),
        [](const Investment& inv) {
            return inv.getGainLoss() < 0;
        });

    return losers;
}

double Portfolio::getAverageReturn() const {
    if (investments.empty()) {
        return 0.0;
    }

    double total_return = std::accumulate(investments.begin(), investments.end(), 0.0,
        [](double sum, const Investment& inv) {
            return sum + inv.getPercentageReturn();
        });

    return total_return / investments.size();
}
// Display methods
void Portfolio::displayPortfolio() const {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "PORTFOLIO: " << portfolioName << "\n";
    std::cout << std::string(60, '=') << "\n";

    if (investments.empty()) {
        std::cout << "No investments in portfolio.\n";
        return;
    }

    std::cout << std::left << std::setw(8) << "Symbol"
              << std::setw(25) << "Company"
              << std::setw(8) << "Shares"
              << std::setw(12) << "Avg Cost"
              << std::setw(12) << "Curr Price"
              << std::setw(12) << "Value"
              << std::setw(12) << "Gain/Loss"
              << "Return%" << "\n";
    std::cout << std::string(100, '-') << "\n";

    std::cout << std::fixed << std::setprecision(2);
    for (const auto& investment : investments) {
        if (investment.getStock()) {
            std::cout << std::left << std::setw(8) << investment.getStock()->getSymbol()
                      << std::setw(25) << investment.getStock()->getCompanyName().substr(0, 24)
                      << std::setw(8) << investment.getSharesOwned()
                      << "$" << std::setw(11) << investment.getPurchasePrice()
                      << "$" << std::setw(11) << investment.getStock()->getCurrentPrice()
                      << "$" << std::setw(11) << investment.getCurrentValue()
                      << "$" << std::setw(11) << investment.getGainLoss()
                      << investment.getPercentageReturn() << "%\n";
        }
    }
}

void Portfolio::displaySummary() const {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "PORTFOLIO SUMMARY: " << portfolioName << "\n";
    std::cout << std::string(50, '=') << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Investments: " << investments.size() << "\n";
    std::cout << "Total Invested: $" << totalInitialInvestment << "\n";
    std::cout << "Current Value: $" << getCurrentValue() << "\n";
    std::cout << "Total Gain/Loss: $" << getTotalGainLoss() << "\n";
    std::cout << "Portfolio Return: " << getPercentageReturn() << "%\n";
    std::cout << "Average Return: " << getAverageReturn() << "%\n";
}

void Portfolio::displayDetailedReport() const {
    displaySummary();
    displayPortfolio();

    if (!investments.empty()) {
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "PERFORMANCE ANALYSIS\n";
        std::cout << std::string(50, '=') << "\n";

        try {
            Investment top = getTopPerformer();
            Investment worst = getWorstPerformer();

            std::cout << "Top Performer: " << top.getStock()->getSymbol() 
                      << " (" << std::fixed << std::setprecision(2) 
                      << top.getPercentageReturn() << "%)\n";
            std::cout << "Worst Performer: " << worst.getStock()->getSymbol() 
                      << " (" << worst.getPercentageReturn() << "%)\n";

            auto losers = getLosers();
            std::cout << "Losing Investments: " << losers.size() << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error in analysis: " << e.what() << "\n";
        }
    }
}

// File I/O operations
bool Portfolio::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << portfolioName << "\n";
    file << totalInitialInvestment << "\n";
    file << investments.size() << "\n";

    for (const auto& investment : investments) {
        if (investment.getStock()) {
            file << investment.getStock()->getSymbol() << ","
                 << investment.getStock()->getCompanyName() << ","
                 << investment.getStock()->getCurrentPrice() << ","
                 << investment.getStock()->getPreviousPrice() << ","
                 << investment.getSharesOwned() << ","
                 << investment.getPurchasePrice() << ","
                 << investment.getTotalInvested() << "\n";
        }
    }

    file.close();
    return true;
}

bool Portfolio::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    investments.clear();

    std::string line;
    if (!std::getline(file, portfolioName)) {
        return false;
    }

    if (!std::getline(file, line)) {
        return false;
    }
    totalInitialInvestment = std::stod(line);

    if (!std::getline(file, line)) {
        return false;
    }
    size_t count = std::stoul(line);

    for (size_t i = 0; i < count; ++i) {
        if (!std::getline(file, line)) {
            return false;
        }

        std::stringstream ss(line);
        std::string symbol, companyName, currentPriceStr, previousPriceStr;
        std::string sharesStr, purchasePriceStr, totalInvestedStr;

        if (std::getline(ss, symbol, ',') &&
            std::getline(ss, companyName, ',') &&
            std::getline(ss, currentPriceStr, ',') &&
            std::getline(ss, previousPriceStr, ',') &&
            std::getline(ss, sharesStr, ',') &&
            std::getline(ss, purchasePriceStr, ',') &&
            std::getline(ss, totalInvestedStr)) {

            try {
                double currentPrice = std::stod(currentPriceStr);
                double previousPrice = std::stod(previousPriceStr);
                int shares = std::stoi(sharesStr);
                double purchasePrice = std::stod(purchasePriceStr);

                auto stock = std::make_shared<Stock>(symbol, companyName, currentPrice);
                stock->setPreviousPrice(previousPrice);

                Investment investment(stock, shares, purchasePrice);
                investments.push_back(investment);
            } catch (const std::exception&) {
                continue; // Skip invalid entries
            }
        }
    }

    file.close();
    return true;
}

bool Portfolio::exportToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << "Symbol,Company,Shares,Purchase Price,Current Price,Current Value,Gain/Loss,Return %\n";

    for (const auto& investment : investments) {
        if (investment.getStock()) {
            file << investment.getStock()->getSymbol() << ","
                 << investment.getStock()->getCompanyName() << ","
                 << investment.getSharesOwned() << ","
                 << std::fixed << std::setprecision(2) << investment.getPurchasePrice() << ","
                 << investment.getStock()->getCurrentPrice() << ","
                 << investment.getCurrentValue() << ","
                 << investment.getGainLoss() << ","
                 << investment.getPercentageReturn() << "\n";
        }
    }

    file.close();
    return true;
}

// Operators
Portfolio& Portfolio::operator=(const Portfolio& other) {
    if (this != &other) {
        investments = other.investments;
        portfolioName = other.portfolioName;
        totalInitialInvestment = other.totalInitialInvestment;
    }
    return *this;
}

Investment& Portfolio::operator[](size_t index) {
    if (index >= investments.size()) {
        throw std::out_of_range("Index out of range");
    }
    return investments[index];
}

const Investment& Portfolio::operator[](size_t index) const {
    if (index >= investments.size()) {
        throw std::out_of_range("Index out of range");
    }
    return investments[index];
}

// Iterator support
std::vector<Investment>::iterator Portfolio::begin() {
    return investments.begin();
}

std::vector<Investment>::iterator Portfolio::end() {
    return investments.end();
}

std::vector<Investment>::const_iterator Portfolio::begin() const {
    return investments.begin();
}

std::vector<Investment>::const_iterator Portfolio::end() const {
    return investments.end();
}