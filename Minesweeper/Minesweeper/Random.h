#pragma once
#include <random>

class Random
{
	// One instance of the x variable, and all instances SHARE this variable
	//static variables/functions exist for the lifetime of your program
	static std::mt19937 random;

public:

	/*static int x;
	int y, z;*/

	//One and only one of this function (because we are using static
	static int Int(int min, int max);
	static float Float(float min, float max);

};

