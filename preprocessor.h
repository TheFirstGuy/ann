/*
Date: 6/7/2016
Programer: Urs Evora
Header file for preprocessing functions.
*/

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <vector>
#include <string>


/* Reads an ARFF file completely and stores instances, expected values, 
features and output classes to vectors stored in memory. Might crash with 
very large files.
fileName: Name/path of file to be read.
instances: vector of specific features to be trained on.
evs: Expected Values that coorelate to each instance (might combine to single class)
classes: Output classifications and how they coorelate to output neurons.
features: Names of each feature coorelating to the instances.
*/
void readARFF( const std::string& fileName, std::vector<vector<double>*>& instances,
std::vector<vector<double>*>& evs, std::vector<std::string>& classes, 
std::vector<std::string>& features );




#endif
