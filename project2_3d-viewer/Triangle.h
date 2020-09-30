#ifndef TRIANGLE__H
#define TRIANGLE__H
#include "Line.h"
#include <vector>
/**
 * @author Wufangjie Ma
 * This class inherits the Shape class for drawing the Triangle
 **/
class Triangle : public Shape
{
public:
    Triangle(){};
    ~Triangle(){
        std::vector<Point>().swap(t_points);
    };
    Triangle(const std::vector<Point>&);
    Triangle(const Point&, const Point&, const Point&);
    // Drawing Triangle
    void drawTriangle(const Point &p1, const Point &p2, const Point &p3) const;
    static bool isDrawed;
    virtual void draw() const;
    double getMAX_X() const;
private:
    // Store the vertexs of triangle
    std::vector<Point> t_points;
    Triangle& operator=(const Triangle&);
};

Triangle::Triangle(const Point& a, const Point& b, const Point& c){
    t_points.push_back(a);
    t_points.push_back(b);
    t_points.push_back(c);
}
Triangle::Triangle(const std::vector<Point>& vp):t_points(vp){}
// Drawing function
void Triangle::drawTriangle(const Point &a, const Point &b, const Point &c) const
{
	Line l1;
	Line l2;
	Line l3;
	l1.dda(a, b);
	l2.dda(b, c);
	l3.dda(a, c);
}

// using drawTriangle and the point store in the vector to draw a triangle
void Triangle::draw() const{
    // std::cout<<"Draw a Triangle"<< std::endl;
    for (int i = t_points.size() % 3 ==0 ? t_points.size() : t_points.size()-1 ; i >=3; i-=3)
    {
        drawTriangle(t_points[i-1], t_points[i-2], t_points[i-3]);
    }
    
}

#endif // !TRIANGLE__H
