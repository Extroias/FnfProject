#include "Time.h"
std::shared_mutex Time::timeMutex;
float Time::_delta = 0;
std::chrono::duration<double> Time::_deltad;
milliseconds Time::_now;

milliseconds Time::now()
{
	std::shared_lock lock(timeMutex);
	return _now;
}

float Time::delta()
{
	std::shared_lock lock(timeMutex);
	return _delta;
}

double Time::deltad()
{
	std::shared_lock lock(timeMutex);
	return _deltad.count();
}

std::chrono::duration<double> Time::deltadur()
{
	std::shared_lock lock(timeMutex);
	return _deltad;
}