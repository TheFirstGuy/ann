/*
6/9/2016
Programmer: Urs Evora & Stefan Cherubin
Utility functions for ANN.
*/


#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <iostream>
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
	void incrementTPositive();
	void incrementFPositive();
	void incrementTNegative();
	void incrementFNegative();
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
<<<<<<< HEAD
//TODO: add function to check results of classified data.
//Correctly classified and un-classified data should be in two seperate containers.
//Sweep each container, then update the needed variables for calculating FScore accordingly.
//Number of false positives and false negatives will be determined by the significance level and number of data points in each container
//A significance level of 0.05 should mean that the bottom 2.5% of the positive container should be false positive 
//and top 2.5% of negative container should be false negatives.
//I believe that its 2.5% since there are two sets to work with
=======

/* Prints result of ann activation to given ostream.*/
bool printResult( const std::vector<double>& result, const Instance& inst, std::ostream& os );
<<<<<<< HEAD
>>>>>>> ab759951266736e1936e42daa5f2761c21e31f3f
=======

/*
 Checks if a comma seperated string can be converted into a vector of some element.
 elementCheck is a function pointer which takes a substring that checks if substring can
 be valid element.
 */
bool valCommaStr( const std::string& str, bool (*elementCheck)( const std::string& , const size_t&
, const size_t& ) );

/* Checks if substring is a valid integer. [ Low, high ) */
bool valIntStr( const std::string& str, const size_t& low, const size_t& high );

/* Converts a comma seperated string of integers to a vector of ints.
 Returns true when successful. */
bool strToIntVec( const std::string& str, std::vector<int>& result );

/* Checks if substring is a valid double. [Low, high ) */
bool valDoubleStr( const std::string& str, const size_t& low, const size_t& high );



>>>>>>> 1d3717b8924b4a89aea51d25ca86c5d9169a2fd5
#endif
