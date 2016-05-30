# This is a comment. All will run by default when make is called in the 
# directory
all: ann

ann: main.o Neuron.o
	g++ main.o Neuron.o -o ann
	
	#g++ Neuron.o -o neuron

main.o: main.cpp
	g++ -c main.cpp

Neuron.o: Neuron.cpp
					g++ -c Neuron.cpp

clean:
					rm -rf *o ann

