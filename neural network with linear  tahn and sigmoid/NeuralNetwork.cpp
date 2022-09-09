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

	trainingActivationValues = new float[biasesSize + topology[0]];
	trainingPreactivationValues = new float[biasesSize];

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
	delete[] trainingActivationValues;
	delete[] trainingPreactivationValues;
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

	trainingActivationValues = new float[biasesSize + topology[0]];
	memcpy(trainingActivationValues, other.trainingActivationValues, (biasesSize + topology[0]) * sizeof(float));
	trainingPreactivationValues = new float[biasesSize];
	memcpy(trainingPreactivationValues, other.trainingPreactivationValues, biasesSize * sizeof(float));

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
		delete[] trainingActivationValues;
		delete[] trainingPreactivationValues;
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

		trainingActivationValues = new float[biasesSize + topology[0]];
		memcpy(trainingActivationValues, other.trainingActivationValues, (biasesSize + topology[0]) * sizeof(float));
		trainingPreactivationValues = new float[biasesSize];
		memcpy(trainingPreactivationValues, other.trainingPreactivationValues, biasesSize * sizeof(float));

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

	trainingActivationValues = other.trainingActivationValues;
	other.trainingActivationValues = nullptr;

	trainingPreactivationValues = other.trainingPreactivationValues;
	other.trainingPreactivationValues = nullptr;

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
		delete[] trainingActivationValues;
		delete[] trainingPreactivationValues;
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

		trainingActivationValues = other.trainingActivationValues;
		other.trainingActivationValues = nullptr;

		trainingPreactivationValues = other.trainingPreactivationValues;
		other.trainingPreactivationValues = nullptr;

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
	for (int i = 0; i < topologySize; i++)
	{
		for (int j = 0; j < topology[i]; j++)
		{
			for (int k = 0; k < topology[i + 1]; k++)
			{
				printf("%f ", weights[j * topology[i + 1] + k]);
			}
			printf("\n");
		}
		printf("\n");
	}

	printf("Biases:\n");
	for (int i = 0; i < topologySize; i++)
	{
		for (int j = 0; j < topology[i + 1]; j++)
		{
			printf("%f ", biases[j]);
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

void NeuralNetwork::FeedForward(float* input)
{
	for (int i = 0; i < topology[0]; i++)
	{
		trainingActivationValues[i] = input[i];
	}

	for (int i = 0; i < topologySize - 1; i++)
	{
		for (int j = 0; j < topology[i + 1]; j++)
		{
			trainingPreactivationValues[j] = biases[j];
			for (int k = 0; k < topology[i]; k++)
			{
				trainingPreactivationValues[j] += trainingActivationValues[k] * weights[k * topology[i + 1] + j];
			}
			trainingActivationValues[topology[0] + j] = LinearTahn(trainingPreactivationValues[j]);
		}
		for (int j = 0; j < topology[i + 1]; j++)
		{
			trainingActivationValues[topology[0] + j] = trainingActivationValues[topology[0] + j];
		}
	}
}