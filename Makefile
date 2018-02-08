CC = g++
CFLAGS = -std=c++11 -g -Wall
TARGET = Hex
SOURCES = main.cpp HexGraph.cpp HexNode.cpp
OBJECTS = $(SOURCES:.cpp=.o)

default: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) main.o HexGraph.o HexNode.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

HexGraph.o: HexGraph.cpp HexGraph.hpp
	$(CC) $(CFLAGS) -c HexGraph.cpp

HexNode.o: HexNode.cpp HexNode.hpp
	$(CC) $(CFLAGS) -c HexNode.cpp

clean:
	rm ${OBJECTS} ${TARGET}
