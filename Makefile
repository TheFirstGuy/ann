# This is a comment. All will run by default when make is called in the 
# directory
all: ann

test: testAnn

# Compile with tester main file
testAnn: tester.o ANN.o Neuron.o
	g++ tester.o ANN.o Neuron.o -o testAnn

ann: main.o ANN.o Neuron.o
	g++ main.o ANN.o Neuron.o -o ann
	
	#g++ Neuron.o -o neuron

main.o: main.cpp
	g++ -c main.cpp

tester.o: tester.cpp
	g++ -c tester.cpp
	
ANN.o: ANN.cpp
	g++ -c ANN.cpp
	
Neuron.o: Neuron.cpp
					g++ -c Neuron.cpp

clean:
					rm -rf *o ann
					rm -rf *o testAnn

