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


#endif