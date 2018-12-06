#pragma once

#include "NeuralSection.h"
#include "Random.h"

class NeuralNetwork
{
public:
	NeuralNetwork(uint32_t* _topology, uint32_t _layerCount, int32_t Seed =0);
	NeuralNetwork(NeuralNetwork * _main);
	~NeuralNetwork();

	std::string ToString();

private :
	
	uint32_t *Topology;
	Random* randomizer;
	NeuralSection **Sections;
	uint32_t layerCount;

public:


	
};

