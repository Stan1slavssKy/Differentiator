#==========================================================================================

# Makefile for calc_project
#		author: Kurnevich Stanislav

#==========================================================================================

CXX       = g++
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

VALGRIND_FLAGS = --leak-check=full

DIFF_DIR = ./differentiator
LIBS_DIR = ./libs
TREE_DIR = ./tree

SOURCE = $(DIFF_DIR)/diff.cpp $(DIFF_DIR)/main.cpp $(LIBS_DIR)/Onegin.cpp $(TREE_DIR)/tree.cpp
OBJECT = $(SOURCE:.cpp=.o)
OUTPUT = Calculator

default: valgrind

valgrind: $(OUTPUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUTPUT) "test"

launch: $(OUTPUT)
	./$(OUTPUT) "test"

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

main.o: $(DIFF_DIR)/main.cpp
	$(CXX) -c $^

diff.o: $(DIFF_DIR)/diff.cpp
	$(CXX) -c $^

Onegin.o: $(LIBS_DIR)/Onegin.cpp
	$(CXX) -c $^

tree.o: $(TREE_DIR)/tree.cpp
	$(CXX) -c $^

clean:
	rm -f *.o *.a $(OBJECT) $(OUTPUT)

#==========================================================================================