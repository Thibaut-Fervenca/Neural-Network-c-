#include "stdafx.h"
#include "NeuralNetwork.h"



NeuralNetwork::NeuralNetwork(uint32_t* _topology,uint32_t _layerCount, int32_t seed)
{

	layerCount = _layerCount;

	//Validation
	if (layerCount < 2)
		throw
		std::invalid_argument("Not enough layer for the neural network");

	
	randomizer = new Random();

	Sections = new NeuralSection*[layerCount - 1];

	for (int i = 0; i < layerCount - 1; i++)
	{
		Sections[i] = new NeuralSection(_topology[i], _topology[i + 1], randomizer);
	}

}



NeuralNetwork::NeuralNetwork(NeuralNetwork * _main)
{
	randomizer = _main->randomizer;

	Topology = _main->Topology;

	Sections = new NeuralSection*[_main->layerCount - 1];

	for (int i = 0; i < _main->layerCount - 1; i++)
	{
		Sections[i] = new NeuralSection(_main->Sections[i]);
	}

}



NeuralNetwork::~NeuralNetwork()
{
}

std::string NeuralNetwork::ToString()
{
	std::string toReturn = "";

	for (int i = 0; i < layerCount - 1; i++)
	{
		toReturn +=Sections[i]->ToString();
	}

	return toReturn;
}

