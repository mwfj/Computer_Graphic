#include "Vector3f.hpp"

Vector3f::Vector3f(double x, double y, double z)
    :x_axis(x),y_axis(y),z_axis(z)
{
}

Vector3f::Vector3f(const Vector3f& other)
    :x_axis(other.x_axis),y_axis(other.y_axis),z_axis(other.z_axis)
{
}

Vector3f::~Vector3f()
{
}
Vector3f& Vector3f::operator=(const Vector3f& other){
    if (this != &other)
    {
        x_axis = other.x_axis;
        y_axis = other.y_axis;
        z_axis = other.z_axis;
    }
    return *this;
}
Vector3f Vector3f::operator-() const{
    return Vector3f(-x_axis,-y_axis,-z_axis);
}
Vector3f Vector3f::operator+(const Vector3f& other) const{
    return Vector3f(x_axis+other.x_axis, y_axis+other.y_axis, z_axis+other.z_axis);
}

Vector3f Vector3f::operator-(const Vector3f& other) const{
    return Vector3f(x_axis-other.x_axis, y_axis-other.y_axis, z_axis-other.z_axis);
}
Vector3f Vector3f::operator*(const Vector3f& other) const{
    return Vector3f(x_axis*other.x_axis, y_axis*other.y_axis, z_axis*other.z_axis);
}
Vector3f Vector3f::operator/(const Vector3f& other) const{
    return Vector3f(x_axis/other.x_axis, y_axis/other.y_axis, z_axis/other.z_axis);
}

bool Vector3f::operator==(const Vector3f& other) const{
    return (x_axis==other.x_axis && y_axis == other.y_axis && z_axis == other.z_axis);
}

bool Vector3f::operator!=(const Vector3f& other) const{
    return (x_axis!=other.x_axis && y_axis != other.y_axis && z_axis != other.z_axis);
}

const Vector3f& Vector3f::operator*=(float scale){
    x_axis *= scale;
    y_axis *= scale;
    z_axis *= scale;
    return *this;
}

const Vector3f& Vector3f::operator/=(float scale){
    if ( scale < 0.001 && scale > -0.001 ) {
        std::cout<<"scale too small in /=" <<std::endl;
    }else{
        x_axis /= scale;
        y_axis /= scale;
        z_axis /= scale;
    }
    return *this;
}

const Vector3f& Vector3f::operator+=(const Vector3f& other){
    x_axis += other.x_axis;
    y_axis += other.y_axis;
    z_axis += other.z_axis;
    return *this;
}

const Vector3f& Vector3f::operator-=(const Vector3f& other){
    x_axis -= other.x_axis;
    y_axis -= other.y_axis;
    z_axis -= other.z_axis;
    return *this;
}
