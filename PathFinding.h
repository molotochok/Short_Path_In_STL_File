#pragma once
#include<vector>
#include"STLParser.h"
#define FLOAT_MAX 999999.0
class PathFinding {
private:
	std::vector<std::vector<float>> _vertexMatrix;
	std::vector < std::vector<float>> _graph;

	//Private methods
	float findDistance(const Point& point1, const Point& point2);
	int findMinDistance(const std::vector<float>& distances, const std::vector<bool>& shortestPathSet);
	void inizializeGraph(int size);
	int getIndex(const Point& point, STLParser& stlParser);
public:
	//Constructors
	PathFinding(STLParser stlParser);
	PathFinding(const std::vector<std::vector<float>>& _vertexMatrix);
	
	//Public methods
	void findShortestPath(Point& source, Point& target, STLParser& stlParser);
	void outputMatrix(const std::vector<std::vector<float>>& matrix, const std::string& name, char delimiter);
	void outputPath(const std::vector<int>& parent, int v);

	//Getter setter
	void setVertexMatrix(const std::vector<Triangle>& triangles);
	void setVertexMatrix(const std::vector<std::vector<float>>& _vertexMatrix);
	std::vector<std::vector<float>> getVertexMatrix();

	void setGraph(const std::vector<std::vector<float>>& vertexMatrix);
	std::vector<std::vector<float>> getGraph();
};