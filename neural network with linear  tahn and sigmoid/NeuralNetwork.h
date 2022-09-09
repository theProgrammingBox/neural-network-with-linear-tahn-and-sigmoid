#pragma once
#include <iostream>
#include "Randoms.h"

class NeuralNetwork
{
public:
	NeuralNetwork(int topologySize, int* topology);
	~NeuralNetwork();
	NeuralNetwork(const NeuralNetwork& other);
	NeuralNetwork& operator=(const NeuralNetwork& other);
	NeuralNetwork(NeuralNetwork&& other);
	NeuralNetwork& operator=(NeuralNetwork&& other);

	void Print();

private:
	int topologySize;
	int* topology;

	int weightsSize;
	float* weights;	// 3d

	int biasesSize;
	float* biases;	// 2d

	float* trainingActivationValues;	// 2d
	float* trainingPreactivationValues;	// 2d

	float* dActivationValues;		// 2d
	float* dPreactivationValues;	// 2d
};