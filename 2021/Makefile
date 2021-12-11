CURRENT_DAY = Day12
SOLUTION_FILE = $(CURRENT_DAY)/solution.cpp
SOLUTION_BINARY = solution
SOLUTION_TARGET = $(CURRENT_DAY)/$(SOLUTION_BINARY)
OBJS = $(CURRENT_DAY)/solution.o

#CPP_FLAGS = -Wall -Werror -Wextra -pedantic -ansi
CPP = g++

all: clean aoc test

aoc: 
	$(CPP) $(SOLUTION_FILE) -o $(SOLUTION_TARGET)

test:
	cd $(CURRENT_DAY) && ./$(SOLUTION_BINARY)

clean:
	rm -f $(SOLUTION_TARGET)
	rm -f $(OBJS)