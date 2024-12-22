#pragma once
#include <math.h>
#include <stdlib.h>

#ifndef PER_TABLE_SIZE
	#define PER_TABLE_SIZE 32
#endif // !PER_TABLE_SIZE


namespace Perlin {
	class Perlin2D
	{
	private:
		char permutationTable[PER_TABLE_SIZE];
	public:
		Perlin2D();

		float fNoise(float fx, float fy);

		static float lerp(float a, float b, float t);

		static float qunticCurve(float t);

		float* GetPseudoRandomGradientVector(int x, int y);

		static float Dot(float a[], float b[]);

		~Perlin2D();
	private:

	};
	
}
