CXX=g++
CXXFLAGS=-Wall
LDFLAGS= -lSDL2 -g -std=c++11
EXEC=space_game
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
			
