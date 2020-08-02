#pragma once
#include <vector>
#include <iostream>
#include <queue>

struct Vertex
{
	Vertex(int vertex_id);
	Vertex(int vertex_id, int vertex_weight);
	int id;
	int weight;
};

struct Edge
{
	Edge(int id1, int id2, int edge_weight);
	int u;
	int v;
	int weight;
};

class Graph
{
private:
	std::vector< std::vector < Vertex > > *edges;
	std::vector<Edge>  *edge_list;
	std::vector<int> *used;;
	int graph_size;
	void dfs(int vertex_id);
public:
	Graph(int number_of_vertices);
	~Graph();

	int vertex_connectivity();
	void add_edge(int vertex_id1, int vertex_id2, int weight = 0);
	void add_directed_edge(int from, int to, int weight = 0);
	int max_flow(int start_vertex_id, int finish_vertex_id);
	void test();
	void sort();
};

