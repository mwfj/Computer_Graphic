#ifndef RAYTRACER__H
#define RAYTRACER__H
/**
 * @author Wufangjie Ma
 * 
 **/

#include "Ray.hpp"
#include "Triangle.hpp"
class Ray_tracer
{
private:
    Ray eye_ray;
    Triangle triangle;
    Ray_tracer();
public:
    Ray_tracer(const Ray&, const Triangle&);
    Ray_tracer(const Ray_tracer&);
    double calBarycentry(const Ray&, const Triangle&) const;
    ~Ray_tracer();
}; 
 
#endif //!RAYTRACER__H