#ifndef ILLUMINATION__H
#define ILLUMINATION__H
//For MAC
#ifdef __APPLE__ 
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h> // The GL Utility Toolkit (Glut) Header
#else 
//For Linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include "Color.hpp"
class Illumination
{
private:
    int x_c;
    int y_c;
    Color background_color;
    Color obj_color;
    Color diffuse_coef; //Ka
    Color specular_coef; //Ks
    Color ambient_coef; //Ka
    Illumination& operator=(const Illumination&);
    Illumination();
public:
    Illumination(int, int);
    Illumination(const Illumination&);
    ~Illumination();
    void write_pixel(int,int, const Color&);
    void write_pixel(const Color&);
    void draw_backgounrd();
    void draw_object();
    Color getObjColor() const{
        return obj_color;
    }
    Color getBackground_color() const{
        return background_color;
    }
    Color getKd() const{
        return diffuse_coef;
    }
    Color getKs() const{
        return specular_coef;
    }
    Color getKa() const{
        return ambient_coef;
    }
};

#endif //!ILLUMINATION__H