TEST_TARGET = tests
PROJECT_TARGET = ascii85

CXX = g++
C_FLAGS = -std=c++17
L_FLAGS = -lgtest -lgtest_main -lpthread

PROJECT_SOURCE = main.cpp
TEST_SOURCE = test.cpp

all: $(PROJECT_TARGET) $(TEST_TARGET)

$(PROJECT_TARGET): $(PROJECT_SOURCE)
	$(CXX) $(C_FLAGS) -o $(PROJECT_TARGET) $(PROJECT_SOURCE)

$(TEST_TARGET): $(TEST_SOURCE)
	$(CXX) $(C_FLAGS) -o $(TEST_TARGET) $(TEST_SOURCE) $(L_FLAGS)


clean:
	rm -f $(PROJECT_TARGET) $(TEST_TARGET) *.o

test: $(TEST_TARGET)
	./$(TEST_TARGET)


.PHONY: all clean test
