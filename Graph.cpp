#include "Graph.h"
#include <functional>
#include <algorithm>
#include <ctime>

Graph::Graph(const Matrix & mtx)
{
	if(mtx.rows() != mtx.cols())
	{
		failBit = true;
		errStr = "Matrix is not square";
		return;
	}

	unsigned n = mtx.rows();

	graph.clear();
	graph.resize(n);

	for(unsigned i = 0; i < n; i++)
		for(unsigned j = 0; j < n; j++)
			graph[i].emplace_back(j, mtx[i][j]);
}

const std::list<std::pair<int, double>> & Graph::operator[]( size_t index ) const
{
    return graph[index];
}

bool Graph::fail() const
{
	return failBit;
}

std::string Graph::getErrorString() const
{
	return errStr;
}

bool Graph::hasCycle() const
{
	unsigned n = graph.size();
	std::vector<int> visited(n, 0);
	std::vector<int> inRec(n, 0);

	std::function<bool(unsigned)> hasCycleRec = [&hasCycleRec, this, &visited, &inRec](unsigned v)
	{
		visited[v] = 1;
		inRec[v] = 1;

		for(auto edge : graph[v])
		{
			unsigned w = edge.first;
			if(inRec[w]) return true;
			if(!visited[w] && hasCycleRec(w)) return true;
		}
		inRec[v] = 0;
		return false;
	};

	for(unsigned i = 0; i < n; i++)
		if(!visited[i])
			if(hasCycleRec(i)) return true;


	return false;
}

std::vector<unsigned> Graph::topSort() const
{
	unsigned n = graph.size();
	std::vector<int> visited(n, 0);
	std::vector<unsigned> result;
	std::function<void(unsigned)> tsRec = [&tsRec, this, &visited, &result](unsigned v)
	{
		visited[v] = true;
		for(auto & edge : graph[v])
		{
			unsigned w = edge.first;
			if(!visited[w])
				tsRec(w);
		}
		result.push_back(v);
	};

	for(unsigned i = 0; i < n; i++)
		if(!visited[i])
			tsRec(i);

    std::reverse(result.begin(), result.end());

	return result;
}

Graph Graph::generateDAG(unsigned n, double edgeProb /* = 0.5 */)
{
	srand(static_cast<unsigned>(time(NULL)));

	auto randf = []()
	{
		return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
	};

	Matrix mtx(n, n);

	std::vector<unsigned> vec(n);
	std::vector<double> inSum(n, 0.0);
	for(unsigned i = 0; i < n; i++)
		vec[i] = i;

	for(unsigned i = n; i > 0; i--)
	{
		unsigned v = rand() % i;
		std::swap(vec[i - 1], vec[v]);
	}

	for(unsigned w = 0; w < n; w++)
	{
		for(unsigned v = 0; v < w; v++)
		{
			if(inSum[v] < 1.0 && edgeProb != 0.0 && randf() <= edgeProb)
			{
                double weight = randf()*(1.0 - inSum[w]);
				inSum[w] += weight;
				unsigned from = vec[v];
				unsigned to = vec[w];
				mtx[from][to] = weight;
			}
		}
	}

	return Graph(mtx);
}

bool Graph::test( )
{

    return true;
}
