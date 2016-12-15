#pragma once

#include <iostream>

class Simulation;

class Algorithm
{
	public:
		virtual void solve(Simulation*) = 0;
};
