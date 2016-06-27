/*
6/9/2016
Programmer: Urs Evora
Utility functions for ANN.
*/


#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include "Instance.h"

// Returns random double from (0 to 1)
double randD();

// Returns a random integer from [0 to max) (exclusive)
int randI( const int& max );

// Returns random character
char randC();

// Returns random string
std::string randS(const size_t& size);

// Generates random instances.
// num: number of instances to be generated.
// dataSize: number of features to be generated.
// eSize: number of expected outputs.
// strLen: length of random strings generated.
// instances: input/output vector of instances
void genRandInsts( const int& num, const int& dataSize, const int& eSize,
const int& strLen, std::vector<Instance>& instances );

// Returns a copy of a string in lower case 
std::string toLower( const std::string& str );

#endif
