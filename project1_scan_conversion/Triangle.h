#ifndef TRIANGLE__H
#define TRIANGLE__H
#include "Line.h"
#include "ColorPicker.h"
// #include "Shape.h"
#include <vector>
/**********************************************
 * 
 * @author Wufangjie Ma
 * 
 **********************************************/
class Triangle : public Shape
{
public:
    Triangle(){};
    ~Triangle(){
        std::vector<Point>().swap(t_points);
    };
    Triangle(const std::vector<Point>&, const ColorPicker&);
    void drawTriangle(const Point &p1, const Point &p2, const Point &p3) const;
    static bool isDrawed;
    virtual void draw() const;

private:
    ColorPicker cp_t;
    std::vector<Point> t_points;
    Triangle& operator=(const Triangle&);
};
Triangle::Triangle(const std::vector<Point>& vp, const ColorPicker& c):
                    t_points(vp),cp_t(c)

{}
void Triangle::drawTriangle(const Point &a, const Point &b, const Point &c) const
{
	Line l1(cp_t);
	Line l2(cp_t);
	Line l3(cp_t);
	l1.dda(a, b);
	l2.dda(b, c);
	l3.dda(a, c);
}

void Triangle::draw() const{
    // std::cout<<"Draw a Triangle"<< std::endl;
    for (int i = t_points.size() % 3 ==0 ? t_points.size() : t_points.size()-1 ; i >=3; i-=3)
    {
        drawTriangle(t_points[i-1], t_points[i-2], t_points[i-3]);
    }
    
}
#endif // !TRIANGLE__H
