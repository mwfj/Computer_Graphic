#ifndef POINT__H
#define POINT__H
/**
 * @author Wufangjie Ma
 * 
 **/
class Point{
public:
	Point();
	~Point(){};
	Point(double x1, double y1, double z1);
	double getX() const;
	double getY() const;
	double getZ() const;
    void setX(double);
    void setY(double);
	void setZ(double);
    Point(const Point&);
	Point operator-() const;
	Point operator-(const Point&) const;
	Point operator+(const Point&) const;
	// Point &operator=(const Point &);

private:
	double x;
	double y;
	double z;
};

Point::Point():x(1),y(1),z(1)
{}
Point::Point(const Point& p):x(p.getX()), y(p.getY()), z(p.getZ()){}
Point::Point(double x1, double y1,double z1):x(x1), y(y1),z(z1)
{}
double Point::getX() const{
	return x;
}
double Point::getY() const{
	return y;
}
double Point::getZ() const{
	return z;
}
void Point::setX(double x_){
    x =x_;
}
void Point::setY(double y_){
    y =y_;
}
void Point::setZ(double z_){
	z = z_;
}
Point Point::operator-() const{
	return Point(-x,-y,-z);
}
Point Point::operator-(const Point& other) const{
	return Point(x-other.getX(),y-other.getY(),z-other.getZ());
}
Point Point::operator+(const Point& other) const{
	return Point(x+other.getX(),y+other.getY(),z+other.getZ());
}
#endif