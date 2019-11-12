#ifndef CIRCLE__H
#define CIRCLE__H
#include "Shape.h"
#include "ColorPicker.h"
#include <vector>
#include <math.h>
/**********************************************
 * 
 * @author Wufangjie Ma
 * 
 **********************************************/
class Circle : public Shape{
public:
    Circle(){}
    ~Circle(){
        std::vector<Point>().swap(c_points);
    }
    Circle(const std::vector<Point>&, const ColorPicker&);
    void plotCircle(int x_center, int y_center, int x, int y) const;
    virtual void draw() const;
    void drawCirlce(const Point&, const Point&) const; //midpoint algorithm
private:
    ColorPicker cp_c;
    std::vector<Point> c_points;
};

Circle::Circle(const std::vector<Point>& vp, const ColorPicker& c):
    cp_c(c),c_points(vp){}


void Circle::plotCircle(int x_center, int y_center, int x, int y) const{
    write_pixel(x_center+x , y_center+y, cp_c);
    write_pixel(x_center+x , y_center-y, cp_c);
    write_pixel(x_center-x , y_center+y, cp_c);
    write_pixel(x_center-x , y_center-y, cp_c);
    write_pixel(x_center+y , y_center+x, cp_c);
    write_pixel(x_center+y , y_center-x, cp_c);
    write_pixel(x_center-y , y_center+x, cp_c);
    write_pixel(x_center-y , y_center-x, cp_c);
}

void Circle::drawCirlce(const Point& center, const Point& side) const {
    int r = abs(sqrt( ( side.getX()-center.getX() ) * ( side.getX()-center.getX() ) - (side.getY()-center.getY())*(side.getY()-center.getY()) ) );
    float p = 1-r;
    int x = 0, y = r;
    plotCircle(center.getX(),center.getY(), x, y);
    while (x<y)
    {
        if (p<0)
        {
            x++;
            p = p + 2*x +1;
        }else{
            x++;
            y--;
            p = p + 2*(x-y) +1;
        }
        plotCircle(center.getX(),center.getY(), x, y);
    }

    
}

void Circle::draw() const {
    for (int i = c_points.size()%2 == 0?c_points.size():c_points.size()-1 ; i >=2; i-=2)
    {
        drawCirlce(c_points[i-1], c_points[i-2]);
    }
}
#endif // !CIRCLE__H