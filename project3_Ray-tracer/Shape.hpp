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
#include "Point.hpp"
#include <iostream>
/**
 * @author Wufangjie Ma
 * this class is the base class for drawing
 * I move and use write_pixel funciton in this class
 **/
class Shape
{
public:
    Shape(){};
    virtual ~Shape(){
    }
    Shape(int x, int y, int z):p(Point(x,y,z)){}
    // Shape(int x, int y, const ColorPicker& c):p(Point(x,y)),cp(c){}
    void write_pixel(int x, int y, double intensity) const
    {
        /* Turn on the pixel found at x,y */
        glColor3f(51.0/255.0, 51.0/255.0, 51.0/255.0);
        glBegin(GL_POINTS);
        glVertex3i(x, y, 0);
        glEnd();
    }
    // void write_pixel(int x, int y, const ColorPicker& c) const
    // {
    //     /* Turn on the pixel found at x,y */
    //     glColor3f(c.getR(), c.getG(), c.getB());
    //     glBegin(GL_POINTS); 
    //     glVertex3i(x, y, 0);
    //     glEnd();
    // }
    virtual void draw() const{
        // std::cout<<"Draw a Shape"<< std::endl;
        write_pixel(p.getX(), p.getY(), 1.0); 
        
    };
    // virtual void draw() const =0;
private:
    Point p;
    // ColorPicker cp;
    Shape(const Shape&);
    Shape& operator=(const Shape&);
};

#endif // !SHAPE__H
