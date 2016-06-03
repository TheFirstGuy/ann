/*
5/30/2016
Programmer: Urs Evora
Testing functions for Neuron and ANN.
*/

#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h> 	// random
#include "Neuron.h"




// Tests if randomD is within acceptable range

bool testRandom( int num ){
	double result;
	for(int i = 0; i < num; i++){
		result = randD();
		if(result > 1 || !isfinite(result) || result < 0 ){ 
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
		if( result > 1 || !isfinite(result) || result < -1 ){
			std::cout << "Sigmoid Failed. result: " << result << " x: " << 
			std::endl;
			return false;
		}
		result = sigmoid(-x);
		if( result > 1 || !isfinite(result) || result < -1 ){
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
bool testActivation(int num){
	double learningRate = 0.1;
	double result;
	for(int size = 0 ; size < num; size++ ){
		// Make test input
		std::vector<double> testInst;
		for(int i = 0; i < size; i++){
			testInst.push_back(randD());
		}
		// Test neuron
		for( ; learningRate < 0.8; learningRate += 0.1){
			Neuron n(size, learningRate);
			result = n.activate( testInst );
			if( result <= -1 || !isfinite(result) || result >= 1){
				std::cout << "Activation failed. Displaying input vector... \n";
				for( int i = 0; i < testInst.size(); i++ ){
					std::cout << testInst[i] << std::endl;
				}
				std::cout << "Result: " << result << " Size: " << size << 
				" Learning Rate: "<< learningRate << std::endl;
				return false;
			}
		}
	}
	return true;
}

// Tests back propagation in similar manner activation is tested. 
// Calls both activation and backprop methods.
bool testBackProp(int num){
	double learningRate = 0.1;
	double result;
	for(int size = 0 ; size < num; size++ ){
		// Make test input
		std::vector<double> testInst;
		std::vector<double> testDelta;
		std::vector<double> testFS;
		for(int i = 0; i < size; i++){
			testInst.push_back(randD());
			testDelta.push_back(randD());
			testFS.push_back(randD());
		}
		// Test neuron
		for( ; learningRate < 0.8; learningRate += 0.1){
			Neuron n(size, learningRate);
			n.activate( testInst );
			result = n.backProp(testDelta, testFS);
			if( !isfinite(result) ){
				std::cout << "Result: " << result << " Size: " << size << 
				" Learning Rate: "<< learningRate << std::endl;
				std::cout << "BackProp failed. Displaying delta vector... \n";
				for( int i = 0; i < testDelta.size(); i++ ){
					std::cout << testDelta[i] << std::endl;
				}
				std::cout << "Displaying testFS vector... \n";
				for( int i = 0; i < testFS.size(); i++ ){
					std::cout << testFS[i] << std::endl;
				}
				return false;
			}
		}
	}
	return true;
}

int main(){
	srand(time(NULL));
	std::cout << "Testing Neuron..." << std::endl;
	std::cout << "Testing Random with 10000 numbers." << std::endl;
	testRandom( 10000 );
	std::cout << "Testing sigmoid with 10000 numbers." << std::endl;
	testSigmoid( 10000 );
	std::cout << "Testing activation up to size 50." << std::endl;
	testActivation( 50 );
	std::cout << "Testing back prop up to size 50." << std::endl;
	testBackProp(50);
	std::cout << "Test complete." << std::endl;
	return 0;
}
