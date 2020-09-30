#ifndef VECTOR2F__H
#define VECTOR2F__H
#include <iostream>
/**
 * @author Wufangjie Ma
 * This Class is for store the two-dimensional data
 **/
class Vector2f
{
private:
    double x_axis;
    double y_axis;
public:
    Vector2f(double x, double y);
    Vector2f(const Vector2f& other);
    double getX(){
        return x_axis;
    }
    double getY(){
        return y_axis;
    }

    void setX(double x_temp){
        x_axis = x_temp;
    }

    void setY(double y_temp){
        y_axis = y_temp;
    }

    Vector2f operator+(const Vector2f& other) const;
    Vector2f operator-(const Vector2f& other) const;
    Vector2f operator*(const Vector2f& other) const;
    Vector2f operator/(const Vector2f& other) const;

    Vector2f& operator=(const Vector2f& other);

    bool operator==(const Vector2f& other) const;
    bool operator!=(const Vector2f& other) const;

    const Vector2f &operator*=(float scale);
    const Vector2f &operator/=(float scale);
    const Vector2f &operator+=(const Vector2f &other);
    const Vector2f &operator-=(const Vector2f &other);

    ~Vector2f(){}
};

#endif // VECTOR2F__H