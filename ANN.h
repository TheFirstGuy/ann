/*
Date: 5/29/2016
Programer: Urs Evora
Header file for ANN.
*/


#ifndef ANN_H
#define ANN_H

#include <vector>
#include "Neuron.h"

class ANN{
public:
	// Contructor for ANN. NumFeatures: number of input nodes for the network.
	// Layers: The size of passed vector determines number of layers. Integers
	// provided in each index determine number of neurons in each layer. Output
	// layer is last layer in vector.
	ANN(const int& numFeatures, const std::vector<int>& layers); 

	// Trains ANN on passed instance by classifying and performing back 
	// propagation. instance: vector of features, must be equal
	// to numFeatures. expected: Desired/expected classifications of output 
	// neurons. Also expected to be of same size of output layer.
	std::vector<double> train(const std::vector<double>& instance, const std::vector<double>& expected );
	
	// Activates on given inputs. No back propagation. See train() for parameter
	// definitions.
	std::vector<double> activate(const std::vector<double>& instance);

	// Returns number of output neurons.
	int getNumOut() const;
	// Returns number of input neurons.
	int getNumIn() const;
	// Returns number of layers (hidden + output layers).
	int getNumHidLayers() const;
	// Returns number of neurons in a layer. layer: layer index number.
	int getNumNeurons( const int& layer ) const;


private:
	const int numIn;
	const int numOut;
	std::vector<vector<Neuron>> layers;
	

}

#endif
