#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int topologySize, int* topology, float lamda)
{
	this->topologySize = topologySize;
	this->topology = new int[topologySize];
	memcpy(this->topology, topology, topologySize * sizeof(int));

	weightsSize = 0;
	biasesSize = 0;
	for (int i = 0; i < topologySize - 1; i++)
	{
		weightsSize += topology[i] * topology[i + 1];
		biasesSize += topology[i + 1];
	}
	weights = new float[weightsSize];
	biases = new float[biasesSize];

	activationValues = new float[biasesSize + topology[0]];
	preactivationValues = new float[biasesSize];

	dWeights = new float[weightsSize];
	dBiases = new float[biasesSize];

	dActivationValues = new float[biasesSize + topology[0]];
	dPreactivationValues = new float[biasesSize];

	Random random;
	for (int i = 0; i < weightsSize; i++)
	{
		weights[i] = random.NormalRandom();
	}
	for (int i = 0; i < biasesSize; i++)
	{
		biases[i] = random.NormalRandom();
	}

	this->lamda = lamda;
}

NeuralNetwork::~NeuralNetwork()
{
	delete[] topology;
	delete[] weights;
	delete[] biases;
	delete[] activationValues;
	delete[] preactivationValues;
	delete[] dWeights;
	delete[] dBiases;
	delete[] dActivationValues;
	delete[] dPreactivationValues;
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& other)
{
	topologySize = other.topologySize;
	topology = new int[topologySize];
	memcpy(topology, other.topology, topologySize * sizeof(int));

	weightsSize = other.weightsSize;
	weights = new float[weightsSize];
	memcpy(weights, other.weights, weightsSize * sizeof(float));

	biasesSize = other.biasesSize;
	biases = new float[biasesSize];
	memcpy(biases, other.biases, biasesSize * sizeof(float));

	activationValues = new float[biasesSize + topology[0]];
	memcpy(activationValues, other.activationValues, (biasesSize + topology[0]) * sizeof(float));
	preactivationValues = new float[biasesSize];
	memcpy(preactivationValues, other.preactivationValues, biasesSize * sizeof(float));

	dWeights = new float[weightsSize];
	memcpy(dWeights, other.dWeights, weightsSize * sizeof(float));

	dBiases = new float[biasesSize];
	memcpy(dBiases, other.dBiases, biasesSize * sizeof(float));

	dActivationValues = new float[biasesSize + topology[0]];
	memcpy(dActivationValues, other.dActivationValues, (biasesSize + topology[0]) * sizeof(float));
	dPreactivationValues = new float[biasesSize];
	memcpy(dPreactivationValues, other.dPreactivationValues, biasesSize * sizeof(float));

	lamda = other.lamda;
}

NeuralNetwork& NeuralNetwork::operator=(const NeuralNetwork& other)
{
	if (this != &other)
	{
		delete[] topology;
		delete[] weights;
		delete[] biases;
		delete[] activationValues;
		delete[] preactivationValues;
		delete[] dWeights;
		delete[] dBiases;
		delete[] dActivationValues;
		delete[] dPreactivationValues;

		topologySize = other.topologySize;
		topology = new int[topologySize];
		memcpy(topology, other.topology, topologySize * sizeof(int));

		weightsSize = other.weightsSize;
		weights = new float[weightsSize];
		memcpy(weights, other.weights, weightsSize * sizeof(float));

		biasesSize = other.biasesSize;
		biases = new float[biasesSize];
		memcpy(biases, other.biases, biasesSize * sizeof(float));

		activationValues = new float[biasesSize + topology[0]];
		memcpy(activationValues, other.activationValues, (biasesSize + topology[0]) * sizeof(float));
		preactivationValues = new float[biasesSize];
		memcpy(preactivationValues, other.preactivationValues, biasesSize * sizeof(float));

		dWeights = new float[weightsSize];
		memcpy(dWeights, other.dWeights, weightsSize * sizeof(float));

		dBiases = new float[biasesSize];
		memcpy(dBiases, other.dBiases, biasesSize * sizeof(float));

		dActivationValues = new float[biasesSize + topology[0]];
		memcpy(dActivationValues, other.dActivationValues, (biasesSize + topology[0]) * sizeof(float));
		dPreactivationValues = new float[biasesSize];
		memcpy(dPreactivationValues, other.dPreactivationValues, biasesSize * sizeof(float));

		lamda = other.lamda;
	}

	return *this;
}

