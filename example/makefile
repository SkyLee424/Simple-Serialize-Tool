CXX = clang++
TARGET = example
CXXFLAGS = -std=c++17 -c

INCLUDE_PATH = -I/home/skylee/Documents/WorkSpace/Demo/Serialize/includes

SRC = $(wildcard *.cpp)
DEPEND = $(patsubst %.cpp, %.o, $(SRC))

$(TARGET): $(DEPEND)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@  $(INCLUDE_PATH)

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -f *.o