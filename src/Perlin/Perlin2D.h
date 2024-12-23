#pragma once
#include <math.h>
#include <stdlib.h>
#include <Arduino.h>

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

		void SetPseudoRandomGradientVector(int x, int y, float vector[2]);

		static float Dot(const float* a, const float* b);

		~Perlin2D();
	private:

	};
	
}
