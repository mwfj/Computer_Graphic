#ifndef COLOR__H
#define COLOR__H
#include "Vector3f.hpp"
class Color
{
private:
    double r;//red
    double g;//green
    double b;//blue
public:
    Color();
    Color(const Color&);
    Color(double);
    Color(double, double, double);
    Color &operator=(const Color&);
    Color operator+(const Color&) const;
    const Color &operator+=(const Color&);
    const Color &operator*=(const Color&);
    const Color &operator*=(int);
    Color operator-(const Color&) const;
    Color operator*(const Color&) const;
    Color operator*(const Vector3f&) const;
    Color operator*(double) const;
    Color operator/(const Color&) const;
    ~Color();
    double getRed() const{
        return r;
    }
    double getGreen() const{
        return g;
    }
    double getBlue() const{
        return b;
    }

    void setRed(double r_){
        r = r_;
    }

    void setGreen(double g_){
        g = g_;
    }

    void setBlue(double b_){
        b = b_;
    }
};


#endif // !COLOR__H