#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Genome.h"
#include "Data.h"
#include <vector>
#include <algorithm>

#define GENOMECOUNT 10
#define CYCLES 99999999999999
#define ELITISM FALSE // Don't use "true" to maintain portability between compilers.
#define TRUE (1==1) // Don't use "true" to maintain portability between compilers.
#define FALSE (1==0)
#define BATTLE_ROYALE_SIZE 5

Genome& getBestGenome(std::vector<Genome>&);
std::vector<int> battleRoyale(std::vector<Genome>&);
std::vector<Genome> evolveGenomes(std::vector<Genome>&);
int bestCandidate(std::vector<int>, std::vector<Genome>&);


int main()
{
	Data data;
	std::vector<Genome> genomes;
	genomes.reserve(GENOMECOUNT); // Reserve memory for genes.
	std::cout << "Creating genomes" << std::endl;
	for(int i = 0; i < GENOMECOUNT; i++) genomes.push_back(Genome(&data)); // Populate genome pool
	std::cout << "GENOME POOL CREATED" << std::endl;
	int x;
	//std::cin >> x;
	for(int i = 0; i < CYCLES; i++)
	{
		genomes = evolveGenomes(genomes);
		
		if(i % 10000 == 0)
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
	int candidateGenome, candidateGenomeTwo;
	for(;battleRoyale.size() < BATTLE_ROYALE_SIZE;)
	{
		int randId = rand() % genomes.size();
		while(std::find(battleRoyale.begin(), battleRoyale.end(), randId) != battleRoyale.end()) randId = rand() % genomes.size();
		battleRoyale.push_back(randId);
	}
	// Get Best Candidates...
	candidateGenome = battleRoyale.at(bestCandidate(battleRoyale, genomes));
	battleRoyale.erase(std::remove(battleRoyale.begin(), battleRoyale.end(), candidateGenome), battleRoyale.end());
	candidateGenomeTwo = battleRoyale.at(bestCandidate(battleRoyale, genomes));
	std::vector<int> candidates;
	candidates.push_back(candidateGenome);
	candidates.push_back(candidateGenomeTwo);
	return candidates;
}

int bestCandidate(std::vector<int> candidates, std::vector<Genome>& genomes)
{
	int bestCandidate = 0;
	for(int i = 1; i < candidates.size(); i++)
	{
		if(genomes.at(candidates.at(i)) < genomes.at(candidates.at(bestCandidate))) bestCandidate = i;
	}
	return bestCandidate;
}