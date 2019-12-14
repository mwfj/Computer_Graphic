#include "Ray.hpp"

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