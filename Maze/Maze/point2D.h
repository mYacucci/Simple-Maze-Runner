#include <cstdlib>
#include <iostream>

using namespace std;

struct Point2D {
	int x;
	int y;

	Point2D(int x = 0, int y = 0) : x(x), y(y) {}

	friend ostream& operator<<(ostream& os,  Point2D const& point2D) {
		os << "(" << point2D.x << ", " << point2D.y << ")";
		return os;
	}

	bool equals(Point2D rhs) {
		return (x == rhs.x && x == rhs.y)? true : false;
	}
};