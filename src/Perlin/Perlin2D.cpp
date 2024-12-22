#include "Perlin2D.h"

namespace Perlin {

	
	Perlin2D::Perlin2D()
	{
		for (int i = 0; i < PER_TABLE_SIZE; i++) {
			permutationTable[i] = rand() % 255; 
		}
	}

	float Perlin2D::fNoise(float fx, float fy)
	{
		int left = (int)floor(fx);
		int top = (int)floor(fy);

		float pointInQuadX = fx - left;
		float pointInQuadY = fy - top;

		float* topLeftGradient = GetPseudoRandomGradientVector(left, top);
		float* topRightGradient = GetPseudoRandomGradientVector(left + 1, top);
		float* bottomLeftGradient = GetPseudoRandomGradientVector(left, top + 1);
		float* bottomRightGradient = GetPseudoRandomGradientVector(left + 1, top + 1);

		float distanceToTopLeft[2] = { pointInQuadX, pointInQuadY };
		float distanceToTopRight[2] = { pointInQuadX - 1, pointInQuadY };
		float distanceToBottomLeft[2] = { pointInQuadX, pointInQuadY - 1 };
		float distanceToBottomRight[2] = { pointInQuadX - 1, pointInQuadY - 1 };

		float tx1 = Dot(distanceToTopLeft, topLeftGradient);
		float tx2 = Dot(distanceToTopRight, topRightGradient);
		float bx1 = Dot(distanceToBottomLeft, bottomLeftGradient);
		float bx2 = Dot(distanceToBottomRight, bottomRightGradient);

		pointInQuadX = qunticCurve(pointInQuadX);
		pointInQuadY = qunticCurve(pointInQuadY);

		float tx = lerp(tx1, tx2, pointInQuadX);
		float bx = lerp(bx1, bx2, pointInQuadX);
		float tb = lerp(tx, bx, pointInQuadY);


		delete[] topLeftGradient;
		delete[] topRightGradient;
		delete[] bottomLeftGradient;
		delete[] bottomRightGradient;


		return tb;
	}

	float Perlin2D::lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	float Perlin2D::qunticCurve(float t)
	{
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	float* Perlin2D::GetPseudoRandomGradientVector(int x, int y)
	{
		int v = (int)(((x * 1836311903) ^ ((y * 2971215073) + 4807526976)) & (PER_TABLE_SIZE - 1));
		v = permutationTable[v] & 7;  // Используем 8 возможных направлений

		switch (v)
		{
			case 0: return new float[2] { 1, 0 };
			case 1: return new float[2] { -1, 0 };
			case 2: return new float[2] { 0, 1 };
			case 3: return new float[2] { 0, -1 };
			case 4: return new float[2] { 1, 1 };
			case 5: return new float[2] { -1, 1 };
			case 6: return new float[2] { 1, -1 };
			case 7: return new float[2] { -1, -1 };
			default: return new float[2] { 0, 0 }; // Безопасность
		}
	}

	float Perlin2D::Dot(float a[], float b[])
	{
		return a[0] * b[0] + a[1] * b[1];
	}

	Perlin2D::~Perlin2D()
	{

	}
}