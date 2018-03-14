#include"STLParser.h"
#include<fstream>
#include<exception>
#include<iostream>
#include<algorithm>
#include<iterator>

//---------------STLParser---------------------
//Constructors
STLParser::STLParser() {
	setFilePath("");
};
STLParser::STLParser(const std::string& filePath) {
	setFilePath(filePath);
	_index = 0;
	_points.resize(0);
};

//Helpful methods
float STLParser::getPointName(float x, float y, float z) {
	float index;
	if (std::find_if(_points.begin(), _points.end(), [&](Point point) {
		if (point._x == x && point._y == y && point._z == z) {
			index = point._index;
			return true;
		}
		return false;
	}) == _points.end()) {
		_index++;
		index = _index;
		_points.push_back(Point(index, x, y, z));
	}
	return index;
}

Point STLParser::parsePoint(std::ifstream& input, bool hasIndex) {
	float x = parseFloat(input);
	float y = parseFloat(input);
	float z = parseFloat(input);
	float index = 0;
	if (hasIndex)
		index = getPointName(x, y, z);
	return Point(index, x, y, z);
}
float STLParser::parseFloat(std::ifstream& input) {
	char f_buf[sizeof(float)];
	input.read(f_buf, 4);
	float* fptr = (float*)f_buf;
	return *fptr;
}

//Main methods
void STLParser::parse() {
	std::ifstream input(_filePath, std::ios::binary | std::ios::in);
	if (!input) {
		throw std::exception("\nCan't read file!\nSuch file doesn't exist!\n");
	}

	char header[HEADER_LENGTH];
	char numOfTrianglesChar[NUM_TRIANGLES_LENGTH];
	char attrByteCountChar[ATTR_BYTE_COUNT_LENGTH];

	input.read(header, HEADER_LENGTH);
	input.read(numOfTrianglesChar, NUM_TRIANGLES_LENGTH);

	unsigned int* temp = (unsigned int*)numOfTrianglesChar;
	unsigned int numOfTriangles = *temp;

	for (unsigned int i = 0; i < numOfTriangles; i++) {
		Point normal = parsePoint(input, false);
		Point point1 = parsePoint(input, true);
		Point point2 = parsePoint(input, true);
		Point point3 = parsePoint(input, true);
		Triangle triangle(normal, point1, point2, point3);
		_triangles.push_back(triangle);
		input.read(attrByteCountChar, ATTR_BYTE_COUNT_LENGTH);
	}
}
void STLParser::outputTriangles() {
	std::ostream_iterator<Triangle> os(std::cout, "\n");
	std::copy(_triangles.begin(), _triangles.end(), os);
}

void STLParser::outputPoints()
{
	std::cout << "Points (index (x, y, z):\n";
	std::ostream_iterator<Point> os(std::cout, "\n");
	std::copy(_points.begin(), _points.end(), os);
}

//getter and setter
void STLParser::setFilePath(std::string filePath) {
	_filePath = filePath;
}
std::string STLParser::getFilePath() {
	return _filePath;
}
void STLParser::setTriangles(std::vector<Triangle> triangles) {
	_triangles = triangles;
}
std::vector<Triangle> STLParser::getTriangles() {
	return _triangles;
}
std::vector<Point> STLParser::getPoints() {
	return _points;
}

//---------------Point---------------------
Point::Point() : _index(0), _x(0), _y(0), _z(0) {};
Point::Point(float index, float x, float y, float z) {
	_index = index;
	_x = x;
	_y = y;
	_z = z;
}
std::ostream& operator<<(std::ostream& out, const Point& point) {
	out << point._index << " (" << point._x << ", " << point._y << ", " << point._z << ")";
	return out;
}
std::istream& operator>>(std::istream& in, Point& point) {
	std::cout << "x= ";	in >> point._x;
	std::cout << "y= ";	in >> point._y;
	std::cout << "z= ";	in >> point._z;
	return in;
}
bool operator==(const Point& point1, const Point& point2) {
	if (fabs(point1._x - point2._x) < 0.001 && fabs(point1._y - point2._y) < 0.001 && fabs(point1._z - point2._z) < 0.001)
		return true;
	return false;
}

//---------------Triangle---------------------
Triangle::Triangle() : _normal(), _point1(), _point2(), _point3() {};
Triangle::Triangle(Point normal, const Point& point1, const Point& point2, const Point& point3) {
	_normal = normal;
	_point1 = point1;
	_point2 = point2;
	_point3 = point3;
}

std::ostream& operator<<(std::ostream& out, const Triangle& triangle) {
	out << "\nTriangle:\n";
	out << "Normal:" << triangle._normal << std::endl;
	out << "Point1:" << triangle._point1 << std::endl;
	out << "Point2:" << triangle._point2 << std::endl;
	out << "Point3:" << triangle._point3 << std::endl;
	return out;
}