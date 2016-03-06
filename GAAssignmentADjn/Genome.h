#include "Data.h"
#include <vector>
#include <random>

class Genome
{
public:
	Genome crossover(Genome&);
	Genome(Data*);
	void evaluateFitness();
	double getFitness();
	bool operator<(const Genome &otherGenome) const { return fitness < otherGenome.fitness; }
	void printFunction();
	void mutate();
	std::vector<double> genes;
	static std::mt19937 mt;
	static std::random_device rd;
	double randomCoValue();
	int randomInt(int, int);
	Data* data;
private:
	int currentCoefficient = 0;
	double fitness;
	
};