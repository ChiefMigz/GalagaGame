#pragma once
class Timer
{
private:
	static Timer* sIntance;

	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
};

