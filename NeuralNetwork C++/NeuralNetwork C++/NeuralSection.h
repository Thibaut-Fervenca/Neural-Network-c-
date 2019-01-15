#pragma once
#include "Random.h"
class NeuralSection
{
private :

	

	Random* randomizer;

	double** Weights;

	int InputCount;
	int OutputCount;

public:
	NeuralSection(uint32_t InputCount, uint32_t OutputCount,Random* Randomizer);
	NeuralSection(NeuralSection* Main);

	void Copy(NeuralSection* _ToCopy);


	std::string ToString();

	double* FeedForward(double* _Input);

	~NeuralSection();

	void Mutate(double Mutationpropability = 0.2, double MutationAmount = 2.0);

private:

	
	///https ://en.wikipedia.org/wiki/Activation_function
	double ReLU(double x);

	

};

