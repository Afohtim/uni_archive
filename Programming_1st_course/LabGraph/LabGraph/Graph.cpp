#include "Graph.h"

template <class var>
var max(var x, var y)
{
	return x > y ? x : y;
}

template <class var>
var min(var x, var y)
{
	return x < y ? x : y;
}

Vertex::Vertex(int vertex_id)
{
	weight = 0;
	id = vertex_id;
}

Vertex::Vertex(int vertex_id, int vertex_weight)
{
	id = vertex_id;
	weight = vertex_weight;
}

void Graph::dfs(int vertex_id)
{
	(*used)[vertex_id] = 1;
	for (auto to : (*edges)[vertex_id])
	{
		if (!(*used)[to.id])
		{
			dfs(to.id);
		}
	}
	std::cout << vertex_id << '\n';
}

Graph::Graph(int number_of_vertices)
{
	graph_size = number_of_vertices;
	edges = new std::vector< std::vector < Vertex > >(number_of_vertices);
	used = new std::vector<int>(graph_size, 0);
}

Graph::~Graph()
{
	delete edges;
}

int Graph::vertex_connectivity()
{
	Graph double_graph(2 * graph_size);
	for (int i = 0; i < graph_size; ++i)
	{
		double_graph.add_directed_edge(graph_size + i + 1, i + 1, 1);
		for (int j = 0; j < (*edges)[i].size(); ++j)
		{
			double_graph.add_directed_edge(i + 1, graph_size + j + 1, 1);
		}
	}
	int first_vertex = 0, second_vertex = graph_size + 1;
	int res = double_graph.max_flow(first_vertex, second_vertex);
	for (int i = 0; i < graph_size; ++i)
	{
		first_vertex = i;
		for (int j = 0; j < graph_size; ++j)
		{
			second_vertex = graph_size + j;
			if (i != j)
			{
				res = min(res, double_graph.max_flow(first_vertex, second_vertex));
				std::cout << i << ' ' << j << ' ' << res << '\n';
			}
		}
	}
	return res;
}

void Graph::add_edge(int vertex_id1, int vertex_id2, int weight)
{
	(*edges)[vertex_id1 - 1].push_back(Vertex(vertex_id2 - 1));
	(*edges)[vertex_id2 - 1].push_back(Vertex(vertex_id1 - 1));
	(*edge_list).push_back(Edge(vertex_id1, vertex_id2, weight));
	(*edge_list).push_back(Edge(vertex_id2, vertex_id1, weight));
}

void Graph::add_directed_edge(int from, int to, int weight)
{
	(*edges)[from - 1].push_back(Vertex(to - 1, weight));
	(*edge_list).push_back(Edge(from, to, weight));
}

int Graph::max_flow(int start_vertex_id, int finish_vertex_id)
{
	int flow = 0;
	int cur_flow = 0;
	std::queue<int> to_visit;
	std::vector<std::pair<int, int> > info(graph_size);
	info[finish_vertex_id].first = -1;
	to_visit.push(start_vertex_id);
	std::vector< std::vector < Vertex > > edg(edges->begin(), edges->end());
	while(!to_visit.empty())
	{
		int v = to_visit.front();
		to_visit.pop();
		for (auto i = edg[v].begin();i != edg[v].end(); ++i)
		{
			Vertex to = *i;
			
				
			if (!(*used)[to.id])
			{
				(*used)[to.id] = 1;
				info[to.id].first = v;
				info[to.id].second = to.weight;
				to_visit.push(to.id);
				if (to.id == finish_vertex_id)
				{
					break;
				}
			}
		}
		while (!to_visit.empty())
			to_visit.pop();

		if (info[finish_vertex_id].first == -1)
			return flow;
		else
		{
			int cur_vertex = finish_vertex_id;
			int cur_flow = info[cur_vertex].second;
			while (cur_vertex != start_vertex_id)
			{
				cur_flow = min(cur_flow, info[cur_vertex].second);
				cur_vertex = info[cur_vertex].first;

			}
			flow += cur_flow;

			cur_vertex = finish_vertex_id;
			while (cur_vertex != start_vertex_id)
			{
				for (int i = 0; i < edg[info[cur_vertex].first].size(); ++i)
				{
					if (edg[info[cur_vertex].first][i].id == cur_vertex)
					{
						edg[info[cur_vertex].first][i].weight -= cur_flow;
						cur_vertex = info[cur_vertex].first;
						break;
					}
				}
				
			}
		}

		info[finish_vertex_id].first = -1;
		to_visit.push(start_vertex_id);
	}
	return flow;
}

void Graph::test()
{
	for (int vertex = 0; vertex < graph_size; ++vertex)
	{
		if (!(*used)[vertex])
		{
			dfs(vertex);
		}
	}
	std::cout << '\n';
	used->assign(graph_size, 0);

}

void Graph::sort()
{
	std::vector<std::pair<int,int> > positions(graph_size);
	for (int i = 0; i < graph_size; ++i)
	{
		positions[i] = { (*edges)[i].size(), i };
	}
	for (int i = 2; i < graph_size; i)
	{

	}

}

Edge::Edge(int id1, int id2, int edge_weight)
{
	u = id1;
	v = id2;
	weight = edge_weight;
}
