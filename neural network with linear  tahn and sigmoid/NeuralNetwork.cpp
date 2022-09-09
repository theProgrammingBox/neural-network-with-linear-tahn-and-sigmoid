#include "NeuralNetwork.h"

/*
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
*/

NeuralNetwork::NeuralNetwork(int topologySize, int* topology)
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
}

NeuralNetwork::~NeuralNetwork()
{
	delete[] topology;
	delete[] weights;
	delete[] biases;
	delete[] trainingActivationValues;
	delete[] trainingPreactivationValues;
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
	trainingPreactivationValues = new float[biasesSize];

	dActivationValues = new float[biasesSize + topology[0]];
	dPreactivationValues = new float[biasesSize];
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
		trainingPreactivationValues = new float[biasesSize];

		dActivationValues = new float[biasesSize + topology[0]];
		dPreactivationValues = new float[biasesSize];
	}

	return *this;
}

NeuralNetwork::NeuralNetwork(NeuralNetwork&& other)
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

	dActivationValues = other.dActivationValues;
	other.dActivationValues = nullptr;

	dPreactivationValues = other.dPreactivationValues;
	other.dPreactivationValues = nullptr;
}

NeuralNetwork& NeuralNetwork::operator=(NeuralNetwork&& other)
{
	if (this != &other)
	{
		delete[] topology;
		delete[] weights;
		delete[] biases;
		delete[] trainingActivationValues;
		delete[] trainingPreactivationValues;
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

		dActivationValues = other.dActivationValues;
		other.dActivationValues = nullptr;

		dPreactivationValues = other.dPreactivationValues;
		other.dPreactivationValues = nullptr;
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
}