# Variables for compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Name of the final executable
TARGET = CastleProblem

# Default rule (runs when you just type 'make')
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): CastleProblem.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) CastleProblem.o

# Rule to compile the source file into an object file
CastleProblem.o: CastleProblem.cpp
	$(CXX) $(CXXFLAGS) -c CastleProblem.cpp

# Clean rule to remove built files
clean:
	rm -f $(TARGET) CastleProblem.o
