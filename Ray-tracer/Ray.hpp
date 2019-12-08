#ifndef RAY__H
#define RAY__H
/**
 * @author Wufangjie Ma
 * 
 **/

#include "Vector3f.hpp"
#include <math.h>
#include <limits>

class Ray
{
private:
    Vector3f ori; //R0
    Vector3f direction; // Rd
    double max_ray;
    double min_ray;
    Ray& operator=(const Ray&);
public:
    Ray();
    Ray(const Ray&);
    Ray(const Vector3f&, const Vector3f&);
    Vector3f getOri() const{
        return ori;
    }
    Vector3f getDir() const{
        return direction;
    }
    ~Ray();
};

Ray::Ray()
:ori(Vector3f(0.0f,0.0f,0.0f)),
direction(Vector3f(0.0f,0.0f,0.0f)),
max_ray(std::numeric_limits<double>::infinity()),
min_ray(-std::numeric_limits<double>::infinity())
{}
Ray::Ray(const Ray& r):
ori(r.ori),
direction(r.direction),
max_ray(r.max_ray),
min_ray(r.min_ray)
{}
Ray::Ray(const Vector3f& ori_, const Vector3f& dir_):
ori(ori_),direction(dir_){
    max_ray = std::numeric_limits<double>::infinity();
    min_ray = -std::numeric_limits<double>::infinity();
}


Ray::~Ray()
{
}

#endif // !RAY__H