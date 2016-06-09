# This is a comment. All will run by default when make is called in the 
# directory

CC=g++

CFLAGS= -std=c++0x -c

SOURCES= main.o ANN.o Neuron.o Instance.o 


all: ann

test: testAnn

# Compile with tester main file
testAnn: tester.o ANN.o Neuron.o Instance.o
	$(CC) tester.o ANN.o Neuron.o Instance.o -o testAnn

ann: main.o ANN.o Neuron.o
	$(CC) $(SOURCES) -o ann
	
	#g++ Neuron.o -o neuron

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

tester.o: tester.cpp
	$(CC) $(CFLAGS) tester.cpp
	
ANN.o: ANN.cpp
	$(CC) $(CFLAGS) ANN.cpp
	
Neuron.o: Neuron.cpp
	$(CC) $(CFLAGS) Neuron.cpp
	
Instance.o: Instance.cpp
	$(CC) $(CFLAGS) Instance.cpp

clean:
					rm -rf *o ann
					rm -rf *o testAnn

