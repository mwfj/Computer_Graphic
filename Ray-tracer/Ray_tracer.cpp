/**
 * @author Wufangjie Ma
 * 
 **/
#include "Ray_tracer.hpp"
Ray_tracer::~Ray_tracer(){}
Ray_tracer::Ray_tracer(const Ray& r_, const Triangle& t_)
    :eye_ray(r_),triangle(t_){}
Ray_tracer::Ray_tracer(const Ray_tracer& rt_):
    eye_ray(rt_.eye_ray), triangle(rt_.triangle){}

double Ray_tracer::calBarycentry(const Ray& er_, const Triangle& tri_) const{
    double t, gamma, beta;
    std::vector<Point> temp_t_point;
    temp_t_point = tri_.getPointList();
    // double a = t_points[0].getX();
    // a: t_points[0] b: t_points[1] c: t_points[2]
    Point eb = temp_t_point[1]-temp_t_point[0];
    Point ec = temp_t_point[2]-temp_t_point[0];
    /** T
     * { -EBX, -ECX, (ax - ROX)
     *   -EBY, -ECY, (ay - ROY)
     *   -EBZ, -ECZ, (az - ROZ) }
     * **/
    double T[3][3] = {
        {-eb.getX(),-ec.getX(),( temp_t_point[0].getX()-eye_ray.getOri().getX() )},
        {-eb.getY(),-ec.getY(),( temp_t_point[0].getY()-eye_ray.getOri().getY() )},
        {-eb.getZ(),-ec.getZ(),( temp_t_point[0].getZ()-eye_ray.getOri().getZ() )}
    };
    // std::vector<std::vector<double> > T(3, std::vector<double>(3));
    // std::vector<std::vector<double> > A(3, std::vector<double>(3));
    // std::vector<std::vector<double> > B(3, std::vector<double>(3));
    // std::vector<std::vector<double> > C(3, std::vector<double>(3));
    /** A
     * { -EBX, -ECX, RdX
     *   -EBY, -ECY, Rdy
     *   -EBZ, -ECZ, Rdz }
     * **/
    double A[3][3] = {
        {-eb.getX(), -ec.getX(), eye_ray.getDir().getX()},
        {-eb.getY(), -ec.getY(), eye_ray.getDir().getY()},
        {-eb.getZ(), -ec.getZ(), eye_ray.getDir().getZ()}
    };
    /** B
     * { (ax-ROX), -ECX, RdX
     *   (ay-ROY), -ECY, Rdy
     *   (az-ROZ), -ECZ, RdZ }
     * **/
    double B[3][3] = {
        { ( temp_t_point[0].getX()-eye_ray.getOri().getX() ), -ec.getX(), eye_ray.getDir().getX() },
        { ( temp_t_point[0].getY()-eye_ray.getOri().getY() ), -ec.getY(), eye_ray.getDir().getY() },
        { ( temp_t_point[0].getZ()-eye_ray.getOri().getZ() ), -ec.getZ(), eye_ray.getDir().getZ() }
    };
    /** C
     * { -EBX, (ax-ROX), RdX
     *   -EBY, (ay-ROY), Rdy
     *   -EBZ, (az-ROZ), RdZ }
     * **/
    double C[3][3] = {
        { -eb.getX(), ( temp_t_point[0].getX()-eye_ray.getOri().getX() ), eye_ray.getDir().getX() },
        { -eb.getY(), ( temp_t_point[0].getY()-eye_ray.getOri().getY() ), eye_ray.getDir().getY() },
        { -eb.getZ(), ( temp_t_point[0].getZ()-eye_ray.getOri().getZ() ), eye_ray.getDir().getZ() }
    };
    Matrix m_;
    t = m_.determinant(T)/m_.determinant(A);
    beta = m_.determinant(B)/m_.determinant(A);
    gamma = m_.determinant(C)/m_.determinant(A);
    if (t>0)
    {
        if (beta > 0 && gamma > 0)
        {
            if ( (beta+gamma) < 1)
            {
                return t;
            }
        }   
    }
    return 0;
}