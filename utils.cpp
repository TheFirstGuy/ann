/*
6/9/2016
Programmer: Urs Evora & Stefan Cherubin
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
	true_negative = 0;
	true_positive = 0;
	false_negative = 0;
	false_positive = 0;
	total_accuracy = 0.0f;
}
FOne::FOne(float sig_level, int tpositive, int fpositive, int tnegative, int fnegative) {
	significance_level = sig_level;
	alpha = significance_level;
	beta = sqrtf((1.00f / alpha) - 1.00f);
	true_negative = tnegative;
	true_positive = tpositive;
	false_negative = fnegative;
	false_positive = fpositive;
	total_accuracy = 0.0f;
}
float FOne::calculateFScore()
{
	if (((1 + beta * beta) * true_positive + (beta * beta) * false_negative + false_positive) > 0) {

		total_accuracy = (1 + beta * beta) * true_positive /
			((1 + beta * beta) * true_positive + (beta * beta) * false_negative + false_positive);

	}
	else {
		total_accuracy = -1.0;
	}
	return total_accuracy;
}
void FOne::incrementTPositive()
{
	true_positive++;
}

void FOne::incrementFPositive()
{
	false_positive++;
}

void FOne::incrementTNegative()
{
	true_negative++;
}

void FOne::incrementFNegative()
{
	false_negative++;
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
	std::vector<char> temp(size);
	//char temp [size];
	for(int i = 0; i < size; ++i){
		temp[i] = randC();
	}
	return std::string(temp.data(), size);
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

void printResult( const vector<double>& result, const Instance& inst, ostream& os ){

}
