#include "Vec2.h"

Vec2::Vec2()
{
    x=y=0;
}


Vec2::Vec2(float a, int b)
{
    x=a;
    y=b;
}

float Vec2::dotProduct(const Vec2& vec2)
{
    return(x*vec2.x+y*vec2.y);
}
Vec2 Vec2::crossProduct(const Vec2& vec2)
{
    return Vec2();
}
float Vec2::lenght()
{
    return sqrt(x*x + y*y);
}

float Vec2::lengthSquared()
{
    float len = lenght();
    return len*len;
}
void Vec2::normalize()
{
    float len = lenght();
    if(len!=0)
    {
        x/=len;
        y/=len;
    }
}
void Vec2::inverse()
{
    x=1/x;
    y=1/y;
}

void Vec2::change(float a, float b)
{
    x=a;
    y=b;
}
void Vec2::change(Vec2 vec2)
{
    x=vec2.x;
    y=vec2.y;
}
void Vec2::changeX(float a)
{
    x=a;
}
void Vec2::changeY(float b)
{
    y=b;
}

Vec2 Vec2::operator+(const Vec2& vec2)
{
    return Vec2(x+vec2.x,y+vec2.y);
}
Vec2 Vec2::operator-(const Vec2& vec2)
{
    return Vec2(x-vec2.x,y-vec2.y);
}
Vec2 Vec2::operator*(float num)
{
    return Vec2(x*num,y*num);
}
Vec2 Vec2::operator/(float num)
{
    return Vec2(x/num,y/num);
}

Vec2& Vec2::operator+=(const Vec2& vec2)
{
    x+=vec2.x;
    y+=vec2.y;
    return *this;
}
Vec2& Vec2::operator-=(const Vec2& vec2)
{
    x-=vec2.x;
    y-=vec2.y;
    return *this;
}
Vec2& Vec2::operator*=(float num)
{
    x*=num;
    y*=num;
    return *this;
}
Vec2& Vec2::operator/=(float num)
{
    if(num==0)
        return *this;
    x/=num;
    y/=num;
    return *this;
}

bool Vec2::operator==(const Vec2 vec2)
{
    return (x==vec2.x && y==vec2.y);
}
bool Vec2::operator!=(const Vec2 vec2)
{
    return !(*this==vec2);
}

std::ostream& operator<<(std::ostream& out, const Vec2 vec)
{
    out << vec.x << " "<< vec.y << std::endl;
    return out;
}