NeuralNetwork::NeuralNetwork(NeuralNetwork&& other) noexcept
{
	topologySize = other.topologySize;
	topology = other.topology;
	other.topology = nullptr;

	weightsSize = other.weightsSize;
	weights = other.weights;
	other.weights = nullptr;

	biasesSize = other.biasesSize;
	biases = other.biases;
	other.biases = nullptr;

	activationValues = other.activationValues;
	other.activationValues = nullptr;

	preactivationValues = other.preactivationValues;
	other.preactivationValues = nullptr;

	dWeights = other.dWeights;
	other.dWeights = nullptr;

	dBiases = other.dBiases;
	other.dBiases = nullptr;

	dActivationValues = other.dActivationValues;
	other.dActivationValues = nullptr;

	dPreactivationValues = other.dPreactivationValues;
	other.dPreactivationValues = nullptr;

	lamda = other.lamda;
}

NeuralNetwork& NeuralNetwork::operator=(NeuralNetwork&& other) noexcept
{
	if (this != &other)
	{
		delete[] topology;
		delete[] weights;
		delete[] biases;
		delete[] activationValues;
		delete[] preactivationValues;
		delete[] dWeights;
		delete[] dBiases;
		delete[] dActivationValues;
		delete[] dPreactivationValues;

		topologySize = other.topologySize;
		topology = other.topology;
		other.topology = nullptr;

		weightsSize = other.weightsSize;
		weights = other.weights;
		other.weights = nullptr;

		biasesSize = other.biasesSize;
		biases = other.biases;
		other.biases = nullptr;

		activationValues = other.activationValues;
		other.activationValues = nullptr;

		preactivationValues = other.preactivationValues;
		other.preactivationValues = nullptr;

		dWeights = other.dWeights;
		other.dWeights = nullptr;

		dBiases = other.dBiases;
		other.dBiases = nullptr;

		dActivationValues = other.dActivationValues;
		other.dActivationValues = nullptr;

		dPreactivationValues = other.dPreactivationValues;
		other.dPreactivationValues = nullptr;

		lamda = other.lamda;
	}

	return *this;
}

void NeuralNetwork::Print()
{
	printf("Topology: ");
	for (int i = 0; i < topologySize; i++)
	{
		printf("%d ", topology[i]);
	}
	printf("\n\n");

	printf("Weights:\n");
	int weightIndex = 0;
	for (int i = 0; i < topologySize; i++)
	{
		for (int j = 0; j < topology[i + 1]; j++)
		{
			for (int k = 0; k < topology[i]; k++)
			{
				printf("%f ", weights[weightIndex++]);
			}
			printf("\n");
		}
		printf("\n");
	}

	printf("Biases:\n");
	int biasIndex = 0;
	for (int i = 1; i < topologySize; i++)
	{
		for (int j = 0; j < topology[i]; j++)
		{
			printf("%f ", biases[biasIndex++]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Lamda: %f\n", lamda);
}

float NeuralNetwork::LinearTahn(float x)
{
	return (x <= 1 && x >= -1) * x + (x > 1) - (x < -1);
}

float NeuralNetwork::DLinearTahn(float x, float derivative)
{
	return (x <= 1 && x >= -1) + (x > 1) * (derivative < 0) * lamda + (x < -1) * (derivative > 0) * lamda;
}

float NeuralNetwork::LinearSigmoid(float x)
{
	return (x <= 0.5f && x >= -0.5f) * (x + 0.5f) + (x > 0.5f);
}

float NeuralNetwork::DLinearSigmoid(float x, float derivative)
{
	return (x <= 0.5f && x >= -0.5f) + (x > 0.5f) * (derivative < 0) * lamda + (x < -0.5f) * (derivative > 0) * lamda;
}

void NeuralNetwork::FeedForward(float* input, float* output)
{
	memcpy(activationValues, input, topology[0] * sizeof(float));

	int activationStartIndex;
	int activationIndex = 0;
	int preactivationIndex = 0;
	int weightIndex = 0;
	for (int i = 0; i < topologySize - 1; i++)
	{
		activationStartIndex = activationIndex;
		for (int j = 0; j < topology[i + 1]; j++)
		{
			activationIndex = activationStartIndex;
			//printf("%f\n", biases[preactivationIndex]);
			preactivationValues[preactivationIndex] = biases[preactivationIndex];

			for (int k = 0; k < topology[i]; k++)
			{
				//printf("%f * %f\n", activationValues[activationIndex], weights[weightIndex]);
				preactivationValues[preactivationIndex] += weights[weightIndex++] * activationValues[activationIndex++];
			}
			//printf("= %f\n", LinearTahn(preactivationValues[preactivationIndex]));
			activationValues[preactivationIndex + topology[0]] = LinearTahn(preactivationValues[preactivationIndex]);

			preactivationIndex++;
			//printf("\n");
		}
	}

	memcpy(output, activationValues + biasesSize + topology[0] - topology[topologySize - 1], topology[topologySize - 1] * sizeof(float));
}