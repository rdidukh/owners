#include "Matrix.h"
#include "Algos.h"
#include "Graph.h"
#include <cassert>
#include <functional>

bool RecursionAlgo::calculate(const Matrix & inMtx, Matrix & outMtx)
{
	bool ret = preCheck(inMtx);

	if(!ret)
		return false;

    unsigned n = inMtx.rows();
    Graph graph(inMtx);

    if(graph.hasCycle())
    {
        setErrorString("Cycle dependency detected");
        return false;
    }

    outMtx = Matrix(n, n, 0.0);
    std::vector<int> visited(n, 0);

    unsigned source;

    std::function<void(unsigned, double)> calcRec = [&](unsigned v, double coef)
    {
        visited[v] = 1;

        if(source != v)
            outMtx[source][v] += coef;

        for ( auto edge : graph[ v ] )
        {
            assert(visited[ edge.first ]);
            calcRec(edge.first, coef*edge.second);
        }

        visited[v] = 0;
    };

    for(source = 0; source < n; source++)
    {
        calcRec(source, 1.0);
    }

	return true;
}
