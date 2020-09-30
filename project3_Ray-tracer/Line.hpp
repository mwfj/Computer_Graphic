#ifndef LINE__H
#define LINE__H
#include "Point.hpp"
#include "Shape.hpp"
#include <iostream>
#include <vector>
/**
 * @author Wufangjie Ma
 * This class inherits the Shape class for drawing the Line
 **/
class Line: public Shape{
public:
    Line(){}
    Line(const std::vector<Point> &);
    ~Line(){
		std::vector<Point>().swap(l_points);
	}
    static bool isDrawed;
    std::vector<Point> l_points;
    void dda(const Point& a, const Point& b) const;
    virtual void draw() const;
private:
    Line& operator=(const Line &);
};


#endif // !POINT_T
