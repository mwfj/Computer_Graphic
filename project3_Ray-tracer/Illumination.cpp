#include "Illumination.hpp"

Illumination::~Illumination()
{
}

Illumination::Illumination(int x_, int y_):
    x_c(x_),
    y_c(y_),
    background_color(Color(0.0)),
    obj_color(Color(0.686)),
    diffuse_coef(Color(0.8,0.8,0.8)),
    specular_coef(Color(1.0)),
    ambient_coef(Color(0.2))
{
}

Illumination::Illumination(const Illumination& i_):
    x_c(i_.x_c),
    y_c(i_.y_c),
    background_color(i_.background_color), 
    obj_color(i_.obj_color),
    diffuse_coef(i_.diffuse_coef),
    specular_coef(i_.specular_coef),
    ambient_coef(i_.ambient_coef)
{}
void Illumination::write_pixel(int x_, int y_, const Color& c)
/* Turn on the pixel found at x,y */
{
	// glColor3f(c.getRed()/255.0, c.getGreen()/255.0, c.getBlue()/255.0);
    glColor3f(c.getRed(), c.getGreen(), c.getBlue());
	glBegin(GL_POINTS);
	glVertex3i(x_, y_, 0);
	glEnd();
}
void Illumination::write_pixel(const Color& c){
    // std::cout<<"Red: "<<c.getRed()<<", "<<"Green: "<<c.getGreen()<<", "<<"Blue: "<<c.getBlue()<<std::endl;
    // glColor3f(c.getRed()/255.0, c.getGreen()/255.0, c.getBlue()/255.0);
    glColor3f(c.getRed(), c.getGreen(), c.getBlue());
	glBegin(GL_POINTS);
	glVertex3i(x_c, y_c, 0);
	glEnd();
}
void Illumination::draw_backgounrd(){
    write_pixel(x_c,y_c,background_color);
}
void Illumination::draw_object(){
    write_pixel(x_c,y_c,obj_color);
}