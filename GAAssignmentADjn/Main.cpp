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
int bestCandidate(std::vector<int>, std::vector<Genome>&);

int main()
{
	Data data;
	Genome genomerino(&data);
	std::vector<Genome> genomes;
	genomes.reserve(GENOMECOUNT); // Reserve memory for genes.
	std::cout << "Creating genomes" << std::endl;
	for(int i = 0; i < GENOMECOUNT; i++) genomes.push_back(Genome(&data)); // Populate genome pool
	std::cout << "GENOME POOL CREATED" << std::endl;
	for(int i = 0; i < CYCLES; i++)
	{
		genomes = evolveGenomes(genomes);
		if(i % 1000 == 0)
		{
			getBestGenome(genomes).printFunction();
			std::cout << getBestGenome(genomes).getFitness() << std::endl;
		}
	}
	getBestGenome(genomes).printFunction();
	do{} while (true);
	return 0;
}

std::vector<Genome> evolveGenomes(std::vector<Genome>& genomes) // Maybe work? -- Check
{
	std::vector<Genome> spoiledKids;
	spoiledKids.reserve(GENOMECOUNT);
	if(ELITISM) spoiledKids.push_back(getBestGenome(genomes));
	while(spoiledKids.size() < GENOMECOUNT)
	{
		std::vector<int> candidates = battleRoyale(genomes);
		spoiledKids.push_back(genomes.at(candidates.at(0)).crossover(genomes.at(candidates.at(1))));
	}
	for(int i = 0; i < spoiledKids.size(); i++) spoiledKids.at(i).mutate();
	return spoiledKids;
}

Genome& getBestGenome(std::vector<Genome>& genomes) // Definitely works.
{
	Genome* currentBest = &genomes.at(0);
	for(int i = 1; i < genomes.size(); i++)
		if(genomes.at(i).getFitness() < currentBest->getFitness())
			currentBest = &genomes.at(i);
	return *currentBest;
}

std::vector<int> battleRoyale(std::vector<Genome>& genomes) // Not sure if works..
{
	std::vector<int> battleRoyale; // Vector of indices of genomes in genomes argument.
	battleRoyale.reserve(BATTLE_ROYALE_SIZE);
	int candidateGenome, candidateGenomeTwo;
	for(;battleRoyale.size() < BATTLE_ROYALE_SIZE;)
	{
		int randId = genomes.at(0).randomInt(0, genomes.size()-1);
		while(std::find(battleRoyale.begin(), battleRoyale.end(), randId) != battleRoyale.end()) randId = genomes.at(0).randomInt(0, genomes.size()-1);
		battleRoyale.push_back(randId);
	}
	// Get Best Candidates...
	candidateGenome = battleRoyale.at(bestCandidate(battleRoyale, genomes)); // candidateGenome = index of bestCandidate in genomes.
	battleRoyale.erase(std::remove(battleRoyale.begin(), battleRoyale.end(), candidateGenome), battleRoyale.end()); // Remove best candidate
	candidateGenomeTwo = battleRoyale.at(bestCandidate(battleRoyale, genomes)); // candidateGenomeTwo = 2nd best candidate in tournament.
	std::vector<int> candidates;
	candidates.push_back(candidateGenome);
	candidates.push_back(candidateGenomeTwo);
	return candidates;
}

int bestCandidate(std::vector<int> candidates, std::vector<Genome>& genomes) // Returns best candidate in genomes in terms of position in candidates rather than position in genomes.
{
	int bestCandidate = 0;
	for(int i = 1; i < candidates.size(); i++)
	{
		if(genomes.at(candidates.at(i)) < genomes.at(candidates.at(bestCandidate))) bestCandidate = i;
	}
	return bestCandidate;
}