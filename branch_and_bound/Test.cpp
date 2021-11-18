#include "Test.h"
#include <windows.h>
#include <iostream>
#include "BranchBound.h"
#include "DataReader.h"
#include "Graph.h"
#include <iomanip>
#include <fstream>
using namespace std;

void Test::runTest()
{
    Graph* graph = new Graph();
    long long int frequency, start = 0, elapsed, sum, size = 0;
    pair<int, string> result;
    int nmbrOfTests = 1;
    string path = "";
    pair<int[3], string[2]>* initValues = DataReader::readInitData();

    if (initValues == nullptr)
    {
        cout << "Program konczy prace." << endl;
        return;
    }

    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

    int numberOfFiles = initValues[0].first[0];
    string outputName = initValues[0].second[0] + ".csv";
    ofstream outputFile;
    outputFile.open(outputName);
    outputFile << "Nazwa pliku,czas[s],czas[ms],ilosc testow\n";

    for (int k = 1; k < numberOfFiles; k++)
    {
        sum = 0; path = ""; graph = DataReader::readFile((initValues[k].second[0]));
        size = graph->getSize();
        graph->showMatrix();

        cout << endl << "================ " << initValues[k].second[0] << " ================ " << endl;
        cout << "================ Liczba testow " << initValues[k].first[0] << " ================ " << endl << endl;

        for (int i = 0; i < initValues[k].first[0]; i++)
        {
            BranchBound* bb = new BranchBound();
            start = read_QPC();
            result = bb->findSolution(graph);
            elapsed = read_QPC() - start;
            sum += elapsed;
            delete bb;
        }

        printResult(size, sum, initValues[k].first[0], result.second, result.first, frequency);
        outputFile << initValues[k].second[0] << "," << float(sum) / (initValues[k].first[0]) / frequency << "," << setprecision(3) << float(sum * 1000.0) / (initValues[k].first[0]) / frequency << "," << initValues[k].first[0] << ", " << path << "\n";
    }
    outputFile.close();
    cout << "Wyniki zapisano do: " << outputName << endl << endl;
}

long long int Test::read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

void Test::printResult(int size, long long int sum, int test, string& path, int result, long long int f)
{
    cout << "Optymalna droga ma dlugosc: " << result << endl << "Optymalna droga: ";
    cout << path << endl;
    cout << "Sredni czas operacji[s] = " << setprecision(3) << float(sum / float(test)) / f << endl;
    cout << "Sredni czas operacji[ms] = " << setprecision(3) << float(sum * 1000.0) / float(test) / f << endl;
    cout << "Sredni czas operacji [us] = " << setprecision(3) << float(sum * 1000000.0) / float(test) / f << endl << endl;
}
