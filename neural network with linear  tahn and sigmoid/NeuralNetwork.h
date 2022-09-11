#pragma once
#include <iostream>
#include "Randoms.h"

class NeuralNetwork
{
public:
	NeuralNetwork(int topologySize, int* topology, float lamda);
	~NeuralNetwork();
	NeuralNetwork(const NeuralNetwork& other);
	NeuralNetwork& operator=(const NeuralNetwork& other);
	NeuralNetwork(NeuralNetwork&& other) noexcept;
	NeuralNetwork& operator=(NeuralNetwork&& other) noexcept;

	void Print();
	float LinearTahn(float x);
	float DLinearTahn(float x, float derivative);
	float LinearSigmoid(float x);
	float DLinearSigmoid(float x, float derivative);
	void FeedForward(float* input, float* output);

private:
	int topologySize;
	int* topology;

	int weightsSize;
	float* weights;	// 3d

	int biasesSize;
	float* biases;	// 2d

	float* activationValues;	// 2d
	float* preactivationValues;	// 2d

	float* dWeights;	// 3d
	float* dBiases;	// 2d

	float* dActivationValues;		// 2d
	float* dPreactivationValues;	// 2d

	float lamda;
};