#pragma once
#include "Math.h"
#include <vector>

class BezierPath
{
public:
	BezierPath();
	~BezierPath();

	void addCurve(BezierCurve curve, int samples);

	void sample(std::vector<Vector2>* sampledPath);
private:
	std::vector<BezierCurve> mCurves;
	std::vector<int> mSamples;
};

