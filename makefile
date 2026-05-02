CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

OBJS = main.o game.o utils.o battle.o

all: game

game: $(OBJS)
	$(CXX) $(CXXFLAGS) -o game $(OBJS)

main.o: main.cpp game.h utils.h battle.h
	$(CXX) $(CXXFLAGS) -c main.cpp

game.o: game.cpp game.h utils.h
	$(CXX) $(CXXFLAGS) -c game.cpp

utils.o: utils.cpp utils.h game.h
	$(CXX) $(CXXFLAGS) -c utils.cpp

battle.o: battle.cpp battle.h game.h utils.h
	$(CXX) $(CXXFLAGS) -c battle.cpp

clean:
	rm -f $(OBJS)

clean_game:
	rm -f game *.exe