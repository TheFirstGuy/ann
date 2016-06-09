/*
Date: 6/8/2016
Programer: Urs Evora
Header file for instance class and functions.
*/

#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <memory>
#include <string>

/* The Instance class encapsulates data for a single instance.
It keeps track of features, class names, and data.
*/
class Instance{
	public:
		// Constructor for instance class. Data and expected will be converted into
		// unique pointers. Features and classes are copied/
		Instance( const std::string& name, const std::vector<double>* data,
		const std::vector<double>* expected, const std::shared_ptr<std::vector<std::string> > features,
		const std::shared_ptr<std::vector<std::string> > classes );
		
		// Copy constructor
		Instance( const Instance& rhs );
		
		// Copy assignment operator
		Instance& operator=( const Instance& rhs );
		
		// Destructor
		~Instance();
		
		// Returns specific feature data at provided index;
		double operator[]( const int& index ) const;
		
		// Returns specific expected data at provided index.
		double getExpected( const int& index ) const;
		
		// Return data instance size.
		size_t getDataSize() const;
		
		// Return expected size.
		size_t getExpectSize() const;
	
		// Returns name of feature at given index.
		std::string getFeatName( const int& index ) const;
		
		// Returns name of class at given index.
		std::string getClassName( const int& index ) const;
		
		// Training set name.
		const std::string name;
		
		// numeric representation of instance. a.k.a input data.
		const std::unique_ptr<std::vector<double> > data;
		
		// Numeric representation of expected outputs (0,1).
		const std::unique_ptr<std::vector<double> > expected;
		
		// Pointer to names of each feature input.
		const std::shared_ptr<std::vector<std::string> > features;
		
		// Pointer to names of each expected output classification
		const std::shared_ptr<std::vector<std::string> > classes;
		
};

#endif
