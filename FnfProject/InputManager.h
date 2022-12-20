#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include <vector>

class InputManager
{
public:
	InputManager();

	void TakeSnapshot();

private:

	const Uint8* states;
	int length;
	std::vector<std::vector<bool>>snapshots;

};

#endif //INPUTMANAGER_H	
