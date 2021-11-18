#include "Node.h"

Node::Node(vector<vector<int>> matrix, vector<pair<int, int>> path, int cost, int vertex, int level)
{
	this->matrix = matrix;
	this->path = path;
	this->cost = cost;
	this->level = level;
	this->vertex = vertex;
}

Node::~Node()
{
}

Node::Node()
{
}
