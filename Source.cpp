#include "STLParser.h"
#include "PathFinding.h"
#include <iostream>
#include <exception>

Point getPoint(std::string text) {
	Point point;
	std::cout << text;
	std::cin >> point;
	return point;
}

std::string path;

int main() {
	try {
		std::cout << "Write file name:\n";
		std::cin >> path;
		//--------------Parser------------------------------
		STLParser stlParser(path);
		stlParser.parse();
		stlParser.outputTriangles();

		//--------------PathFinding-------------------------
		Point sourcePoint, targetPoint;
		sourcePoint = getPoint("Write source point:\n");
		targetPoint = getPoint("Write target point:\n");
		//VertexMatrix 
		PathFinding pathFinding(stlParser);		//inizialze vertexMatrix (source target weight)
		//Graph
		pathFinding.setGraph(pathFinding.getVertexMatrix());	//create graph from vertexMatrix

		std::cout << "--------------------------Result----------------------------\n";
		pathFinding.findShortestPath(sourcePoint, targetPoint, stlParser);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	system("pause");
	return 0;
}