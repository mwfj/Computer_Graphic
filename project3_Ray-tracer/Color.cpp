#include "Color.hpp"

Color::Color(const Color& c_):r(c_.r),g(c_.g),b(c_.b){}

Color::Color(double c_):r(c_),g(c_),b(c_){}

Color::Color(double r_, double g_, double b_):r(r_),g(g_),b(b_)
{
}

Color::Color():r(0.0f),g(0.0f),b(0.0f){
}

Color& Color::operator=(const Color& c_){
    if (this == &c_)
    {
        return *this;
    }
    r = c_.r;
    g = c_.g;
    b = c_.b;
    return *this;
}
Color Color::operator+(const Color& other) const{
    return Color(r+other.getRed(), g+other.getGreen(), b+other.getBlue());
}
const Color& Color::operator+=(const Color& other){
    r += other.getRed();
    g += other.getGreen();
    b += other.getBlue();
    return *this;
}
const Color& Color::operator*=(const Color& other){
    r *= other.getRed();
    g *= other.getGreen();
    b *= other.getBlue();
    return *this;
}
const Color& Color::operator*=(int i){
    r *= i;
    g *= i;
    b *= i;
    return *this;
}
Color Color::operator-(const Color& other) const{
    return Color(r-other.getRed(), g-other.getGreen(), b-other.getBlue());
}
Color Color::operator*(const Color& other) const{
    return Color(r*other.getRed(), g*other.getGreen(), b*other.getBlue());
}
Color Color::operator*(const Vector3f& other) const{
    return Color(r*other.getX(), g*other.getY(), b*other.getZ());
}
Color Color::operator*(double c_) const{
    return Color(r*c_, g*c_, b*c_);
}
Color Color::operator/(const Color& other) const{
    return Color(r/other.getRed(), g/other.getGreen(), b/other.getBlue());
}
Color::~Color()
{
}
