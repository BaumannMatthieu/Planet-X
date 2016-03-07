CXX=g++
CXXFLAGS=-Wall
LDFLAGS= -lSDL2
EXEC=space_game
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
			
