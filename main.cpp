#include "Portfolio.h"
#include <iostream>
#include <memory>
#include <limits>
#include <random>
#include <thread>
#include <chrono>
using namespace std;
class StockPortfolioManager {
private:
    Portfolio portfolio;
    std::mt19937 rng;

    // Utility methods
    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    double getRandomPrice(double basePrice, double volatility = 0.1) {
        std::uniform_real_distribution<double> dist(-volatility, volatility);
        double change = basePrice * dist(rng);
        return std::max(0.01, basePrice + change);  // Minimum price of $0.01
    }

    void simulateRealTimeUpdates() {
        std::cout << "\nSimulating real-time price updates...\n";
        for (int i = 0; i < 5; ++i) {
            // Update prices for all stocks in portfolio
            for (size_t j = 0; j < portfolio.getInvestmentCount(); ++j) {
                try {
                    Investment& inv = portfolio[j];
                    if (inv.getStock()) {
                        double currentPrice = inv.getStock()->getCurrentPrice();
                        double newPrice = getRandomPrice(currentPrice, 0.05);
                        inv.getStock()->setCurrentPrice(newPrice);
                    }
                } catch (const std::exception&) {
                    continue;
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Update " << (i + 1) << "/5 completed...\n";
        }
        std::cout << "Real-time updates completed!\n";
    }

public:
    StockPortfolioManager() : portfolio("My Investment Portfolio"), rng(std::random_device{}()) {}

    void displayMenu() {
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "STOCK PORTFOLIO MANAGER\n";
        std::cout << std::string(50, '=') << "\n";
        std::cout << "1.  Add Investment\n";
        std::cout << "2.  Remove Investment\n";
        std::cout << "3.  Update Stock Price\n";
        std::cout << "4.  View Portfolio\n";
        std::cout << "5.  View Portfolio Summary\n";
        std::cout << "6.  View Detailed Report\n";
        std::cout << "7.  Sort Investments by Value\n";
        std::cout << "8.  Sort Investments by Symbol\n";
        std::cout << "9.  View Top Performers\n";
        std::cout << "10. View Losing Investments\n";
        std::cout << "11. Simulate Real-time Updates\n";
        std::cout << "12. Save Portfolio\n";
        std::cout << "13. Load Portfolio\n";
        std::cout << "14. Export to CSV\n";
        std::cout << "15. Load Sample Data\n";
        std::cout << "0.  Exit\n";
        std::cout << std::string(50, '-') << "\n";
        std::cout << "Enter your choice: ";
    }

    void addInvestment() {
        std::string symbol, companyName;
        int shares;
        double purchasePrice, currentPrice;

        std::cout << "\nEnter stock symbol: ";
        std::cin >> symbol;
        clearInputBuffer();

        std::cout << "Enter company name: ";
        std::getline(std::cin, companyName);

        std::cout << "Enter number of shares: ";
        std::cin >> shares;

        std::cout << "Enter purchase price per share: $";
        std::cin >> purchasePrice;

        std::cout << "Enter current price per share: $";
        std::cin >> currentPrice;

        try {
            auto stock = std::make_shared<Stock>(symbol, companyName, currentPrice);
            Investment investment(stock, shares, purchasePrice);

            if (portfolio.addInvestment(investment)) {
                std::cout << "Investment added successfully!\n";
            } else {
                std::cout << "Failed to add investment.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    void removeInvestment() {
        std::string symbol;
        std::cout << "\nEnter stock symbol to remove: ";
        std::cin >> symbol;

        if (portfolio.removeInvestment(symbol)) {
            std::cout << "Investment removed successfully!\n";
        } else {
            std::cout << "Investment not found.\n";
        }
    }

    void updateStockPrice() {
        std::string symbol;
        double newPrice;

        std::cout << "\nEnter stock symbol: ";
        std::cin >> symbol;

        std::cout << "Enter new price: $";
        std::cin >> newPrice;

        if (portfolio.updateStockPrice(symbol, newPrice)) {
            std::cout << "Stock price updated successfully!\n";
        } else {
            std::cout << "Failed to update stock price.\n";
        }
    }

    void sortInvestments() {
        char choice;
        std::cout << "\nSort by value: (a)scending or (d)escending? ";
        std::cin >> choice;

        portfolio.sortInvestmentsByValue(choice == 'a' || choice == 'A');
        std::cout << "Investments sorted by value.\n";
    }

    void viewTopPerformers() {
        size_t count;
        std::cout << "\nEnter number of top performers to display: ";
        std::cin >> count;

        try {
            auto topPerformers = portfolio.getTopPerformers(count);

            std::cout << "\nTop " << topPerformers.size() << " Performers:\n";
            std::cout << std::string(80, '-') << "\n";

            for (const auto& inv : topPerformers) {
                if (inv.getStock()) {
                    std::cout << inv.getStock()->getSymbol() << " ("
                              << inv.getStock()->getCompanyName() << "): "
                              << std::fixed << std::setprecision(2)
                              << inv.getPercentageReturn() << "%\n";
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    void viewLosingInvestments() {
        auto losers = portfolio.getLosers();

        if (losers.empty()) {
            std::cout << "\nNo losing investments found!\n";
        } else {
            std::cout << "\nLosing Investments (" << losers.size() << "):\n";
            std::cout << std::string(80, '-') << "\n";

            for (const auto& inv : losers) {
                if (inv.getStock()) {
                    std::cout << inv.getStock()->getSymbol() << " ("
                              << inv.getStock()->getCompanyName() << "): "
                              << std::fixed << std::setprecision(2)
                              << "$" << inv.getGainLoss() << " ("
                              << inv.getPercentageReturn() << "%)\n";
                }
            }
        }
    }

    void savePortfolio() {
        std::string filename;
        std::cout << "\nEnter filename to save: ";
        std::cin >> filename;

        if (portfolio.saveToFile(filename)) {
            std::cout << "Portfolio saved successfully!\n";
        } else {
            std::cout << "Failed to save portfolio.\n";
        }
    }

    void loadPortfolio() {
        std::string filename;
        std::cout << "\nEnter filename to load: ";
        std::cin >> filename;

        if (portfolio.loadFromFile(filename)) {
            std::cout << "Portfolio loaded successfully!\n";
        } else {
            std::cout << "Failed to load portfolio.\n";
        }
    }

    void exportToCSV() {
        std::string filename;
        std::cout << "\nEnter CSV filename: ";
        std::cin >> filename;

        if (portfolio.exportToCSV(filename)) {
            std::cout << "Portfolio exported to CSV successfully!\n";
        } else {
            std::cout << "Failed to export portfolio.\n";
        }
    }

    void loadSampleData() {
        std::cout << "\nLoading sample portfolio data...\n";

        // Create sample stocks
        auto apple = std::make_shared<Stock>("AAPL", "Apple Inc.", 150.25);
        auto microsoft = std::make_shared<Stock>("MSFT", "Microsoft Corporation", 305.50);
        auto amazon = std::make_shared<Stock>("AMZN", "Amazon.com Inc.", 3100.75);
        auto google = std::make_shared<Stock>("GOOGL", "Alphabet Inc.", 2650.25);
        auto tesla = std::make_shared<Stock>("TSLA", "Tesla Inc.", 800.50);

        // Create sample investments
        Investment inv1(apple, 100, 145.00);
        Investment inv2(microsoft, 50, 280.25);
        Investment inv3(amazon, 10, 3200.00);
        Investment inv4(google, 25, 2500.50);
        Investment inv5(tesla, 30, 750.75);

        // Add to portfolio
        portfolio.addInvestment(inv1);
        portfolio.addInvestment(inv2);
        portfolio.addInvestment(inv3);
        portfolio.addInvestment(inv4);
        portfolio.addInvestment(inv5);

        std::cout << "Sample data loaded successfully!\n";
    }

    void run() {
        int choice;

        std::cout << "Welcome to Stock Portfolio Manager!\n";
        std::cout << "Demonstrating Object-Oriented Programming Principles\n";

        do {
            displayMenu();
            std::cin >> choice;

            switch (choice) {
                case 1: addInvestment(); break;
                case 2: removeInvestment(); break;
                case 3: updateStockPrice(); break;
                case 4: portfolio.displayPortfolio(); break;
                case 5: portfolio.displaySummary(); break;
                case 6: portfolio.displayDetailedReport(); break;
                case 7: sortInvestments(); break;
                case 8: 
                    portfolio.sortInvestmentsBySymbol();
                    std::cout << "Investments sorted by symbol.\n";
                    break;
                case 9: viewTopPerformers(); break;
                case 10: viewLosingInvestments(); break;
                case 11: simulateRealTimeUpdates(); break;
                case 12: savePortfolio(); break;
                case 13: loadPortfolio(); break;
                case 14: exportToCSV(); break;
                case 15: loadSampleData(); break;
                case 0: 
                    std::cout << "\nThank you for using Stock Portfolio Manager!\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
            }

            if (choice != 0) {
                std::cout << "\nPress Enter to continue...";
                clearInputBuffer();
                std::cin.get();
            }

        } while (choice != 0);
    }
};

int main() {
    try {
        StockPortfolioManager manager;
        manager.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}