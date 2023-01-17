
#ifndef Transform_H
#define Transform_H

#include <mutex>

#include "Shapes.h"

class Transform
{
public:
	Vector2 GetPosition();
	void SetPosition(Vector2 position);


	Vector2 GetScale();
	void SetScale(Vector2 Scale);


	float GetRotation();
	void SetRotation(float rotation);


private:
	Vector2 position;
	std::mutex posMutex;
	Vector2 scale;
	std::mutex scaleMutex;
	float rotation = 0;
	std::mutex rotationMutex;
};
#endif //Transform_H	


