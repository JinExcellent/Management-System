CXX = g++
TARGET = main

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

CXXLAGS = -c -Wall

$(TARGET): $(OBJ)
		$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXLAGS) $< -o $@

.PYONY:clean

clean:
	rm -f *.o $(TARGET)
