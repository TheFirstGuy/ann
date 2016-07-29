/*
6/9/2016
Programmer: Urs Evora
Implementation of Utility functions for ANN.
*/

#include <stdlib.h>				// random
#include <string>			
#include <memory>			// smart pointers
#include <vector>
#include <iostream>
#include "Instance.h"

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

/* Converts string to lower case */
std::string toLower( const std::string& str ){
	std::string result(str.length(), '0');
	for( std::size_t i = 0; i < str.length(); ++i ){
		if( str[i] > 64 && str[i] < 91 ){
				result[i] = str[i] + ( 'z' - 'Z' );
		}
		else { result[i] = str[i]; }
	} 
	return result;
}

/* Prints result of ann activation to given ostream.*/
bool printResult( const std::vector<double>& result, const Instance& inst, std::ostream& os ){
	if( result.size() != inst.classes->size() ){ return false; }
	os << "Instance Name: " << inst.name << std::endl;
	double max = 0;
	size_t index = 0;
	for( size_t i = 0; i < inst.classes->size(); ++i ){
		if( max < result[i] ){ 
			max = result[i]; 
			index = i;
		}
		os << (*inst.classes)[i] << ": " << result[i] << std::endl;
	}
	os << "Classification: " << (*inst.classes)[index] << std::endl;
	return true;
}



