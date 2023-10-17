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

	double Current()
	{
		if (runOnce) {
			if (running) {
				return std::chrono::duration<double, std::chrono::seconds::period>(end - start).count();
			} else {
				return std::chrono::duration<double, std::chrono::seconds::period>(std::chrono::high_resolution_clock::now() - start).count();
			}
		}
	}

private:
	bool runOnce = false;
	bool running = false;
};