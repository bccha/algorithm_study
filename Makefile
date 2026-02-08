# Makefile for Codejam/Codeforces

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17 -D_GLIBCXX_DEBUG

# Target file name (without extension)
# Usage: make run prob=A
PROB ?= main
SRC = $(PROB).cpp
EXE = $(PROB)

.PHONY: all clean run

all: $(EXE)

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXE)

run: $(EXE)
	@echo "Running $(EXE)..."
	@./$(EXE)

clean:
	rm -f *.o *.out $(EXE)
