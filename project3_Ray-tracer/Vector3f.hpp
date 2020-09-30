#ifndef VECTOR3F__H
#define VECTOR3F__H
/**
 * @author Wufangjie Ma
 * This Class is for store the two-dimensional data
 **/
#include<iostream>
#include <math.h>
class Vector3f
{
private:
    double x_axis;
    double y_axis;
    double z_axis;
public:
    Vector3f(double x, double y, double z);
    Vector3f(const Vector3f& other);
    Vector3f cross_product(const Vector3f&);
    void reverse_norm(){
        x_axis = -x_axis;
        y_axis = -y_axis;
        z_axis = -z_axis;
    }
    double modulus();
    //Dot product for one dimension vector
    double dot(const Vector3f&);
    double getX() const{
        return x_axis;
    }
    void normalize(){
       double x = x_axis / sqrt(x_axis*x_axis + y_axis*y_axis +z_axis*z_axis);
       double y = y_axis / sqrt(x_axis*x_axis + y_axis*y_axis +z_axis*z_axis);
       double z = z_axis / sqrt(x_axis*x_axis + y_axis*y_axis +z_axis*z_axis);
        this->x_axis=x;
        this->y_axis=y;
        this->z_axis=z;
    //    return Vector3f(temp_x,temp_y,temp_z);
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
    Vector3f operator*(double) const;
    Vector3f operator/(const Vector3f& other) const;
    Vector3f operator/(double) const;
    Vector3f operator-() const;
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