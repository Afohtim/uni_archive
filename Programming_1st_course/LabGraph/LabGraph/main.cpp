#include "Graph.h"
#include <string>

using namespace std;

int command(Graph &g, int graph_size)
{
	string s;
	cin >> s;
	if(s == "end")
	{
		return 1;
	}
	else if (s == "add")
	{
		int u, v;
		cin >> u >> v;
		g.add_edge(u, v);
	}
	else if (s == "test")
	{
		g.test();
	}
	else if (s == "v")
	{
		cout << g.vertex_connectivity() << '\n';
	}
	else
	{
		cout << "Wrong command\n";
	}
	return 0;
}

int main()
{
	int graph_size;
	cout << "Enter graph size\n";
	cin >> graph_size;
	Graph g(graph_size);
	while (true)
	{
		if (command(g, graph_size) == 1)
		{
			break;
		}
	}
	return 0;
}

/*
3
add 1 2
add 1 3
add 2 3
*/