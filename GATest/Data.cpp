#include "Data.h"
#include <fstream>
#include <string>
#include <iostream>  

Data::Data()
{
	std::ifstream data("..\\Debug\\data.txt");
	std::string line;
	for (int i = 0; std::getline(data, line); i++)
	{
		std::string xs = "", xy = "";

		bool addToXs = true;
		for (char& c : line)
		{
			if (c != ';' && addToXs) xs += c;
			else if (c != ';' && !addToXs) xy += c;
			if (c == ';') addToXs = !addToXs;
		}
		double x = ::atof(xs.c_str()), y = ::atof(xy.c_str());
		getX(i) = x;
		getY(i) = y;
	}
}

double& Data::getX(int i)
{
	return x[i];
}

double& Data::getY(int i)
{
	return y[i];
}