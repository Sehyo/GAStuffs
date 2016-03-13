#include "Genome.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <random>

typedef unsigned int uint;

#define MUTATION_RATE 2 // SET this somewhere between 0 - 100;
#define MAX_NUMBER 5001 // Maximum number for a coefficient at initialisation.
#define BINARY_CROSS 0
#define GAUSSIAN_DEVIATION 1

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
	Genome::variableMutationRate = MUTATION_RATE;
	evaluateFitness();
}

void Genome::evaluateFitness()
{							  
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

double Genome::gaussian()
{
	std::normal_distribution<double> gaussian(0, GAUSSIAN_DEVIATION);
	return gaussian(mt);
}

double Genome::randomCoValue()
{
	std::uniform_real_distribution<double> dist(MAX_NUMBER * -1, MAX_NUMBER);
	return dist(mt);
}

void Genome::mutate()
{

	for(int i = 0; i < genes.size(); i++)
		if(randomInt(0,100) < variableMutationRate) genes.at(i) += gaussian();
	evaluateFitness();
}

Genome Genome::crossover(Genome& otherGenome)
{	

	Genome loveChild(data);
	if(BINARY_CROSS == 1)
	{
		typedef union
		{
			double value;
			char bits[sizeof(double)];
		} Bits;

		Bits a1, b1, c1, d1, e1, f1;
		Bits a2, b2, c2, d2, e2, f2;
		Bits a3, b3, c3, d3, e3, f3;
		Bits temp;
		a1.value = genes.at(0); b1.value = genes.at(1); c1.value = genes.at(2); d1.value = genes.at(3); e1.value = genes.at(4); f1.value = genes.at(5);
		a2.value = otherGenome.genes.at(0); b2.value = otherGenome.genes.at(1); c2.value = otherGenome.genes.at(2); d2.value = otherGenome.genes.at(3); e2.value = otherGenome.genes.at(4); f2.value = otherGenome.genes.at(5);

		int crossPoint = randomInt(0, sizeof(double)*6);

		for(int i = 0; i < sizeof(double) * 6; i++)
		{
				switch(int(i / sizeof(double))) // Find which Gene we are using.
				{
					case 0:
						if(i < crossPoint)	a3.bits[i % sizeof(double)] = a1.bits[i % sizeof(double)];
						else a3.bits[i % sizeof(double)] = a2.bits[i % sizeof(double)];
						break;
					case 1:
						if(i < crossPoint)	b3.bits[i % sizeof(double)] = b1.bits[i % sizeof(double)];
						else b3.bits[i % sizeof(double)] = b2.bits[i % sizeof(double)];
						break;
					case 2:
						if(i < crossPoint)	c3.bits[i % sizeof(double)] = c1.bits[i % sizeof(double)];
						else c3.bits[i % sizeof(double)] = c2.bits[i % sizeof(double)];
						break;
					case 3:
						if(i < crossPoint)	d3.bits[i % sizeof(double)] = d1.bits[i % sizeof(double)];
						else d3.bits[i % sizeof(double)] = d2.bits[i % sizeof(double)];
						break;
					case 4:
						if(i < crossPoint)	e3.bits[i % sizeof(double)] = e1.bits[i % sizeof(double)];
						else e3.bits[i % sizeof(double)] = e2.bits[i % sizeof(double)];
						break;
					case 5:
						if(i < crossPoint)	f3.bits[i % sizeof(double)] = f1.bits[i % sizeof(double)];
						else f3.bits[i % sizeof(double)] = f2.bits[i % sizeof(double)];
						break;
				}
		}

		loveChild.genes.at(0) = a3.value;
		loveChild.genes.at(1) = b3.value;
		loveChild.genes.at(2) = c3.value;
		loveChild.genes.at(3) = d3.value;
		loveChild.genes.at(4) = e3.value;
		loveChild.genes.at(5) = f3.value;
	}
	else
	{
		for(int i = 0; i < genes.size(); i++)
		{
			if(randomInt(0,100) < 50) loveChild.genes.at(i) = genes.at(i);
			else loveChild.genes.at(i) = otherGenome.genes.at(i);
		}
	}
	loveChild.evaluateFitness();
	return loveChild;	
}