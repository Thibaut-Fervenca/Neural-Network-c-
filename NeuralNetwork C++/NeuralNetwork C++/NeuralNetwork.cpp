#include "stdafx.h"
#include "NeuralNetwork.h"
#include <iostream>



NeuralNetwork::NeuralNetwork(uint32_t* _topology, uint32_t _layerCount, int32_t seed)
{

	layerCount = _layerCount;

	Topology = _topology;

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

	layerCount = _main->layerCount;

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
	
	/*for (int i = 0; i < layerCount - 1; i++)
	{
		delete Sections[i];
	}
	delete Sections;*/
}

std::string NeuralNetwork::ToString()
{
	std::string toReturn = "";

	for (int i = 0; i < layerCount - 1; i++)
	{
		toReturn += Sections[i]->ToString();
	}

	return toReturn;
}

double * NeuralNetwork::FeedForward(double * _input)
{
	//Validation
	if (nullptr == _input)
		throw
		std::invalid_argument("input can't be null");

	double* toReturn = _input;

	//feed values through all sections
	for (int i = 0; i < layerCount - 1; i++)
	{
		toReturn = Sections[i]->FeedForward(toReturn);
		//std::cout << toReturn[i] << std::endl;
	}

	return toReturn;
}

void NeuralNetwork::Mutate(double MutationProbability, double MutationAmount)
{
	for (int i = 0; i < layerCount -1; i++)
	{
		Sections[i]->Mutate(MutationProbability, MutationAmount);
	}
}

void NeuralNetwork::Copy(NeuralNetwork * _ToCopy)
{
	_ToCopy->layerCount = layerCount;

	_ToCopy->randomizer = randomizer;

	_ToCopy->Topology = Topology;

	//_ToCopy->Sections = new NeuralSection*[layerCount - 1];

	for (int i = 0; i < layerCount - 1; i++)
	{
		Sections[i]->Copy(_ToCopy->Sections[i]);
	}
}

