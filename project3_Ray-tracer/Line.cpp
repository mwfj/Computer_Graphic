#include "Line.hpp"

Line::Line(const std::vector<Point>& vp):l_points(vp){};
// DDA algorithm
void Line::dda(const Point& a, const Point& b) const
{
	int dx = b.getX() - a.getX(); // represent the difference for x between two points
	int dy = b.getY() - a.getY(); // represent the difference for y between two points
	int steps;
	float x_inc = 0, y_inc = 0;
	float x = a.getX(), y = a.getY(); //record the current position for x and y during drawing the line.
	if (abs(dx) > abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}

	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	for (int i = 0; i < steps; i++)
	{
		// Shape::write_pixel(x, y, cp_l);
        Shape::write_pixel(x,y,1.0);
		x += x_inc;
		y += y_inc;
	}
}

void Line::draw() const{
	// std::cout<<"Draw a Line"<< std::endl;
    for (int i = l_points.size() % 2 == 0 ? l_points.size(): l_points.size()-1; i >=2; i-=2)
    {
        dda(l_points[i-1],l_points[i-2]);
    }
    
}