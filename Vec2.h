#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <cmath>

class Vec2
{
    public:
        float x,y;

        Vec2();
        Vec2(float a, int b);

        float dotProduct(const Vec2& vec2);
        Vec2 crossProduct(const Vec2& vec2);
        float lenght();
        float lengthSquared();
        void normalize();
        void inverse();

        void change(float a, float b);
        void change(Vec2 vec2);
        void changeX(float a);
        void changeY(float b);

        Vec2 operator+(const Vec2& vec2);
        Vec2 operator-(const Vec2& vec2);
        Vec2 operator*(float num);
        Vec2 operator/(float num);

        Vec2& operator+=(const Vec2& vec2);
        Vec2& operator-=(const Vec2& vec2);
        Vec2& operator*=(float num);
        Vec2& operator/=(float num);

        bool operator==(const Vec2 vec2);
        bool operator!=(const Vec2 vec2);

        friend std::ostream& operator<<(std::ostream& out, const Vec2 vec);

    protected:
    private:
};

#endif // VEC2_H
