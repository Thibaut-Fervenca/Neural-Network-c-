// NeuralNetwork C++.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include "Random.h"
#include "NeuralSection.h"
#include "NeuralNetwork.h"
#include <string>

int main()
{

	Random* rand = new Random();

	//Test Rand
	std::cout << rand->NextDouble() << std::endl; 
	std::cout << rand->Next() << std::endl;

	NeuralSection* section = new NeuralSection(3, 2, rand);
	NeuralSection* secondNeuralSection = new NeuralSection(*section);

	std::cout << secondNeuralSection->ToString() << std::endl;

	int layerCount = 2;
	uint32_t *topology = new uint32_t[layerCount];

	topology[0] = 3;
	topology[1] = 2;

	NeuralNetwork* neuralNetwork = new NeuralNetwork(topology,layerCount);

	std::cout << neuralNetwork->ToString() << std::endl;


	delete(rand);

    return 0;
}

