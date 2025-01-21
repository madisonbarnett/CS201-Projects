#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <limits>
#include <queue> //Added queue library

/* 
Name: Madison Barnett
Email: mtbarnett@crimson.ua.edu
Course Section: Fall 2024 CS 201 - 002
Homework #: 4
To Compile: g++ -Wall -std=c++20 GraphDemo.cpp (Driver program)
To Run: ./a.exe (input file) (Driver program)
*/

class Vertex {
public:
	bool visited;
	int distance;
	int previous;
	int finish;
	std::list<int> adj;
};

class Graph {
public:
	Graph(int V, int E, std::pair<int, int> *edges) {
		_V = V;
		_E = E;
		vertices = new Vertex[_V];
		for (int i = 0; i < _V; i++) {
                    vertices[i].visited = false;
                    vertices[i].distance = 65535; // Instead using INFINITY, you can use a large int number to initialize your graph
                    vertices[i].previous = -1;
		}
		for (int i = 0; i < _E; i++) {
		    addEdge(edges[i].first, edges[i].second);
		}
	}

	virtual ~Graph() {
		for (int i=0; i<_V; ++i) {
		    auto adj = vertices[i].adj;
		    adj.clear(); // clear list
		}

		delete[] vertices; // delete array of vertices
	}

	int V() {
		return _V;
	}

	int E() {
		return _E;
	}

	void addEdge(int u, int v) {
		vertices[u].adj.push_back(v);
	}

	std::list<int> getEdges(int u) {
		return vertices[u].adj;
	}

	int degree(int u) {
		return vertices[u].adj.size();
	}

	void bfs(int s) {
		// your implementation goes here
		for (int i=0; i<_V; ++i) {
			vertices[i].visited = false;
			vertices[i].distance = 65535; // Instead using INFINITY, you can use a large int number to initialize your graph
            vertices[i].previous = -1;
		}
		vertices[s].visited = true;
		vertices[s].distance = 0;
		vertices[s].previous = -1;

		// Added queue to ensure FIFO order of search
		std::queue<int> discovered;
		discovered.push(s);

		while (!discovered.empty()) {
			int u = discovered.front();
			discovered.pop();

			// Add each adjacent vertex of u to queue
			for (int v : vertices[u].adj) {
				if (vertices[v].visited == false) {
					vertices[v].visited = true;
					vertices[v].distance = vertices[u].distance + 1;
					vertices[v].previous = u;
					discovered.push(v);
				}
			}
			vertices[u].visited = true;
		}
	}

	void dfs() {
		// your implementation goes here
		for (int i=0; i<_V; ++i) {
			vertices[i].visited = false;
            vertices[i].previous = -1;
		}
		time = 0;
		for (int j=0; j<_V; ++j) {
			if (vertices[j].visited == false) {
				dfs_visit(j);
			}
		}
	}

	void dfs_visit(int u) {
		// your implementation goes here
		time += 1;
		vertices[u].distance = time;
		vertices[u].visited = true;
		// Print upon discovery
		std::cout << u << " ";

		for (int v : vertices[u].adj) {
			if (vertices[v].visited == false) {
				vertices[v].previous  = u;
				dfs_visit(v);
			}
		}

		time = time + 1;
		vertices[u].visited = true;
		vertices[u].finish = time;
		// Print upon finish
		std::cout << u << " ";
	}

	void print_path(int s, int v) {
		if (v == s)
		   std::cout << s;
		else if (vertices[v].previous == -1)
		   std::cout << "not connected";
		else {
		   print_path(s,vertices[v].previous);
		   std::cout << "->" << v;
		}
	}

	std::string toString() {
		std::stringbuf buffer;
		std::ostream os(&buffer);
		os << "Vertices = " << _V << ", Edges = " << _E << std::endl;
		for (int i = 0; i < _V; ++i) {
		    os << i << "(" << degree(i) << "): ";
		    for (const auto& l : vertices[i].adj) 
			os << l << " ";
		    os << std::endl;
		}

		return buffer.str();
	}
private:
	int _V; // no. of vertices
	int _E; // no. of edges
	Vertex *vertices; // array of vertices
	int time; //Added global variable time for DFS
};

#endif
