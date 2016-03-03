#include "Data.h"
#include <vector>

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
private:
	std::vector<double> genes;
	double fitness;
	Data* data;
};