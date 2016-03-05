#include "Genome.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <random>

typedef unsigned int uint;

#define MUTATION_RATE 5 // SET this somewhere between 0 - 100;
#define MAX_NUMBER 1000000 // Maximum number for a coefficient

std::random_device Genome::rd;
std::mt19937 Genome::mt(rd());

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
		Genome::genes.push_back(randomCoValue());
		if(rand() % 100 < 50) genes.at(i) *= -1;
		if(genes.at(i) == 32767 || genes.at(i) == -32767)
		{
			int x = 0;
	//		std::cout << "MAGIC NUMBER FOUND IN CONSTRUCTOR" << std::endl;
		//	std::cin >> x;
		}
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
		//std::cout << "A: " << genes.at(0) << " B: " << genes.at(1) << " C: " << genes.at(2) << " D: " << genes.at(3) << " E: " << genes.at(4) << " F: " << genes.at(5) << std::endl;
		double geneFx = genes.at(0) + genes.at(1)*x + genes.at(2)*std::pow(x,2) + genes.at(3)*std::pow(x, 3) + genes.at(4)*std::pow(x, 4) + genes.at(5)*std::pow(x, 5);
		//double geneFx = genes.at(0) + genes.at(1)*x + genes.at(2)*x*x + genes.at(3)*x*x*x + genes.at(4)*x*x*x*x + genes.at(5)*x*x*x*x*x;
		//std::cout << "X: " << x << std::endl << "Gene Fx: " << geneFx << std::endl << "Wanted Fx: " << data->getY(i) << std::endl;
		// add difference between geneFx and y to fitness.
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

double Genome::randomCoValue()
{
	std::uniform_real_distribution<double> dist(MAX_NUMBER * -1, MAX_NUMBER);
	return dist(mt);
}

void Genome::mutate()
{
	
	for(int i = 0; i < genes.size(); i++)
		if((rand() % 100) < MUTATION_RATE)
		{
			genes.at(i) = randomCoValue();
			if(rand() % 100 < 50) genes.at(i) *= -1;
			if(genes.at(i) == 32767 || genes.at(i) == -32767)
			{
				int x = 0;
			//	std::cout << "MAGIC NUMBER FOUND IN MUTATE" << std::endl;
			//	std::cin >> x;
			}
		}
	evaluateFitness();
}

Genome Genome::crossover(Genome& otherGenome)
{	
	Genome loveChild(data);
	for(int i = 0; i < genes.size(); i++)
	{
		if((rand() % 100) < 50) loveChild.genes.at(i) = genes.at(i);
		else loveChild.genes.at(i) = otherGenome.genes.at(i);
		if(loveChild.genes.at(i) == 32767 || genes.at(i) == -32767)
		{
			int x = 0;
			//std::cout << "MAGIC NUMBER FOUND IN CROSSOVER" << std::endl;
			//std::cin >> x;
		}
	}
	loveChild.getFitness();
	return loveChild;	
}