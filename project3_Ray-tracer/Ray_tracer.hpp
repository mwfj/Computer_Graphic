#ifndef RAYTRACER__H
#define RAYTRACER__H
/**
 * @author Wufangjie Ma
 * 
 **/

#include "Ray.hpp"
#include "Triangle.hpp"
#include "Vector3f.hpp"
class Ray_tracer
{
private:
    // Ray eye_ray;
    std::vector<Triangle> triangle_list; // A list store all the triangles
public:
    Ray_tracer(){}
    Ray_tracer(const std::vector<Triangle>&);
    Ray_tracer(const Ray_tracer&);
    Vector3f calBarycentry(const Ray&,const Triangle&);
    void findIntersection(bool);
    Vector3f normalize(double, double, double);
    Vector3f normalize(const Vector3f&);
    ~Ray_tracer();
}; 
 
#endif //!RAYTRACER__H