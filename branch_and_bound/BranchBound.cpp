#include "BranchBound.h"
#include "Node.h"
#include <queue>
#include <iostream>
using namespace std;

class comp 
{
public:
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return lhs->cost > rhs->cost;
	}
};

BranchBound::BranchBound()
{
    lowerBound = 0;
    upperBound = 0;
    size = 0;
}

BranchBound::~BranchBound()
{
}

pair<int,string> BranchBound::findSolution(Graph* graph)
{
	priority_queue<Node*, std::vector<Node*>, comp> pq;
    vector<vector<int>> distance;
    distance = graph->getVector();
	size = graph->getSize();
	vector<pair<int, int>> path;

	Node* root = newNode(distance,path,0,-1,0);
    root->cost = cost_calculation(root->matrix);
	pq.push(root);
	upperBound = INT_MAX;
    lowerBound = root->cost;

    while(!pq.empty())
    {
		 Node* min = pq.top();
         pq.pop();
		 int currentVertex = min->vertex;

         if (min->level == size - 1)
         {
             min->path.push_back(make_pair(currentVertex, 0));
             printPath(min->path);
             min->cost += distance[currentVertex][0];
             return make_pair(min->cost, "");
         }

         for (int j = 0; j < size; j++)
         {
             if (min->matrix[currentVertex][j] != INT_MAX)
             {
                 Node* child = newNode(min->matrix, min->path, min->level + 1, currentVertex, j);
                 child->cost = min->cost + min->matrix[currentVertex][j]+ cost_calculation(child->matrix);
                 pq.push(child);
             }
         }
         /*for (auto i : pq)
         {

         }*/
         delete min;
    }
    return make_pair(0, "");
}

Node* BranchBound::newNode(vector<vector<int>> matrix_parent, vector<pair<int, int>> path, int level, int i, int j)
{
    Node* node = new Node();
    node->path = path;
    if (level != 0)
        node->path.push_back(make_pair(i, j));

    node->matrix = matrix_parent;

    for (int k = 0; level != 0 && k < size; k++)
    {
        node->matrix[i][k] = INT_MAX;
        node->matrix[k][j] = INT_MAX;
    }

    node->matrix[j][0] = INT_MAX;
    node->level = level;
    node->vertex = j;
    return node;
}

void BranchBound::reduce_row(vector<vector<int>> matrix_reduced, vector<int> row)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (matrix_reduced[i][j] < row[i])
                row[i] = matrix_reduced[i][j];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (matrix_reduced[i][j] != INT_MAX && row[i] != INT_MAX)
                matrix_reduced[i][j] -= row[i];
}

void BranchBound::reduce_column(vector<vector<int>> matrix_reduced, vector<int> col)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (matrix_reduced[i][j] < col[j])
                col[j] = matrix_reduced[i][j];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (matrix_reduced[i][j] != INT_MAX && col[j] != INT_MAX)
                matrix_reduced[i][j] -= col[j];
}

int BranchBound::cost_calculation(vector<vector<int>> matrix_reduced)
{
    int cost = 0;

    vector<int> row(size, INT_MAX);
    reduce_row(matrix_reduced, row);

    vector<int> col(size,INT_MAX);
    reduce_column(matrix_reduced, col);

    for (int i = 0; i < size; i++)
        cost += (row[i] != INT_MAX) ? row[i] : 0,
        cost += (col[i] != INT_MAX) ? col[i] : 0;

    return cost;
}

void BranchBound::printPath(vector<pair<int, int>> list)
{
    for (int i = 0; i < list.size(); i++)
        cout << list[i].first << " -> " << list[i].second << endl;
}