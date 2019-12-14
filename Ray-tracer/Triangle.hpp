#ifndef TRIANGLE__H
#define TRIANGLE__H
#include "Line.hpp"
#include "Ray.hpp"
#include "Matrix.hpp"
#include <vector>
#include <assert.h>
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
    Triangle(const Triangle&);
    Triangle(const std::vector<Point>&);
    Triangle(const Point&, const Point&, const Point&);
    // Drawing Triangle
    void drawTriangle(const Point &p1, const Point &p2, const Point &p3) const;
    static bool isDrawed;
    virtual void draw() const;
    double getMAX_X() const;
    Point getAve() const{
        double sumx = 0.0, sumy = 0.0, sumz = 0.0;
        for (int i = 0; i < t_points.size(); i++)
        {
            sumx+=t_points[i].getX();
            sumy+=t_points[i].getY();
            sumz+=t_points[i].getZ();
        }     
        // std::cout<<sumx<<std::endl;
        return Point(sumx/3.0,sumy/3.0,sumz/3.0);
    }
    double smallest_distance(const Point&);
    const std::vector<Point>& getPointList() const{
        return t_points;
    }
    Vector3f getNorm(); //norm from vertex A
    Vector3f getNormB(); // norm from vertex B
    Vector3f getNormC(); // norm from vertex C
    const std::vector<Vector3f> getNormList();
private:
    // Store the vertexs of triangle
    std::vector<Point> t_points;
    std::vector<Vector3f> norm_list;
    Triangle& operator=(const Triangle&);
};


#endif // !TRIANGLE__H
