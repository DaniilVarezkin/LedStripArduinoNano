#include "Perlin2D.h"

namespace Perlin {

	float topLeftGradient[2];
	float topRightGradient[2];
	float bottomLeftGradient[2];
	float bottomRightGradient[2];
	
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

		SetPseudoRandomGradientVector(left, top, topLeftGradient);
		SetPseudoRandomGradientVector(left + 1, top, topRightGradient);
		SetPseudoRandomGradientVector(left, top + 1, bottomLeftGradient);
		SetPseudoRandomGradientVector(left + 1, top + 1, bottomRightGradient);

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

	void setVectorCoord(float vector[2], float x, float y){
		vector[0] = x;
		vector[1] = y;
	}

	void Perlin2D::SetPseudoRandomGradientVector(int x, int y, float vector[2])
	{
		int v = (x * 31 + y * 37) & (PER_TABLE_SIZE - 1);
		v = permutationTable[v] & 7; // Используем 8 возможных направлений

		static const float gradients[8][2] = {
			{1, 0}, {-1, 0}, {0, 1}, {0, -1},
			{0.707f, 0.707f}, {-0.707f, 0.707f}, {0.707f, -0.707f}, {-0.707f, -0.707f}
		};
		vector[0] = gradients[v][0];
		vector[1] = gradients[v][1];
	}

	float Perlin2D::Dot(const float* a, const float* b)
	{
		return a[0] * b[0] + a[1] * b[1];
	}

	Perlin2D::~Perlin2D()
	{

	}
}