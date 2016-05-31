/*
5/30/2016
Programmer: Urs Evora
Testing functions for Neuron and ANN.
*/

#include <iostream>
#include <vector>
#include <math.h>
#include "Neuron.h"

// Tests if randomD is within acceptable range

bool testRandom( int num ){
	double result;
	for(int i = 0; i < num; i++){
		result = randD();
		if(result > 1 || result < 0 ){ 
			std::cout << "Random Failed. result: " << result << std::endl;
			return false; 
		}
	}
	return true;
}

// Tests if sigmoid is within acceptable range (-1 - 1)

bool testSigmoid( double num ){
	double result;
	double adder = 0.00000000000001;	// arbitrary 
	double x = 0;
	while( x < num ){
		result = sigmoid(x);
		if( result > 1 || result < -1 ){
			std::cout << "Sigmoid Failed. result: " << result << " x: " << 
			std::endl;
			return false;
		}
		result = sigmoid(-x);
		if( result > 1 || result < -1 ){
			std::cout << "Sigmoid Failed. result: " << result << " x: " << 
			std::endl;
			return false;
		}
		x += adder;
		adder *= 10;
	}
	return true; 
}

// Tests Neuron activation with multiple sizes and learning rates
// with sudo data. Assumes randD works. Checks if activation is NaN
// or tends to infinity.
bool neuronActivate(int num){
	double learningRate = 0.1;
	int size;
	double result;
	for( ; size < num; size++ ){
		// Make test input
		std::vector<double> testInst;
		for(int i = 0; i < size; i++){
			testInst.push_back(randD());
		}
		// Test neuron
		for( ; learningRate < 0.8; learningRate += 0.1){
			Neuron n(size, learningRate);
			result = n.activate( testInst );
			if( result == -1 || isnan(result) || isfinite(result) ){
				std::cout << "Activation failed. Displaying input vector... /n";
				for( double d : testInst ){
					std::cout << d << endl;
				}
				std::cout << "Result: " << result << endl;
				return false;
			}
		}
	}
	return true;
}
