# Stock Portfolio Manager Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = portfolio_manager
SOURCES = Stock.cpp Investment.cpp Portfolio.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Stock.h Investment.h Portfolio.h

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Install dependencies (if needed)
install:
	@echo "No external dependencies required for this project"

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build files"
	@echo "  debug   - Build with debug information"
	@echo "  run     - Build and run the program"
	@echo "  install - Install dependencies"
	@echo "  help    - Show this help message"

.PHONY: all clean debug run install help