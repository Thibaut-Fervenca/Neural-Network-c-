// NeuralNetwork C++.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include "Random.h"
#include "NeuralSection.h"
#include "NeuralNetwork.h"
#include <string>
#include <iomanip>

#define INPUT_LENGTH 4

int main()
{

	Random* rand = new Random();

	int iterationCount = 0;

	int layerCount = 3;
	std::uint32_t* topology = new std::uint32_t[layerCount];
	topology[0] = 2;
	topology[1] = 2;
	topology[2] = 1;

	NeuralNetwork BestNetwork = new NeuralNetwork(topology, 3);

	double BestCost = std::numeric_limits<double>::max();
	double *BestNetworkResult = new double[INPUT_LENGTH];

	double** Inputs = new double*[INPUT_LENGTH];
	for (int i = 0; i < INPUT_LENGTH; i++) // input lenght = 4
	{
		Inputs[i] = new double;
	}
	
	Inputs[0][0] = 0; Inputs[0][1] = 0;
	Inputs[1][0] = 0; Inputs[1][1] = 1;
	Inputs[2][0] = 1; Inputs[2][1] = 0;
	Inputs[3][0] = 1; Inputs[3][1] = 1;

	double* ExpectedOutputs = new double[INPUT_LENGTH];
	ExpectedOutputs[0] = 0;
	ExpectedOutputs[1] = 1;
	ExpectedOutputs[2] = 1;
	ExpectedOutputs[3] = 0;


	
	
	while (iterationCount <= 1000000)
	{
		NeuralNetwork mutatedNetwork = new NeuralNetwork(BestNetwork);// Clone the best NEtwork at this point
		mutatedNetwork.Mutate(0.3,2.0); //We mutate the cloned network
		double MutatedNetworkCost = 0;
		double* CurrentNetworkResults = new double[INPUT_LENGTH]; // will be the result of the mutated network

		for (int i = 0; i < INPUT_LENGTH; i++) // input lenght = 4
		{
			double * Result = mutatedNetwork.FeedForward(Inputs[i]);
			MutatedNetworkCost += abs(Result[0] - ExpectedOutputs[i]); 


			CurrentNetworkResults[i] = Result[0];
		}

		//if the mutated network perform better 
		if (MutatedNetworkCost < BestCost)
		{
			BestNetwork = mutatedNetwork;
			BestCost = MutatedNetworkCost;
			BestNetworkResult = CurrentNetworkResults;
		}

		if (iterationCount % 20000 == 0)
		{
			system("cls");
			for (int i = 0; i < INPUT_LENGTH; i++) // input lenght = 4
			{
				std::cout << "Cost : " << Inputs[i][0] << " : " << Inputs[i][1] << " | " << std::setprecision(5) << BestNetworkResult[i] << std::endl;
			}
			std::cout << "Best Cost : " << BestCost << std::endl;
			std::cout << "Iteration : " << iterationCount << std::endl;
		}

		iterationCount++;

		
		//getchar();

	}

	getchar();

	delete(rand);

    return 0;
}

