#include "NeuralNetwork.h"

int main()
{
	int topology[] = { 2, 3, 1 };
	NeuralNetwork nn(3, topology, 0.1);
	nn.Print();

	printf("%f ", nn.LinearTahn(-2));
	printf("%f ", nn.LinearTahn(-1.5));
	printf("%f ", nn.LinearTahn(-0.5));
	printf("%f ", nn.LinearTahn(0.5));
	printf("%f ", nn.LinearTahn(1.5));
	printf("%f ", nn.LinearTahn(2));
	printf("\n");

	printf("%f ", nn.DLinearTahn(-2, -1));
	printf("%f ", nn.DLinearTahn(-1.5, 1));
	printf("%f ", nn.DLinearTahn(-0.5, -1));
	printf("%f ", nn.DLinearTahn(0.5, 1));
	printf("%f ", nn.DLinearTahn(1.5, -1));
	printf("%f ", nn.DLinearTahn(2, 1));
	printf("\n\n");

	printf("%f ", nn.LinearSigmoid(-2));
	printf("%f ", nn.LinearSigmoid(-0.75));
	printf("%f ", nn.LinearSigmoid(-0.2));
	printf("%f ", nn.LinearSigmoid(0.2));
	printf("%f ", nn.LinearSigmoid(0.75));
	printf("%f ", nn.LinearSigmoid(2));
	printf("\n");

	printf("%f ", nn.DLinearSigmoid(-2, -1));
	printf("%f ", nn.DLinearSigmoid(-0.75, 1));
	printf("%f ", nn.DLinearSigmoid(-0.2, -1));
	printf("%f ", nn.DLinearSigmoid(0.2, 1));
	printf("%f ", nn.DLinearSigmoid(0.75, -1));
	printf("%f ", nn.DLinearSigmoid(2, 1));
	printf("\n\n");

	return 0;
}