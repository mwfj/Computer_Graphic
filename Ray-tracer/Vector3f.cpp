#include "Vector3f.hpp"
#include <math.h>
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
Vector3f Vector3f::cross_product(const Vector3f& other){
    double tempx = ( y_axis * other.getZ() ) - (other.getY()*z_axis);;
    double tempy = -(x_axis*other.getZ() - other.getX()*z_axis );; 
    double tempz = ( x_axis*other.getY() ) - ( other.getX()*y_axis);

    return Vector3f(tempx,tempy,tempz);
}
double Vector3f::modulus(){
    double m_ = sqrt( x_axis*x_axis +y_axis*y_axis+z_axis*z_axis );
    return m_;
}
double Vector3f::dot(const Vector3f& other){
    double sum = x_axis*other.getX() + y_axis* other.getY() + z_axis*other.getZ();
    return sum;
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
Vector3f Vector3f::operator*(double d_) const{
    return Vector3f(x_axis*d_,y_axis*d_,z_axis*d_);
}
Vector3f Vector3f::operator/(const Vector3f& other) const{
    return Vector3f(x_axis/other.x_axis, y_axis/other.y_axis, z_axis/other.z_axis);
}

Vector3f Vector3f::operator/(double d_) const{
    return Vector3f(x_axis/d_, y_axis/d_, z_axis/d_);
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
