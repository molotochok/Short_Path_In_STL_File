#include "STLParser.h"
#include "PathFinding.h"
#include <iostream>
#include <exception>

Point getPoint(std::string text, STLParser stlParser) {
	Point point;
	std::vector<Point> points = stlParser.getPoints();
	int decision = 0;
	bool exit = false;

	while (!exit) {
		std::cout << "Choose to input point by it index or by coordinates (index - 1, coordinates - 2):\n";
		std::cin >> decision;

		if (!std::cin || (decision != 1 && decision != 2)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "You should write 1 or 2!\n";
			continue;
		}
		switch (decision)
		{
		case 1:
			int index;
			std::cout << text << " index:\n";
			std::cin >> index;
			for (auto it = points.begin(); it != points.end(); it++) {
				if (index == it->_index) {
					point._index = it->_index;
					point._x = it->_x;
					point._y = it->_y;
					point._z = it->_z;
				}
			}
			exit = true;
			break;
		case 2:
			std::cout << text << " coordinates:\n";
			std::cin >> point;
			exit = true;
			break;
		default:
			break;
		}

	}

	return point;
}

std::string path;

int main() {
	try {
		std::cout << "Write path to stl file:\n";
		std::cin >> path;
		//--------------Parser------------------------------
		STLParser stlParser(path);
		stlParser.parse();
		stlParser.outputPoints();
		std::cout << "Number of points: " << stlParser.getPoints().size() << std::endl;

		//--------------PathFinding-------------------------
		PathFinding pathFinding(stlParser);					 //inizialze vertexMatrix (source target weight)
		pathFinding.setGraph(pathFinding.getVertexMatrix()); //create graph from vertexMatrix

		Point sourcePoint, targetPoint;
		bool exit1 = false;
		while (!exit1)
		{
			sourcePoint = getPoint("Write source point", stlParser);
			targetPoint = getPoint("Write target point", stlParser);

			std::cout << "----------------------------------------Result----------------------------------------\n";
			pathFinding.findShortestPath(sourcePoint, targetPoint, stlParser);

			char decision;
			bool exit2 = false;
			while (!exit2) {
				std::cout << "Continue?(Y/N): "; std::cin >> decision;
				switch (decision)
				{
				case 'Y':
				case 'y':
					exit2 = true;
					break;
				case 'N':
				case 'n':
					exit1 = true;
					exit2 = true;
					break;
				default:
					break;
				}
			}
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	system("pause");
	return 0;
}