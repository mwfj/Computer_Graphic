#ifndef LINE__H
#define LINE__H
#include "Point.h"
#include "Shape.h"
#include <iostream>
#include <vector>
#include "ColorPicker.h"
class Line: public Shape{
public:
    Line(){}
    Line(const std::vector<Point> &, const ColorPicker&);
	Line(const ColorPicker& c):cp_l(c){}
    ~Line(){
		std::vector<Point>().swap(l_points);
	}
    static bool isDrawed;
    std::vector<Point> l_points;
    void dda(const Point& a, const Point& b) const;
    virtual void draw() const;
private:
	ColorPicker cp_l;
    Line& operator=(const Line &);
};
Line::Line(const std::vector<Point> &vp, const ColorPicker& c):l_points(vp),cp_l(c){}

void Line::dda(const Point& a, const Point& b) const
{
	int dx = b.getX() - a.getX(); // represent the difference for x between two points
	int dy = b.getY() - a.getY(); // represent the difference for y between two points
	int steps;
	float x_inc = 0, y_inc = 0;
	float x = a.getX(), y = a.getY(); //record the current position for x and y during drawing the line.
	if (abs(dx) > abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}

	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	for (int i = 0; i < steps; i++)
	{
		Shape::write_pixel(x, y, cp_l);
		x += x_inc;
		y += y_inc;
	}
}

void Line::draw() const{
	// std::cout<<"Draw a Line"<< std::endl;
    for (int i = l_points.size() % 2 == 0 ? l_points.size(): l_points.size()-1; i >=2; i-=2)
    {
        dda(l_points[i-1],l_points[i-2]);
    }
    
}
#endif // !POINT_T
