CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = main
OBJS = main.o SquareMat.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp SquareMat.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

SquareMat.o: SquareMat.cpp SquareMat.hpp
	$(CXX) $(CXXFLAGS) -c SquareMat.cpp

Main: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

test:
	$(CXX) $(CXXFLAGS) test_squaremat.cpp SquareMat.cpp -o test && ./test


clean:
	rm -f *.o $(TARGET) test

.PHONY: all clean Main valgrind