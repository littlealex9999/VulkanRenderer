#pragma once

#include <chrono>

class Stopwatch
{
public:
	std::chrono::high_resolution_clock::time_point begin;
	std::chrono::high_resolution_clock::time_point end;

	void Start()
	{
		if (!runOnce) runOnce = true;
		begin = std::chrono::high_resolution_clock::now();
	}

	void Stop()
	{
		end = std::chrono::high_resolution_clock::now();
	}

	double Current()
	{
		if (runOnce) {
			if (running) {
				return std::chrono::duration<double, std::chrono::seconds::period>(end - begin).count();
			} else {
				return std::chrono::duration<double, std::chrono::seconds::period>(std::chrono::high_resolution_clock::now() - begin).count();
			}
		}

		throw std::runtime_error("Stopwatch is not running. Start the stopwatch to get the current time");
	}

private:
	bool runOnce = false;
	bool running = false;
};