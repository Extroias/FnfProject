
#ifndef Transform_H
#define Transform_H

#include <mutex>

#include "Util/Shapes.h"

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
	Vector2 scale;
	float rotation = 0;
};
#endif //Transform_H	


