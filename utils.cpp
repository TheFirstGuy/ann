/*
6/9/2016
Programmer: Urs Evora
Implementation of Utility functions for ANN.
*/

#include <stdlib.h>				// random
#include <string>			
#include <memory>			// smart pointers
#include <vector>
#include "Instance.h"
#include <math.h>
#include "utils.h"

FOne::FOne() {
	significance_level = 0.05f;
	alpha = significance_level;
	beta = sqrtf((1.00f / alpha) - 1.00f);
}

double randD(){
	return (double)rand() / RAND_MAX;
}

// Returns a random integer from [0 to max) (exclusive)
int randI( const int& max ){
	return (int)(rand() % max );
}
// Returns random character
char randC(){
	return (char)(rand() % 256);		
}

// Returns random string
std::string randS(const size_t& size){
	char temp [size];
	for(int i = 0; i < size; ++i){
		temp[i] = randC();
	}
	return std::string(temp, size);
}

// Generates random instances.
// num: number of instances to be generated.
// dataSize: number of features to be generated.
// eSize: number of expected outputs.
// strLen: length of random strings generated.
// instances: input/output vector of instances
void genRandInsts( const int& num, const int& dataSize, const int& eSize,
const int& strLen, std::vector<Instance>& instances ){
	std::shared_ptr<std::vector<std::string> > features(new std::vector<std::string>());
	std::shared_ptr<std::vector<std::string> > classes(new std::vector<std::string>());
	// Generate sudo names for features and classes
	for( int i = 0; i < dataSize; ++i){
		features->push_back(randS(strLen));
	}
	for( int i = 0; i < eSize; ++i){
		classes->push_back(randS(strLen));
	}
	// Generate instances
	for( int i = 0; i < num; ++i ){
		// Generate sudo data for each instance
		std::vector<double>* data = new std::vector<double>();
		std::vector<double>* expected = new std::vector<double>();
		for( int j = 0; j < dataSize; ++j ){
			data->push_back(randD());
		}
		for( int j = 0; j < dataSize; ++j ){
			expected->push_back(randD());
		}
		instances.push_back( Instance( randS(strLen), data, expected, features, classes ));
	}
}
