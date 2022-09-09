#include "NeuralNetwork.h"

int main()
{
	int topology[] = { 2, 3, 1 };
	NeuralNetwork nn(3, topology);
	nn.Print();

	return 0;
}