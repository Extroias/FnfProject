#ifndef UpdateThread_H
#define UpdateThread_H

#include "InputThread.h"

class UpdateThread
{
public:
	UpdateThread();
	~UpdateThread();

	void ThreadTask();
	void Stop() {
		this->Quit = true;
		this->thread.join();
	}
private:
	std::thread thread;
	bool Quit;

	std::chrono::duration<double> delta;
	milliseconds now;

	void SetTimings();
};
#endif //UpdateThread_H	


