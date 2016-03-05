#include "Data.h"
#include <vector>
#include <random>

class Genome
{
public:
	Genome crossover(Genome& otherGenome);
	Genome(Data* data);
	void evaluateFitness();
	double getFitness();
	bool operator<(const Genome &otherGenome) const { return fitness < otherGenome.fitness; }
	void printFunction();
	void mutate();
	std::vector<double> genes;
	static std::mt19937 mt;
	static std::random_device rd;
	double randomCoValue();
private:
	
	double fitness;
	Data* data;
};