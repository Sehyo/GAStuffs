#pragma once
#include <random>

static class Random
{
private:
	static std::mt19937 mt;
public:
	static void seed(uint32_t seed);
	static uint32_t get();
};