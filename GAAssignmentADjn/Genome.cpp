#include "Genome.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <random>

typedef unsigned int uint;

#define MUTATION_RATE 1 // SET this somewhere between 0 - 100;
#define MAX_NUMBER 500 // Maximum number for a coefficient

std::random_device Genome::rd;
std::mt19937 Genome::mt(rd());

void Genome::printFunction()
{
	std::cout << Genome::genes.at(0) << "+" << Genome::genes.at(1) << "*x+" << Genome::genes.at(2) << "*x^2+" << Genome::genes.at(3) << "*x^3+" << Genome::genes.at(4) << "*x^4+" << Genome::genes.at(5) << "*x^5" << std::endl;
}

Genome::Genome(Data* data)
{
	Genome::data = data;
	for(int i = 0; i < 6; i++)
	{
		Genome::genes.push_back(randomCoValue());
		if(randomInt(0,100) < 50) genes.at(i) *= -1;
	}
	evaluateFitness();
}

void Genome::evaluateFitness() // Need better function...
{							  // Allows the last coefficients to have big bias.
	fitness = 0;
	for (int i = 0; i < 577; i++)
	{
		double x = data->getX(i);double geneFx = genes.at(0) + genes.at(1)*x + genes.at(2)*std::pow(x,2) + genes.at(3)*std::pow(x, 3) + genes.at(4)*std::pow(x, 4) + genes.at(5)*std::pow(x, 5);
		fitness += std::abs(geneFx - data->getY(i));
	}
	fitness /= 577; // There are 577 data inputs in the text file.
	// Technically this doesn't matter since this will happen to all genomes
}

double Genome::getFitness()
{
	evaluateFitness();
	return fitness;
}

int Genome::randomInt(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

double Genome::randomCoValue()
{
	std::uniform_real_distribution<double> dist(MAX_NUMBER * -1, MAX_NUMBER);
	return dist(mt);
}

void Genome::mutate()
{
	
	for(int i = 0; i < genes.size(); i++)
		if(randomInt(0,100) < MUTATION_RATE)
		{
				genes.at(i) = randomCoValue();
				if(randomInt(0, 100) < 50) genes.at(i) *= -1;
		}
	evaluateFitness();
}

Genome Genome::crossover(Genome& otherGenome)
{	
	Genome loveChild(data);
	for(int i = 0; i < genes.size(); i++)
	{
			if(randomInt(0,100) < 50) loveChild.genes.at(i) = genes.at(i);
			else loveChild.genes.at(i) = otherGenome.genes.at(i);
	}
	loveChild.evaluateFitness();
	return loveChild;	
}