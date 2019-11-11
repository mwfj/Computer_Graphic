#ifndef SHAPE__H
#define SHAPE__H
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h> // The GL Utility Toolkit (Glut) Header
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <vector>
#include "Point.h"
#include "ColorPicker.h"
#include <iostream>
class Shape
{
public:
    Shape(){};
    virtual ~Shape(){
    }
    Shape(int x, int y):p(Point(x,y)){}
    Shape(int x, int y, const ColorPicker& c):p(Point(x,y)),cp(c){}
    void write_pixel(int x, int y, double intensity) const
    {
        /* Turn on the pixel found at x,y */
        glColor3f(intensity, intensity, intensity);
        glBegin(GL_POINTS);
        glVertex3i(x, y, 0);
        glEnd();
    }
    void write_pixel(int x, int y, const ColorPicker& c) const
    {
        /* Turn on the pixel found at x,y */
        glColor3f(c.getR(), c.getG(), c.getB());
        glBegin(GL_POINTS); 
        glVertex3i(x, y, 0);
        glEnd();
    }
    virtual void draw() const{
        // std::cout<<"Draw a Shape"<< std::endl;
        write_pixel(p.getX(), p.getY(), 1.0); 
        
    };
    // virtual void draw() const =0;
private:
    Point p;
    ColorPicker cp;
    Shape(const Shape&);
    Shape& operator=(const Shape&);
};

#endif // !SHAPE__H
