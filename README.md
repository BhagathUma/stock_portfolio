# Stock Portfolio Manager

A comprehensive console-based Stock Portfolio Manager application implemented in C++ demonstrating core Object-Oriented Programming (OOP) principles.

## Features

### Core Functionality
- **Investment Tracking**: Add, remove, and manage stock investments
- **Real-time Calculations**: Calculate gains/losses, current values, and percentage returns
- **Portfolio Analysis**: View performance metrics, top performers, and losing investments
- **Data Persistence**: Save/load portfolio data and export to CSV format
- **Real-time Simulation**: Simulate stock price fluctuations

### OOP Principles Demonstrated

#### 1. Classes and Objects
- **Stock Class**: Models individual stocks with symbol, company name, and price data
- **Investment Class**: Represents investment positions in specific stocks
- **Portfolio Class**: Manages collections of investments with comprehensive analysis

#### 2. Encapsulation
- All member variables are private with controlled access through public methods
- Getter and setter methods ensure data integrity
- Input validation prevents invalid data states

#### 3. Constructors and Destructors
- Multiple constructors for flexible object initialization
- Copy constructors for proper object copying
- Destructors ensure proper resource cleanup

#### 4. Composition and Aggregation
- **Composition**: Portfolio owns and manages Investment objects
- **Aggregation**: Investment references Stock objects through smart pointers
- Proper object lifetime management

#### 5. STL Integration
- **Containers**: `std::vector` for storing collections
- **Algorithms**: `std::sort`, `std::find_if`, `std::accumulate`, `std::max_element`
- **Iterators**: Full iterator support for STL compatibility
- **Smart Pointers**: `std::shared_ptr` for memory management

#### 6. File I/O
- Binary file format for efficient data storage
- CSV export for spreadsheet compatibility
- Error handling for file operations

## Project Structure

```
portfolio_manager/
├── Stock.h              # Stock class declaration
├── Stock.cpp            # Stock class implementation
├── Investment.h         # Investment class declaration
├── Investment.cpp       # Investment class implementation
├── Portfolio.h          # Portfolio class declaration
├── Portfolio.cpp        # Portfolio class implementation
├── main.cpp            # Main application with console interface
├── Makefile            # Build configuration
└── README.md           # This file
```

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

### Sample Data
The application includes sample data featuring major tech stocks:
- Apple Inc. (AAPL)
- Microsoft Corporation (MSFT)  
- Amazon.com Inc. (AMZN)
- Alphabet Inc. (GOOGL)
- Tesla Inc. (TSLA)

