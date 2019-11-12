#ifndef RECTANGLE__H
#define RECTANGLE__H
#include "Line.h"
#include "ColorPicker.h"
// #include "Shape.h"
#include <vector>

class Rectangle : public Shape
{
public:
    Rectangle(){};
    Rectangle(const std::vector<Point>&, const ColorPicker&);
    ~Rectangle(){
		std::vector<Point>().swap(r_points);
	};
    static bool isDrawed;
    std::vector<Point> r_points;
    virtual void draw() const;
private:
	ColorPicker cp_r;
    void drawRectangle(const Point&, const Point&) const;
    Rectangle& operator=(const Rectangle&);
};
Rectangle::Rectangle(const std::vector<Point>& vp, const ColorPicker& c)
    :r_points(vp),cp_r(c){}

void Rectangle::drawRectangle(const Point& a, const Point&c) const
{
	/**
     a-------d          d-------c
     |       |    or    |       |
     b-------c          a-------b
    **/
	if (a.getY() > c.getY())
	{
		Point b(a.getX(), c.getY());
		Point d(c.getX(), a.getY());
		Line l1(cp_r);
		Line l2(cp_r);
		Line l3(cp_r);
		Line l4(cp_r);
		l1.dda(a, b);
		l2.dda(b, c);
		l3.dda(c, d);
		l4.dda(d, a);
	}
	else
	{
		Point b(c.getX(), a.getY());
		Point d(a.getX(), c.getY());
		Line l1;
		Line l2;
		Line l3;
		Line l4;
		l1.dda(a, b);
		l2.dda(b, c);
		l3.dda(c, d);
		l4.dda(d, a);
	}
}

void Rectangle::draw() const {
	// std::cout<<"Draw a Rectangle"<< std::endl;
    for (int i = r_points.size() %2 == 0? r_points.size():r_points.size()-1 ; i >=2; i-=2)
    {
        drawRectangle(r_points[i-1], r_points[i-2]);
    }
    
}
#endif // !RECTANGLE__H#define 