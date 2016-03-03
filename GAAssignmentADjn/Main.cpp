#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Genome.h"
#include "Data.h"
#include <vector>
#include <algorithm>

#define GENOMECOUNT 1000
#define CYCLES 10000
#define ELITISM TRUE // Don't use "true" to maintain portability between compilers.
#define TRUE (1==1) // Don't use "true" to maintain portability between compilers.
#define BATTLE_ROYALE_SIZE 10

Genome& getBestGenome(std::vector<Genome>&);
Genome battleRoyale(std::vector<Genome>&);
std::vector<Genome> evolveGenomes(std::vector<Genome>&);

int main()
{
	Data data;
	srand(time(NULL));
	std::vector<Genome> genomes;
	genomes.reserve(GENOMECOUNT); // Reserve memory for genes.
	std::cout << "Creating genomes" << std::endl;
	int x = 0;
	for (int i = 0; i < GENOMECOUNT; i++) genomes.push_back(Genome(&data)); // Populate genome pool
	for(int i = 0; i < CYCLES; i++)
	{
		genomes = evolveGenomes(genomes);
		std::cout << "Completed Cycle: " << i << std::endl;
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
		Genome billy = battleRoyale(genomes);
		Genome theKid = battleRoyale(genomes);
		spoiledKids.push_back(billy.crossover(theKid));
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

Genome battleRoyale(std::vector<Genome>& genomes)
{
	std::vector<int> battleRoyale;
	battleRoyale.reserve(BATTLE_ROYALE_SIZE);
	int bestGenome;
	for(int i = 0; i < BATTLE_ROYALE_SIZE; i++)
	{
		int randId = rand() % genomes.size();
		if(i == 0) bestGenome = randId;
		battleRoyale.push_back(randId);
		if(genomes.at(randId) < genomes.at(bestGenome)) bestGenome = randId;
	}
	return genomes.at(bestGenome);
}