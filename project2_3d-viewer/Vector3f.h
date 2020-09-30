#ifndef VECTOR3F__H
#define VECTOR3F__H
/**
 * @author Wufangjie Ma
 * This Class is for store the two-dimensional data
 **/
#include<iostream>
class Vector3f
{
private:
    double x_axis;
    double y_axis;
    double z_axis;
public:
    Vector3f(double x, double y, double z);
    Vector3f(const Vector3f& other);

    double getX() const{
        return x_axis;
    }
    double getY() const{
        return y_axis;
    }
    double getZ() const{
        return z_axis;
    }

    void setX(double x_temp){
        x_axis = x_temp;
    }

    void setY(double y_temp){
        y_axis = y_temp;
    }

    void setZ(double z_temp){
        z_axis = z_temp;
    }

    Vector3f operator+(const Vector3f& other) const;
    Vector3f operator-(const Vector3f& other) const;
    Vector3f operator*(const Vector3f& other) const;
    Vector3f operator/(const Vector3f& other) const;

    Vector3f& operator=(const Vector3f& other);

    bool operator==(const Vector3f& other) const;
    bool operator!=(const Vector3f& other) const;

    const Vector3f &operator*=(float scale);
    const Vector3f &operator/=(float scale);
    const Vector3f &operator+=(const Vector3f &other);
    const Vector3f &operator-=(const Vector3f &other);
    ~Vector3f();

    
};


#endif // !VECTOR3F__H