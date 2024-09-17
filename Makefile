CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O1
EXEC_FILES= tests main
ALL_HPP=jeu.hpp population.hpp grille.hpp animal.hpp coord.hpp ensemble.hpp param.hpp


tests: test.o ensemble.o coord.o animal.o grille.o population.o  jeu.o
	$(CXX) -o $@ $^ $(LDFLAGS)
# Regle generique
%.o: %.cpp $(ALL_HPP)
	$(CXX) -o $@ -c $< $(CXXFLAGS)


check: tests
	./tests

clean:
	rm -f *.o $(EXEC_FILES)


main: main.o ensemble.o coord.o animal.o grille.o population.o  jeu.o
	$(CXX) -o $@ $^

run: main 
	./main 