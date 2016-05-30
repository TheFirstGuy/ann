/*
Date: 5/29/2016
Programer: Urs Evora
Header file for Neurons.
*/

#ifndef NEURON_H
#define NEURON_H

#include <vector>

class Neuron{
public:
	// Contructor for Neuron. numSynapse: number of inputs synapse required for 
	// this neuron. Typically this is the number of neurons in the previous layer,
	// or number of features.
	Neuron(const int numSynapse);
	
	//Activates neuron and synapse. inputs: vector of input features.
	double activate(const std::vector<double>& inputs);

	//Back propagate
	double backProp(const std::vector<double>& deltaIn); 
	
private:
	std::vector<double> synapse;
	double bias;
	// stores last activation. Used for back propagation and debugging.
	std::vector<double> lastInputs;
	// error from last back propagation.	
	double delta;
}

#endif
