#pragma once

#ifndef FILE_GRAPH_H
#define FILE_GRAPH_H

#include <vector>
#include <list>
#include <string>

#include "Matrix.h"

class Graph
{
public:

	explicit Graph(const Matrix & mtx);

	bool fail() const;
	std::string getErrorString() const;
	bool hasCycle() const;
	std::vector<unsigned> topSort() const;

	static Graph generateDAG(unsigned n, double edgeProb = 0.5);
	static void printDAG(const Graph & graph);

private:
	std::vector<std::list<std::pair<int, double>>> graph;
	bool failBit;
	std::string errStr;
};

#endif // FILE_GRAPH_H