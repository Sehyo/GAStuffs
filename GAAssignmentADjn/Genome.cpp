#include "Genome.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

typedef unsigned int uint;

#define MUTATION_RATE 5 // SET this somewhere between 0 - 100;
#define MAX_NUMBER 100000 // Maximum number for a coefficient

void Genome::printFunction()
{
	std::cout << Genome::genes.at(0) << "+" << Genome::genes.at(1) << "*x+" << Genome::genes.at(2) << "*x^2+" << Genome::genes.at(3) << "*x^3+" << Genome::genes.at(4) << "*x^4+" << Genome::genes.at(5) << "*x^5" << std::endl;
}

Genome::Genome(Data* data)
{
	Genome::data = data;
	// We are working with a fifth order polynomial.
	for(int i = 0; i < 6; i++)
	{
		Genome::genes.push_back(rand() % MAX_NUMBER);
		if(rand() % 100 < 50) genes.at(i) *= -1;
	}
	evaluateFitness();
}

void Genome::evaluateFitness() // Smaller is better
{
	fitness = 0;
	for (int i = 0; i < 577; i++)
	{
		// Check distance between y to wanted y.
		double x = data->getX(i);
		double geneFx = genes.at(0) + genes.at(1)*x + genes.at(2)*x*x + genes.at(3)*x*x*x + genes.at(4)*x*x*x*x + genes.at(5)*x*x*x*x*x;
		// add difference between geneFx and y to fitness.
		fitness += std::abs(geneFx - data->getY(i));
	}
	fitness /= 577; // There are 577 data inputs in the text file.
	// Technically this doesn't matter since this will happen to all genes but I want to work with smaller numbers when I debug stuffs :)
}

double Genome::getFitness()
{
	return fitness;
}

void Genome::mutate()
{
	for(int i = 0; i < genes.size(); i++)
		if((rand() % 100) < MUTATION_RATE)
		{
			genes.at(i) = rand() % MAX_NUMBER;
			if(rand() % 100 < 50) genes.at(i) *= -1;
			evaluateFitness();
		}
}

Genome Genome::crossover(Genome& otherGenome)
{	
	Genome loveChild(data);
	for(int i = 0; i < genes.size(); i++)
	{
		if((rand() % 100) < 50) loveChild.genes.at(i) = genes.at(i);
		else loveChild.genes.at(i) = otherGenome.genes.at(i);
	}
	loveChild.evaluateFitness();
	return loveChild;	
}