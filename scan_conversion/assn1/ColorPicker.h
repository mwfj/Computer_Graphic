#ifndef COLORPICKER__H
#define COLORPICKER__H
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h> // The GL Utility Toolkit (Glut) Header
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
// #include "Shape.h"
class ColorPicker{
public:
    ColorPicker(){}
    ColorPicker(const ColorPicker& cp):r(cp.r),g(cp.g),b(cp.b){}
    ColorPicker(double ra, double ba, double ga):r(ra),g(ga),b(ba){}
    ~ColorPicker(){}
    const ColorPicker& operator=(const ColorPicker&);
    void setR(double temp){
        this->r = temp;
    }
    void setG(double temp){
        this->g = temp;
    }
    void setB(double temp){
        this->b = temp;
    }
    double getR() const {
        return r;
    }
    double getG() const{
        return g;
    }
    double getB() const{
        return b;
    }
private:
    double r;//red
    double g;//green
    double b;//blue
};

const ColorPicker& ColorPicker::operator=(const ColorPicker& c){
    this->r = c.r;
    this->g = c.g;
    this->b = c.b;
    return *this;
}
#endif