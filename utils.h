/*
6/9/2016
Programmer: Urs Evora & Stefan Cherubin
Utility functions for ANN.
*/


#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include "Instance.h"

//F1 Score class, meant to hold variables and functions needed for calculating F1 score
//Note that the significance level is needed for type I and type II error calculations. Alpha is equal to the signifiance error, and is used for type I 
//error calculations. Note that alpha, in terms of beta, is: 1/(1 + beta^2). Beta is used for type two error calculations
//The F1 score, in terms of type I and type II errors is: 
//(1 + beta^2) * true_positive /[ (1 + beta^2) * true_positive + beta^2 * false_negative + false_positive ]
//Note that this formula has a resembalance to Baye's Theorem.
//The significance level will be initially set to 0.05
class FOne {
public:
	FOne();
	FOne(float sig_level, int tpositive, int fpositive, int tnegative, int fnegative);
	int calculateFScore();
private:
	int true_positive, false_positive, true_negative, false_negative;
	float significance_level, alpha, beta, total_accuracy;
};

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
