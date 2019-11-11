#ifndef POINT__H
#define POINT__H
class Point{
public:
	Point();
	~Point(){};
	Point(int x1, int y1);
	// bool operator==(const Point &p);
	// bool operator!=(const Point &p);
	int getX() const;
	int getY() const;

private:
	int x;
	int y;
	Point &operator=(const Point &p);
};

Point::Point():x(1),y(1)
{}

Point::Point(int x1, int y1):x(x1), y(y1)
{}
int Point::getX() const{
	return x;
}
int Point::getY() const{
	return y;
}

#endif