# Stock Portfolio Manager

A comprehensive console-based Stock Portfolio Manager application implemented in C++ demonstrating core Object-Oriented Programming (OOP) principles.

## Features

### Core Functionality
- **Investment Tracking**: Add, remove, and manage stock investments
- **Real-time Calculations**: Calculate gains/losses, current values, and percentage returns
- **Portfolio Analysis**: View performance metrics, top performers, and losing investments
- **Data Persistence**: Save/load portfolio data and export to CSV format
- **Real-time Simulation**: Simulate stock price fluctuations

## Building and Running

### Prerequisites
- C++17 compatible compiler (GCC 7+ or Clang 5+)
- Make utility (optional)

### Build Instructions

#### Using Makefile (Recommended)
```bash
# Build the project
make

# Build with debug information
make debug

# Build and run
make run

# Clean build files
make clean
```

#### Manual Compilation
```bash
g++ -std=c++17 -Wall -Wextra -O2 Stock.cpp Investment.cpp Portfolio.cpp main.cpp -o portfolio_manager
```

### Running the Application
```bash
./portfolio_manager
```

## Usage Guide

### Main Menu Options
1. **Add Investment**: Create new investment positions
2. **Remove Investment**: Remove existing investments
3. **Update Stock Price**: Modify current stock prices
4. **View Portfolio**: Display all investments in tabular format
5. **View Summary**: Show portfolio overview with key metrics
6. **Detailed Report**: Comprehensive analysis with performance data
7. **Sort by Value**: Order investments by current value
8. **Sort by Symbol**: Alphabetical ordering by stock symbol
9. **Top Performers**: Display best performing investments
10. **Losing Investments**: Show investments with negative returns
11. **Real-time Simulation**: Simulate price fluctuations
12. **Save Portfolio**: Persist data to file
13. **Load Portfolio**: Restore saved portfolio
14. **Export CSV**: Export data for external analysis
15. **Load Sample Data**: Load demonstration data

