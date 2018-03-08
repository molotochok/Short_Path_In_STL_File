#pragma once
#include<vector>
#include<string>
#define HEADER_LENGTH 80
#define NUM_TRIANGLES_LENGTH 4
#define ATTR_BYTE_COUNT_LENGTH 2 //attribute byte count

struct Point {
	float _index;
	float _x;
	float _y;
	float _z;

	Point();
	Point(float index, float x, float y, float z);
	friend std::ostream& operator<<(std::ostream& out, const Point& point);
	friend std::istream& operator>>(std::istream& in, Point& point);
	friend bool operator==(const Point& point1, const Point& point2);
};

struct Triangle {
	Point _normal;
	Point _point1;
	Point _point2;
	Point _point3;

	Triangle();
	Triangle(Point normal, const Point& point1, const Point& point2, const Point& point3);
	friend std::ostream& operator<<(std::ostream& out, const Triangle& triangle);
};

class STLParser {
private:
	std::string			  _filePath;
	std::vector<Triangle> _triangles;
	std::vector<Point>	  _points;
	float				  _index;

	//Private methods
	Point parsePoint(std::ifstream& input, bool hasIndex);
	float getPointName(float x, float y, float z);
	float parseFloat(std::ifstream& input);
public:
	//Constructors
	STLParser();
	STLParser(const std::string& filePath);

	//Public methods
	void parse();
	void outputTriangles();

	//getter and setter
	void setFilePath(std::string filePath);
	std::string getFilePath();
	void setTriangles(std::vector<Triangle> triangles);
	std::vector<Triangle> getTriangles();
	std::vector<Point> getPoints();
};