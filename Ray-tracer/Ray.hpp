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
    void setOri(double x, double y, double z) {
        ori.setX(x);
        ori.setY(y);
        ori.setZ(z);
    }
    void setOri(const Vector3f& ori_) {
        ori.setX(ori_.getX());
        ori.setY(ori_.getY());
        ori.setZ(ori_.getZ());
    }
    void setDir(double x, double y, double z){
        direction.setX(x);
        direction.setY(y);
        direction.setZ(z);
    }
    void setDir(const Vector3f& dir_){
        direction.setX(dir_.getX());
        direction.setY(dir_.getY());
        direction.setZ(dir_.getZ());
    }
    ~Ray();
};


#endif // !RAY__H