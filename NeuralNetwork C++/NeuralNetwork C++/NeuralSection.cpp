#include "stdafx.h"
#include "NeuralSection.h"
#include <string>




NeuralSection::NeuralSection(uint32_t _InputCount, uint32_t _OutputCount, Random* _Randomizer)
{
	//Validation 
	if (_InputCount == 0)
	{
		throw 
			std::invalid_argument("Layer do not have Input neurons");
	}
	else if (_OutputCount == 0)
	{
		throw
			std::invalid_argument("Layer do not have Output neurons");
	}
	else if (nullptr == _Randomizer)
	{
		throw
			std::invalid_argument("Randomizer cannot be null");
	}

	//set the randomizer
	randomizer = _Randomizer;

	InputCount = _InputCount + 1;  // +1 for bias
	OutputCount = _OutputCount;


	Weights = new double*[InputCount]; 
	for (int i = 0; i < InputCount; i++)
	{
		Weights[i] = new double[_OutputCount];
	}

	//then we set the random weights
	for (int i = 0; i < _InputCount +1; i++)
	{
		for (int j = 0; j < _OutputCount; j++)
		{
			Weights[i][j] = randomizer->NextDouble() - 0.5f; //-0.5 to 0.5
		}
	}

	


}

NeuralSection::NeuralSection(NeuralSection * _Main)
{
	randomizer = _Main->randomizer;
	
	InputCount = _Main->InputCount;
	OutputCount = _Main->OutputCount;

	Weights = new double*[InputCount]; 
	for (int i = 0; i < InputCount; i++)
	{
		Weights[i] = new double[OutputCount];
	}

	// Set Weights
	for (int i = 0; i < InputCount; i++)
	{
		for (int j = 0; j < OutputCount; j++)
		{
			Weights[i][j] = _Main->Weights[i][j];
		}
	}


}

void NeuralSection::Copy(NeuralSection* _ToCopy)
{
	_ToCopy->randomizer = randomizer;

	_ToCopy->InputCount = InputCount;
	_ToCopy->OutputCount = OutputCount;

	//_ToCopy->Weights = new double*[_ToCopy->InputCount];
	/*for (int i = 0; i < _ToCopy->InputCount; i++)
	{
		_ToCopy->Weights[i] = new double[OutputCount];
	}*/

	// Set Weights
	for (int i = 0; i < _ToCopy->InputCount; i++)
	{
		for (int j = 0; j < _ToCopy->OutputCount; j++)
		{
			_ToCopy->Weights[i][j] = Weights[i][j];
		}
	}
}



std::string NeuralSection::ToString()
{
	std::string toReturn;
	

	for (int i = 0; i <InputCount; i++)
	{
		for (int j = 0; j < OutputCount; j++)
		{
			toReturn += "Neuron :" + std::to_string(i);
			toReturn += " Weight : " + std::to_string(Weights[i][j]);
			toReturn += " To Neuron : " + std::to_string(j);
			toReturn += "\n\n"; // new output Neuron
		}
		toReturn += "\n\n\n"; // new input Neuron
	}


	return toReturn;
	
}

double * NeuralSection::FeedForward(double * _Input)
{
	//validation
	if (nullptr == _Input)
	{
		throw
			std::invalid_argument("The input array cannot be null");
	}

	double* Output = new double[OutputCount];

	for (int i = 0; i < OutputCount; i++)
	{
		Output[i] = 0; //or getting weird number
	}

	//Calculate Weights * input;
	for (int i = 0; i < InputCount; i++)
	{
		for (int j = 0; j < OutputCount; j++)
		{
			if (i == InputCount - 1) // is bias
			{
				Output[j] += Weights[i][j];
			}
			else
			{
				Output[j] += Weights[i][j] * _Input[i];
			}
		}

		// Apply Activation Function
		for (int i = 0; i < OutputCount; i++)
		{
			Output[i] = ReLU(Output[i]);
		}
	}

	return Output;
}

NeuralSection::~NeuralSection()
{
}


double NeuralSection::ReLU(double x)
{
	if (x >= 0)
		return x;
	else
		return x / 20;
}

void NeuralSection::Mutate(double Mutationpropability, double MutationAmount)
{
	for (int i = 0; i < InputCount; i++)
	{
		for (int j = 0; j < OutputCount; j++)
		{
			if (randomizer->NextDouble() < Mutationpropability)
			{
				Weights[i][j] = randomizer->NextDouble() * (MutationAmount * 2.0) - MutationAmount;
			}
		}
	}
}
