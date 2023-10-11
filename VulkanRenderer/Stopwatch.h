#pragma once

#include <chrono>

class Stopwatch
{
public:
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;

	void Start()
	{
		if (!runOnce) runOnce = true;
		start = std::chrono::high_resolution_clock::now();
	}

	void Stop()
	{
		end = std::chrono::high_resolution_clock::now();
	}

	std::chrono::high_resolution_clock::duration current()
	{
		if (runOnce) {
			if (running) {
				return end - start;
			} else {
				return std::chrono::high_resolution_clock::now() - start;
			}
		}
	}

	double toDouble(std::chrono::high_resolution_clock::duration duration)
	{
		return duration.count() / 1000000000.0;
	}

private:
	bool runOnce = false;
	bool running = false;
};