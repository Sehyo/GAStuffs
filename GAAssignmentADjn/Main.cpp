#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Genome.h"
#include "Data.h"
#include <vector>
#include <algorithm>

#define GENOMECOUNT 100
#define CYCLES 99999999999999
#define ELITISM FALSE // Don't use "true" to maintain portability between compilers.
#define TRUE (1==1) // Don't use "true" to maintain portability between compilers.
#define FALSE (1==0)
#define BATTLE_ROYALE_SIZE 10

Genome& getBestGenome(std::vector<Genome>&);
std::vector<int> battleRoyale(std::vector<Genome>&);
std::vector<Genome> evolveGenomes(std::vector<Genome>&);

int main()
{
	Data data;
	srand(time(NULL));
	std::vector<Genome> genomes;
	genomes.reserve(GENOMECOUNT); // Reserve memory for genes.
	std::cout << "Creating genomes" << std::endl;
	for(int i = 0; i < GENOMECOUNT; i++) genomes.push_back(Genome(&data)); // Populate genome pool
	for(int i = 0; i < CYCLES; i++)
	{
		genomes = evolveGenomes(genomes);
		if(i % 1000 == 0)
		{
			std::cout << "Completed Cycle: " << i << std::endl;
			std::cout << "Candidate Solution: " << std::endl;
			getBestGenome(genomes).printFunction();
			std::cout << "Fitness: " << getBestGenome(genomes).getFitness() << std::endl;
		}
	}
	getBestGenome(genomes).printFunction();
	do{} while (true);
	return 0;
}

std::vector<Genome> evolveGenomes(std::vector<Genome>& genomes)
{
	std::vector<Genome> spoiledKids;
	spoiledKids.reserve(GENOMECOUNT);
	if(ELITISM) spoiledKids.push_back(getBestGenome(genomes));
	while(spoiledKids.size() < GENOMECOUNT)
	{
		std::vector<int> candidates = battleRoyale(genomes);
		spoiledKids.push_back(genomes.at(candidates.at(0)).crossover(genomes.at(candidates.at(1))));
		spoiledKids.at(spoiledKids.size()-1).mutate();
	}
	return spoiledKids;
}

Genome& getBestGenome(std::vector<Genome>& genomes)
{
	Genome* currentBest = &genomes.at(0);
	for(int i = 1; i < genomes.size(); i++)
		if(genomes.at(i).getFitness() < currentBest->getFitness())
			currentBest = &genomes.at(i);
	return *currentBest;
}

std::vector<int> battleRoyale(std::vector<Genome>& genomes)
{
	std::vector<int> battleRoyale;
	battleRoyale.reserve(BATTLE_ROYALE_SIZE);
	int candidateGenome;
	int candidateGenomeTwo;
	for(int i = 0; i < BATTLE_ROYALE_SIZE; i++)
	{
		int randId = rand() % genomes.size();
		if(i == 0) candidateGenome = randId;
		if(i == 1) candidateGenomeTwo = randId;
		battleRoyale.push_back(randId);
		if(i > 1)
		{
			if(genomes.at(randId) < genomes.at(candidateGenome) && randId != candidateGenomeTwo) candidateGenome = randId;
			if(genomes.at(randId) < genomes.at(candidateGenomeTwo) && randId != candidateGenome) candidateGenomeTwo = randId;
		}
	}
	std::vector<int> candidates;
	candidates.push_back(candidateGenome);
	candidates.push_back(candidateGenomeTwo);
	return candidates;
}