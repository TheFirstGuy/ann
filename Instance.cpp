/*
Date: 6/8/2016
Programer: Urs Evora
Implementation file for instance class and functions.
*/

#include <vector>
#include <memory>
#include <string>


Instance::Instance( const std::string& name, const std::vector<double>* data,
		const std::vector<double>* expected, const std::shared_ptr<std::vector<std::string> > features,
		const std::shared_ptr<std::vector<std::string> > classes )
		:name(name), data(data), expected(excted), features(features), classes(classes){}
		
Instance::Instance( const Instance& rhs ){
	name = rhs.name;
	std::vector<double>* tData = new std::vector<double>();
	std::vector<double>* eData = new std::vector<double>();
	// Make new copy of data and expected on the heap
	for(const double d : *(rhs.data) ){
		tData->push_back(d);
	}
	for(const double d: *(rhs.expected)){
		eData->push_back(d);
	}
	// Assign members
	data = std::unique_ptr<std::vector<double> >(tData);
	expected = std::unique_ptr<std::vector<double> >(eData);
	features = std::shared_ptr<std::vector<std::string> >(rhs.features);
	classes = std::shared_ptr<std::vector<std::string> >(rhs.classes);
}

Instance& Instance::operator=( const Instance& rhs ){
	if( this != &other ){
		// clear old pointers
		data.reset();
		expected.reset();
		features.reset();
		classes.reset();
		// Make new copy of data and expected on the heap
		for(const double d : *(rhs.data) ){
			tData->push_back(d);
		}
		for(const double d: *(rhs.expected)){
			eData->push_back(d);
		}
		// Assign members
		name = rhs.name();
		data = std::unique_ptr<std::vector<double> >(tData);
		expected = std::unique_ptr<std::vector<double> >(eData);
		features = std::shared_ptr<std::vector<std::string> >(rhs.features);
		classes = std::shared_ptr<std::vector<std::string> >(rhs.classes);
	}
	return *this;
}

Instance::~Instance(){
	// clear old pointers
		data.reset();
		expected.reset();
		features.reset();
		classes.reset();
}

double Instance::operator[]( const int& index ) const{
	return (*data)[index];
}

double Instance::getExpected( const int& index ) const{
	return (*expected)[index];
}

size_t Instance::getDataSize() const{
	return data->size();
}

size_t Instance::getExpectSize() const{
	return expected->size();
}

std::string Instance::getFeatName( const int& index ) const{
	return (*features)[index];
}


std::string Instance::getClassName( const int& index ) const{
	return (*features)[index];
}






