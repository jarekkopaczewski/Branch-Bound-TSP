#pragma once
#include <string>
#include "Graph.h"
#include <string>
using namespace std;

static class DataReader
{
public:
    static Graph* readFile(std::string);
    static pair<int[3], string[2]>* readInitData();
    static std::string readName();
};
