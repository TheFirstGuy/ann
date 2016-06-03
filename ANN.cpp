/*
Date: 6/1/2016
Programer: Urs Evora
Implementation file for ANN.
*/

#include <vector>
#include <algorithm>	// std::fill
//#include <pthread.h>
#include "ANN.h"
#include "Neuron.h"

ANN::ANN(const int& numFeatures, const std::vector<int>& layers, const double& learningRate)
	:numIn(numFeatures), learningRate(learningRate){
	// Initialize layers of the network
	for( int i = 0; i < layers.size(); i++ ){
		std::vector<Neuron*> layer;
		// Initialize neurons for each layer.
		for( int j = 0; j < layers[i]; j++ ){
			// Input layer is dependent on number of Features.
			if( i == 0 ){
				layer.push_back(new Neuron(numFeatures, learningRate));
			}
			else{
				layer.push_back(new Neuron( layers[i-1], learningRate));
			}
		}
		// Add to network.
		network.push_back(layer);
	}
}

void ANN::activate(const std::vector<double>& instance, std::vector<double>& result ){
	// Layer loop
	for( int i = 0; i < network.size(); i++){
		// Neuron loop. For every neuron, activate on output of previous layer
		// or instance if input layer.
		std::vector<double> lastOutputs;
		if( i != 0 ){ getOutputs( i - 1, lastOutputs); 
		for( int j = 0; j < network[i].size(); j++ ){
			// if input layer, pass instance.
			if( i == 0 ){
				result.push_back(network[i][j]->activate( instance ));
			}
			// Otherwise pass last layers outputs
			else{
				// If last activation, save outputs for return
				if( i == network.size() - 1 ){
					result.push_back(network[i][j]->activate(lastOutputs));
				}
				else{
					network[i][j]->activate(lastOutputs);
				}
			}
		}
	}
}

void ANN::train(const std::vector<double>& instance, const std::vector<double>& expected,
	std::vector<double>& result ){
	activate( instance, result );
	std::vector<double> error;
	// Two delta vectors to 
	std::vector<double> delta1;
	std::vector<double> delta2;
	// Matricies for forward synapse
	std::vector<std::vector<double>*> fs1(network[network.size() - 1], new std::vector<double>(expected.size(), 1.0)); 
	std::vector<std::vector<double>*> fs2;
	calculateError( expected, result, error );
	for( int i = network.size() - 1; i >= 0; i--){
		// Get forward synapse before back prop
		if( i % 2 == 0 && i != 0){ 
			delta1.clear();
			getFS(i - 1, fs2);
		}
		else{
			delta2.clear();
			getFS(i - 1, fs1);
		}
		for( int j = 0; j < network[i].size(); j++ ){
			// If output layer. Delta = error
			if( i == network.size() ){
				delta1.push_back(network[i][j]->backProp(error, &fs1[j]);
			}
			else{
				// Use second delta if odd i
			 	if( i % 2 != 0 ){
					delta2.push_back(network[i][j]->backProp(delta1, &fs2[j]); 
				}
				else{
					delta1.push_back(network[i][j]->backProp(delta2, &fs1[j]);
				}
			}
		}
	}	
}
	
	
void ANN::getOutputs( const int& layer, std::vector<double>& result ) const{
	result.clear();
	for( int i = 0; i < network[layer].size(); i++ ){
		result.push_back(network[layer][i]->getOutput();
	}
}

void getFS(const int& layer, std::vector<std::vector<double>*>& result ) const{
	// clear vector
	for( std::vector<std::vector<double>>::iterator itr = result.begin(); itr != result.end(); ++itr){
		delete (*itr);
	}
	result.clear();
	// Loop through each neuron in current layer.
	for( int i = 0; i < network[layer].size(); i++ ){
		// Loop through each neuron in forward layer.
		std::vector<double>* fs = new std::vector<double>(network[layer+1].size());
		for( int j = 0; j < network[layer + 1].size(); j++ ){
			fs->push_back(network[layer+1][j]->getSynapse(i);
		}
		result.push_back(fs);
	}
}


int ANN::getNumOut() const{
	return numOut; 
}

int ANN::getNumIn() const{
	return numIn;
}

int ANN::getNumHidLayers() const{
	return network.size();
}

int ANN::getNumNeurons( const int& layer ) const{
	return network[layer].size();
}
