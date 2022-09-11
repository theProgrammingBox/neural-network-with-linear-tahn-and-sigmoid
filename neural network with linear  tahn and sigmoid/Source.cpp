#include "NeuralNetwork.h"

int main()
{
	int topology[] = { 2, 3, 1 };
	NeuralNetwork nn(3, topology, 0.1);
	nn.Print();
	
	float input[] = { 1, 0 };
	float output[] = { 0 };
	nn.FeedForward(input, output);

	for (int i = 0; i < 1; i++)
	{
		printf("%f ", output[i]);
	}

	return 0;
}