#include "Vector2f.hpp"

Vector2f::Vector2f(double x, double y)
    :x_axis(x),y_axis(y)
{}

Vector2f::Vector2f(const Vector2f& other)
    :x_axis(other.x_axis),
    y_axis(other.y_axis)
{}

Vector2f& Vector2f::operator=(const Vector2f& other){
            
    if (this != &other)
    {
        x_axis = other.x_axis;
        y_axis = other.y_axis;
    }
    return *this;
}

Vector2f Vector2f::operator+(const Vector2f& other) const{
    return Vector2f(x_axis + other.x_axis, y_axis + other.y_axis);
}

Vector2f Vector2f::operator-(const Vector2f& other) const{
    return Vector2f(x_axis - other.x_axis, y_axis - other.y_axis);
}

Vector2f Vector2f::operator*(const Vector2f& other) const{
    return Vector2f(x_axis * other.x_axis, y_axis * other.y_axis);
}
Vector2f Vector2f::operator/(const Vector2f& other) const{
    return Vector2f(x_axis / other.x_axis, y_axis / other.y_axis);
}
bool Vector2f::operator==(const Vector2f& other) const{
    return(x_axis == other.x_axis && y_axis == other.y_axis);
}

bool Vector2f::operator!=(const Vector2f& other) const{
    return(x_axis != other.x_axis && y_axis != other.y_axis);
}

const Vector2f& Vector2f::operator*=(float scale){
    x_axis *= scale;
    y_axis *= scale;
    return *this;
}

const Vector2f& Vector2f::operator/=(float scale){
     if ( scale < 0.001 && scale > -0.001 ) {
        std::cout<<"scale too small in /=" <<std::endl;
    }else{
        x_axis /= scale;
        y_axis /= scale;
    }
    return *this;
}

const Vector2f& Vector2f::operator+=(const Vector2f& other){
    x_axis += other.x_axis;
    y_axis += other.y_axis;
    return *this;
}

const Vector2f& Vector2f::operator-=(const Vector2f& other){
    x_axis -= other.x_axis;
    y_axis -= other.y_axis;
    return *this;
}