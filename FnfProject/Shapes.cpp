#include "Shapes.h"

//Vector2int Methods
Vector2int::Vector2int()
{
    x = 0;
    y = 0;
}
Vector2int::Vector2int(int x, int y)
{
    this->x = x;
    this->y = y;
}
float Vector2int::Distance(Vector2int vector)
{
    float x = vector.x - this->x;
    float y = vector.y - this->y;
    return std::sqrt(x*x + y*y);
}
float Vector2int::SquaredDistance(Vector2int vector)
{
    float x = vector.x - this->x;
    float y = vector.y - this->y;
    return x*x + y*y;
}
float Vector2int::magnitude()
{
    m = sqrtf(x * x + y * y);

    return m;
}
Vector2 Vector2int::normalized()
{
    m = magnitude();
    if (m == 0) {
        return Vector2int(0,0);
    }
    Vector2 temp(x / m, y / m);
    return temp;
}

bool Vector2int::liesIn(Rect r)
{
    return (x > r.position.x) && (x < r.position.x + r.size.x) && (y > r.position.y) && (y < r.position.y + r.size.y);
}

//Vector2int Operators
Vector2int Vector2int::operator+(Vector2int added)
{
    int x = this->x + added.x;
    int y = this->y + added.y;
    return Vector2int(x, y);
}
Vector2int Vector2int::operator-(Vector2int subtractor)
{
    int x = this->x - subtractor.x;
    int y = this->y - subtractor.y;
    return Vector2int(x, y);
}
Vector2int Vector2int::operator*(float multiplier)
{
    int x = this->x * multiplier;
    int y = this->y * multiplier;
    return Vector2int(x, y);
}
Vector2int Vector2int::operator/(float divisor)
{
    int x = this->x / divisor;
    int y = this->y / divisor;
    return Vector2int(x, y);
}
Vector2int& Vector2int::operator+=(const Vector2int& added)
{
    this->x += added.x;
    this->y += added.y;
    return *this;
}
Vector2int& Vector2int::operator-=(const Vector2int& subtractor)
{
    this->x -= subtractor.x;
    this->y -= subtractor.y;
    return *this;
}
Vector2int& Vector2int::operator/=(float divisor)
{
    this->x /= divisor;
    this->y /= divisor;
    return *this;
}
Vector2int& Vector2int::operator*=(float multiplier)
{
    this->x *= multiplier;
    this->y *= multiplier;
    return *this;
} 
bool Vector2int::operator==(Vector2int vec)
{
    if(this->x == vec.x && this->y == vec.y)
    {
        return true;
    }
    else return false;
}
Vector2int::operator Vector2() const
{
    return Vector2(x,y);
}






//Vector2 Methods
Vector2::Vector2()
{
    x = 0;
    y = 0;
}
Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}
float Vector2::magnitude()
{
    m = sqrt(x * x + y * y);

    return m;
}
float Vector2::Distance(Vector2 vector)
{
    float x = vector.x - this->x;
    float y = vector.y - this->y;
    return std::sqrt(x*x + y*y);
}
float Vector2::SquaredDistance(Vector2 vector)
{
    float x = vector.x - this->x;
    float y = vector.y - this->y;
    return x*x + y*y;
}
Vector2 Vector2::normalized()
{
    m = magnitude();
    if (m == 0) {
        return Vector2(0.f,0.f);
    }
    Vector2 temp(x / m, y / m);
    return temp;
}

bool Vector2::liesIn(Rect r)
{
    return !((x < r.min().x) || (y < r.min().y) || (x > r.max().x) || (y > r.max().y));
}

//Vector2 Operators
Vector2 Vector2::operator+(Vector2 added)
{
    float x = this->x + added.x;
    float y = this->y + added.y;
    return Vector2(x, y);
}
Vector2 Vector2::operator-(Vector2 subtractor)
{
    float x = this->x - subtractor.x;
    float y = this->y - subtractor.y;
    return Vector2(x, y);
}
Vector2 Vector2::operator*(float multiplier)
{
    float x = this->x * multiplier;
    float y = this->y * multiplier;
    return Vector2(x, y);
}
Vector2 Vector2::operator/(float divisor)
{
    float x = this->x / divisor;
    float y = this->y / divisor;
    return Vector2(x, y);
}
Vector2& Vector2::operator+=(const Vector2& added)
{
    this->x += added.x;
    this->y += added.y;
    return *this;
}
Vector2& Vector2::operator-=(const Vector2& subtractor)
{
    this->x -= subtractor.x;
    this->y -= subtractor.y;
    return *this;
}
Vector2& Vector2::operator/=(float divisor)
{
    this->x /= divisor;
    this->y /= divisor;
    return *this;
}Vector2& Vector2::operator*=(float multiplier)
{
    this->x *= multiplier;
    this->y *= multiplier;
    return *this;
}
bool Vector2::operator==(Vector2 vec)
{
    if(this->x == vec.x && this->y == vec.y)
    {
        return true;
    }
    else return false;
}
Vector2::operator Vector2int() const
{
 return Vector2int(x,y);
}


//Color Methods
Color::Color()
{
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}
Color::Color(float r, float g, float b, float a)
{
    this->r = r;
    this->b = b;
    this->g = g;
    this->a = a;
}
bool Color::operator==(Color color)
{
    if(r == color.r && b == color.b && g == color.g && a == color.a)
    {
        return true;
    }
    else return false;
}





//Rect Methods
Rect::Rect()
{
    position = Vector2();
    size = Vector2();
}
Rect::Rect(Vector2 position, Vector2 size)
{
    this->position = position;
    this->size = size;
}
//GPU_Rect Rect::ToSDLGPU()
//{
//    GPU_Rect sdlrect{position.x,position.y,size.x,size.y};
//    return sdlrect;
//}

bool Rect::operator==(Rect rect)
{
    if(position == rect.position && size == rect.size)
    {
        return true;
    }
    else return false;
}
