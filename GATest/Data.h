#pragma once

class Data
{
public:
	Data();
	double& getX(int i);
	double& getY(int i);
private:
	double x[577];
	double y[577];
};