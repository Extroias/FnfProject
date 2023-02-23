#ifndef SHAPES_H
#define SHAPES_H

#include <SDL.h>
#include <cmath>

struct Vector2int;
struct Vector2;
struct Rect;
typedef struct Vector2int
{
    public:

    int x=0,y=0;

    Vector2int();
    Vector2int(int x,int y);
    
    float Distance(Vector2int vector);
    float SquaredDistance(Vector2int vector);
    float magnitude();
    /*
    returns direction of Vector
    */
    Vector2 normalized();
    bool liesIn(Rect r);

    Vector2int operator+(Vector2int added);
    Vector2int operator-(Vector2int subtractor);
    Vector2int operator* (float multiplier);
    Vector2int operator/ (float divisor);
    Vector2int& operator+=(const Vector2int& added);
    Vector2int& operator-=(const Vector2int& subtractor);
    Vector2int& operator*=(float multiplier);
    Vector2int& operator/=(float divisor);
    bool operator== (Vector2int vec);
    operator Vector2() const;
    private: 
    float m = sqrtf(x* x + y* y);
    
}Vector2int;

typedef struct Vector2
{
    public:
    float x=0,y=0;

    Vector2();
    Vector2(float x,float y);


    float Distance(Vector2 vector);
    float SquaredDistance(Vector2 vector);
    float magnitude();
    /*
    returns direction of Vector
    */
    Vector2 normalized();
    bool liesIn(Rect r);

    Vector2 operator+(Vector2 added);
    Vector2 operator-(Vector2 subtractor);
    Vector2 operator* (float multiplier);
    Vector2 operator/ (float divisor);
    Vector2& operator+=(const Vector2& added);
    Vector2& operator-=(const Vector2& subtractor);
    Vector2& operator*=(float multiplier);
    Vector2& operator/=(float divisor);
    bool operator== (Vector2 vec);
    operator Vector2int() const;
    private: 
    float m = sqrt(x*x + y*y);
}Vector2;

typedef struct Color
{
    float r,g,b,a;

    Color();
    Color(float r, float g, float b, float a);

    Color Black(){return Color(0,0,0,255);}
    Color Blue(){return Color(0,0,255,255);}
    Color Cyan(){return Color(0,255,255,255);}
    Color Gray(){return Color(122,122,122,255);}
    Color Green(){return Color(0,255,0,255);}
    Color Magenta(){return Color(255,0,255,255);}
    Color Red(){return Color(255,0,0,255);}
    Color White(){return Color(255,255,255,255);}
    Color Yellow(){return Color(255,234.5f,4.08f,255);}

    bool operator== (Color color);
    SDL_Color toSDL(){
        return SDL_Color{(Uint8)r,(Uint8)g,(Uint8)b,(Uint8)a};
    }
}Color;
/**
 * A rectangle, with the origin at the upper left (floating point).
 */
typedef struct Rect
{
    Vector2 position;
    Vector2 size;

    Rect();
    Rect(Vector2 position,Vector2 size);

    Vector2 min(){return position-size/2;}
    Vector2 max(){return position+size/2;}
    //GPU_Rect ToSDLGPU();
    SDL_Rect ToSDLRect()
    {
        SDL_Rect rect;
        rect.x = position.x; rect.y = position.y; rect.w = size.x; rect.h = size.y;
        return rect;
    }

    bool operator== (Rect rect);
}Rect;

#endif //SHAPES_H
