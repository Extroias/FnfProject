#ifndef Time_H
#define Time_H

#include <shared_mutex>
#include "RendererThread.h"

using milliseconds = std::chrono::duration<double, std::milli>;

class Time
{
private:
	static std::shared_mutex timeMutex;

	static std::chrono::duration<double>  _deltad; //Time between frames in seconds, double
	static float _delta; //Time between frames in seconds, float
	static milliseconds _now; //Time at the start of the frame

public:

	static std::chrono::duration<double> deltadur(); //Time between frames in duration
	static double deltad(); //Time between frames in seconds, double
	static float delta(); //Time between frames in seconds, float
	static milliseconds now(); //Time at the start of the frame

	friend void RendererThread::SetTimings();
};

#endif //Time_H	

