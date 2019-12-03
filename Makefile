OBJ = numerov.o func.o print.o norma.o bisection.o
DEPS =  $(OBJ:.o=.h)
SOURCES = main.cpp $(OBJ:.o=.cpp)

all : main.x $(SOURCES) $(DEPS) $(OBJ)

%.o: %.cpp $(DEPS)
	g++ -c -std=c++11 $<

main.x: main.cpp $(OBJ)
	g++ -std=c++11 -o $@ $(OBJ) main.cpp

.PHONY: clean
clean:
	rm -f *.o *~ *.x *# *.txt a.out
