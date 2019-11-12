#ifndef ELLIPSE__H
#define ELLIPSE__H
#define ROUND(a) ((int) (a + 0.5))
#include "Shape.h"
#include "ColorPicker.h"
#include<vector>
class Eillpse : public Shape{
public:
    Eillpse(){};
    ~Eillpse(){
        std::vector<Point>().swap(e_points);
    };
    Eillpse(const std::vector<Point>&, const ColorPicker&);
    virtual void draw() const;
    void drawEillpse(const Point&, const Point&) const; //midpoint algorithm
    void plotEllipse(int, int, int, int) const;
private:
    ColorPicker cp_e;
    std::vector<Point> e_points;
};
Eillpse::Eillpse(const std::vector<Point>& vp, const ColorPicker& c):
    cp_e(c),e_points(vp){}

void Eillpse::plotEllipse(int x_center, int y_center, int x, int y) const{
        write_pixel(x_center + x , y_center + y , cp_e);
        write_pixel(x_center - x , y_center + y , cp_e);
        write_pixel(x_center + x , y_center - y , cp_e);
        write_pixel(x_center - x , y_center - y , cp_e);
    }
void Eillpse::drawEillpse(const Point& c, const Point& r) const{
    float rx_squre =r.getX()*r.getX();
    float ry_squre =r.getY()*r.getY();
    int rx2 = 2 * rx_squre;
    int ry2 = 2 * ry_squre; 
    int p;
    int x = 0, y = r.getY();
    int px = 0, py = rx2 * y;
    plotEllipse(c.getX(), c.getY(), x, y);

    p = ROUND(ry_squre - rx_squre*r.getY() + 0.25* rx_squre);
    
    while (px < py)
    {
        x++;
        px += ry2;
        if(p < 0){
            p += px + ry_squre;
        }else{
            y--;
            py -= rx2;
            p += px -py + ry_squre;
        }
        plotEllipse(c.getX(), c.getY(), x, y);
    }
    p = ROUND( ry_squre * (x+0.5) * (x+0.5) +rx_squre * (y-1) * (y-1) - rx_squre*ry_squre);
    while (y>0)
    {
        y--;
        py -= rx2;
        if(p>0){
            p += rx_squre - py;
        }else{
            x++;
            px += ry2;
            p += px - py + rx_squre;
        }
        plotEllipse(c.getX(), c.getY(), x, y);
    }
    
    
}

void Eillpse::draw() const{
    for (int i = e_points.size()%2 == 0?e_points.size():e_points.size()-1 ; i >=2; i-=2)
    {
        drawEillpse(e_points[i-1], e_points[i-2]);
    }
    
}
#endif