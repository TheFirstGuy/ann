/*
5/30/2016
Programmer: Urs Evora
Testing functions for Neuron and ANN.
*/

#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>			// random
#include <stdlib.h> 	// random
#include "Neuron.h"
#include "ANN.h"




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

// Tests constructor, copy constructor, and destructor.
// Num: number of input features. Range: Max possible size of
// hidden layers multiplied by num. Assumes randD() functions.
// numLayers: number of layers in network.
bool testANNConstructors(int num, int range, int numLayers){
	std::vector<int> layers;
	for( int i = 1; i <= num; ++i ){
		layers.clear();	
		// Initialize layers
		for( int j = 0; j < numLayers; ++j){
			layers.push_back( (int)ceil( randD() * i * range ));
		}
		for(double learningRate = 0.1; learningRate < 0.8; learningRate += 0.1 ){
			ANN net1( i, layers, learningRate );
			ANN net2 = net1;
		}
		if( net1.getNumIn() != net2.getNumIn() ){
			std::cout << "getNumIn() Failed. Net1: " << net1.getNumIn() <<
			" Net2: " << net2.getNumIn() << std::endl;
			return false;
		}
		if( net1.getNumOut() != net2.getNumOut() ){
			std::cout << "getNumOut() Failed. Net1: " << net1.getNumOut() <<
			" Net2: " << net2.getNumOut() << std::endl;
			return false;
		}
		if( net1.getNumHidLayers() != net2.getNumHidLayers() ){
			std::cout << "getNumHidLayers() Failed. Net1: " << net1.getNumHidLayers() <<
			" Net2: " << net2.getNumHidLayers() << std::endl;
			return false;
		}
		for( int k = 0; k < net1.getNumHidLayers(); ++k){
			if( net1.getNumNeurons(k) != net2.getNumNeurons(k) ){
				std::cout << "getNumNeurons() Failed. Net1: " << net1.getNumNeurons() <<
				" Net2: " << net2.getNumNeurons() << std::endl;
				return false;
			}
		}  
	}
	return true;
}

// Tests activate() function and copy constructor function.
// Num: number of input features. Range: Max possible size of
// hidden layers multiplied by num. Assumes randD() functions.
// numLayers: number of layers in network.
// iterations: number of activations tested.
bool testANNActivate(int num, int range, int numLayers, int iterations){
	std::vector<int> layers;
	// Initialize layers
	for( int j = 0; j < numLayers; ++j){
		layers.push_back( (int)ceil( randD() * i * range ));
	}
	ANN net1( i, layers, learningRate );
	ANN net2 = net1;
	std::vector<double> instance;
	for( int i = 0; i < iterations; ++i){
		// Generate random instances
		instance.clear();
		for( int j = 0; j < net1.getNumIn(); ++j){
			instance.push_back(randD());
		}	
		std::vector<double> result1;
		std::vector<double> result2;
		net1.activate( instance, result1 );
		net2.activate( instance, result2 );
		for( int j = 0; j < result1.size(); ++j ){
			if( result1[j] != result2[j] ){
				std::cout << "Activation failed. Result1[" << j << "]: " << result1[j]
				<< " Result2[" << j << "]: " << result2[j] << std::endl;
				std::cout << "Net1 Stats \n";
				std::cout << "Number of Layers: " << result1.getNumHidLayers() << std::endl;
				std::cout << "Number inputs: " << result1.getNumIn() << std::endl;
				std::cout << "Number outputs: " << result1.getNumOut() << std::endl;
				std::cout << "Net2 Stats \n";
				std::cout << "Number of Layers: " << result2.getNumHidLayers() << std::endl;
				std::cout << "Number inputs: " << result2.getNumIn() << std::endl;
				std::cout << "Number outputs: " << result2.getNumOut() << std::endl;
				return false;
			}
		}
	}
	return true;
}

// Tests back propagation. Variables the same as
// test activate. If neural nets diverge, then error occured.
bool testANNTrain(int num, int range, int numLayers, int iterations){
	std::vector<int> layers;
	// Initialize layers
	for( int j = 0; j < numLayers; ++j){
		layers.push_back( (int)ceil( randD() * i * range ));
	}
	ANN net1( i, layers, learningRate );
	ANN net2 = net1;
	std::vector<double> instance;
	std::vector<double> expected;
	for( int i = 0; i < iterations; ++i){
		// Generate random instances
		instance.clear();
		for( int j = 0; j < net1.getNumIn(); ++j){
			instance.push_back(randD());
		}	
		// Generate expected values
		for( int j = 0; j < net1.getNumOut(); ++j){
			if(randD() > 0.5){
				expected.push_back( 1.0 );
			}
			else{ expected.push_back( 0.0 ); }
		}
		std::vector<double> result1;
		std::vector<double> result2;
		net1.train( instance, expected ,result1 );
		net2.train( instance, expected ,result2 );
		for( int j = 0; j < result1.size(); ++j ){
			if( result1[j] != result2[j] ){
				std::cout << "Training failed. Result1[" << j << "]: " << result1[j]
				<< " Result2[" << j << "]: " << result2[j] << std::endl;
				std::cout << "Net1 Stats \n";
				std::cout << "Number of Layers: " << result1.getNumHidLayers() << std::endl;
				std::cout << "Number inputs: " << result1.getNumIn() << std::endl;
				std::cout << "Number outputs: " << result1.getNumOut() << std::endl;
				std::cout << "Net2 Stats \n";
				std::cout << "Number of Layers: " << result2.getNumHidLayers() << std::endl;
				std::cout << "Number inputs: " << result2.getNumIn() << std::endl;
				std::cout << "Number outputs: " << result2.getNumOut() << std::endl;
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
	std::cout << "Testing ANN constructors up to 5 layers, with up to 100 neurons per layer." << std::endl;
	testANNConstructors( 50, 2, 5 );
	std::cout << "Testing ANN activation up to 5 layers, with up to 100 neurons per layer." << 
	" With up to 100 iterations. "<< std::endl;
	testANNActivate( 50, 2, 5, 100 );
	std::cout << "Testing ANN training up to 5 layers, with up to 100 neurons per layer." << 
	" With up to 100 iterations. "<< std::endl;
	testANNTrain(50, 2, 5, 100 );
	std::cout << "Test complete." << std::endl;
	return 0;
}
