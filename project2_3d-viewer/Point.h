#ifndef POINT__H
#define POINT__H
class Point{
public:
	Point();
	~Point(){};
	Point(double x1, double y1);
	double getX() const;
	double getY() const;
    void setX(double);
    void setY(double);
    Point(const Point&);
	// Point &operator=(const Point &);

private:
	double x;
	double y;
};

Point::Point():x(1),y(1)
{}
Point::Point(const Point& p):x(p.getX()), y(p.getY()){}
Point::Point(double x1, double y1):x(x1), y(y1)
{}
double Point::getX() const{
	return x;
}
double Point::getY() const{
	return y;
}

void Point::setX(double x_){
    x =x_;
}
void Point::setY(double y_){
    y =y_;
}
#endif