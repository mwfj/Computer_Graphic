#ifndef COLOR__H
#define COLOR__H
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
    ~Color();
    double getRed(){
        return r;
    }
    double getGreen(){
        return g;
    }
    double getBlue(){
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
Color::~Color()
{
}

#endif // !COLOR__H