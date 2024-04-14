CXX = g++
CXXFLAGS = -std=c++17
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp,%.o,$(SOURCES))
TESTS = $(wildcard tests/test-*.cpp)
TEST_EXECS = $(patsubst tests/%.cpp,%,$(TESTS))

all: $(OBJECTS) $(TEST_EXECS)

$(OBJECTS): %.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_EXECS): %: tests/%.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) $< $(OBJECTS) -o $@