#include "Graph.h"
#include "Node.h"
#include <string>
#include <vector>
using namespace std;

class BranchBound
{
private:
	int lowerBound;
	int upperBound;
    int size;
public:
	BranchBound();
	~BranchBound();
    pair<int, string> findSolution(Graph*);
    Node* newNode(vector<vector<int>>, vector<pair<int, int>>, int , int , int );
    void reduce_row(vector<vector<int>>, vector<int> );
    void reduce_column(vector<vector<int>> , vector<int>  );
    int cost_calculation(vector<vector<int>> );
    void printPath(vector<pair<int, int>> );
};

