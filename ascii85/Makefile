TEST_TARGET = tests
PROJECT_TARGET = ascii85

CXX = g++
C_FLAGS = -std=c++17 -I(GTEST_DIR)/include
L_FLAGS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread

PROJECT_SOURCE = main.cpp
TEST_SOURCE = test.cpp

PROJECT_OBJ = $(PROJECT_SOURCE:.cpp=.o)
TEST_OBJ = $(TEST_SOURCE:.cpp=.o)

all: $(PROJECT_TARGET) $(TEST_TARGET)

$(PROJECT_TARGET): $(PROJECT_SOURCE)
	$(CXX) -o $@ $^

$(TEST_TARGET): $(TEST_SOURCE)
	$(CXX) -o $@ $^ $(L_FLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(PROJECT_OBJ) $(TEST_OBJ) $(PROJECT_TARGET) $(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)


.PHONY: all clean test
