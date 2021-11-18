#pragma once
#include <vector>
using namespace std;

class Node
{
public:
	Node(vector<vector<int>>, vector<pair<int, int>>, int, int, int);
	~Node();
	Node();
	vector<pair<int, int>> path;
	vector<vector<int>> matrix;
	int cost;
	int vertex;
	int level;
};

