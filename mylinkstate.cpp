// Zhelin Yu, Lab 3, Computer Networking
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <unistd.h>
#include <iomanip>
using namespace std;
#define INFINITE 1073741824

void dijkstra(const int srcNode, const int n, int **graph, bool flag);
void printlsrHeader(const int srcNode, const int n);
void printFTHeader(const int srcNode, const int n);

int main(int argc, char *argv[])
{
    //Error handling of prompt input
    if (argc < 4)
    {
        cout << "Error: Need to enter mylinkstate <input file> <node i> <flag> for running the program" << endl;
        return -1;
    }
    else if (argc > 4)
    {
        cout << ("Error: Too many arguments") << endl;
        return -2;
    }

    //Declaration of variables
    ifstream nodefile(argv[1]);
    int n = 0, srcNode = atoi(argv[2]);
    bool flag = argv[3][0] == '1' && argv[3][1]=='\0' ? true : false;
    auto start = chrono::steady_clock::now();

    //Check argument values
    if (nodefile.is_open())
    {
        nodefile >> n;
    }
    else
    {
        cout << "Error: The target file can not be opened." << endl;
        return -3;
    }

    if (srcNode < 1 || srcNode > n || n < 1)
    {
        cout << "Error: source node is incorrect or the number of node in the file is smaller than 1" << endl;
        return -4;
    }

    int **graph;
    graph = new int *[n + 1];
    graph[0] = NULL;

    // Initialization the graph
    for (int i = 0; i < n + 1; ++i)
    {
        graph[i] = new int[n + 1];
        graph[i][0] = -1;
    }
    int i, j, ptpDist;
    while (nodefile >> i >> j >> ptpDist)
    {
        graph[i][j] = ptpDist;
    }

    // Build routing table
    dijkstra(srcNode, n, graph, flag);
    auto end = chrono::steady_clock::now();
    cout << "Execution time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0 << "ms" << endl;
    return 0;
}

// use dijkstra algorithm to compute the shortest path from the target node to all other nodes
void dijkstra(const int srcNode, const int n, int **graph, const bool flag)
{
    int shortestDist[n + 1];
    int nodeIndex[n + 1];
    bool visited[n + 1];
    int forwardTable[n + 1];

    for (int i = 0; i < n + 1; i++)
    {
        shortestDist[i] = INFINITE;
        visited[i] = false;
        nodeIndex[i] = srcNode;
        forwardTable[i] = 0;
    }
    if (flag)
    {
        printlsrHeader(srcNode, n);
    }
    shortestDist[srcNode] = 0;
    int addNode = srcNode;
    int smallestDistNode;
    long smallestDictPerStep;
    string sourceNode = to_string(srcNode);
    string outputStr;
    for (int step = 0; step < n; step++)
    {
        if (flag)
        {
            printf("%-7d", step);
            printf("{%s}", sourceNode.c_str());
            cout << string(3 * n - sourceNode.length(), ' ');
        }
        smallestDictPerStep = INFINITE;
        for (int dstNode = 1; dstNode <= n; dstNode++)
        {
            outputStr = "";
            if (dstNode == srcNode)
            {
                continue;
            }
            else if (visited[dstNode] == true)
            {
                if (flag)
                    cout << setw(9) << left << "";
            }
            else
            {
                if (graph[dstNode][addNode] + shortestDist[addNode] < shortestDist[dstNode])
                {
                    shortestDist[dstNode] = graph[dstNode][addNode] + shortestDist[addNode];
                    nodeIndex[dstNode] = addNode;
                }
                if (shortestDist[dstNode] < smallestDictPerStep)
                {
                    smallestDictPerStep = shortestDist[dstNode];
                    smallestDistNode = dstNode;
                }
                if (flag)
                {
                    cout << setw(9) << left;
                    if (shortestDist[dstNode] == INFINITE)
                    {
                        outputStr.append("INF,");
                        outputStr.append(to_string(nodeIndex[dstNode]));
                        cout << outputStr;
                    }
                    else
                    {
                        outputStr.append(to_string(shortestDist[dstNode]));
                        outputStr.append(",");
                        outputStr.append(to_string(nodeIndex[dstNode]));
                        cout << outputStr;
                    }
                }
            }
        }
        addNode = smallestDistNode;
        visited[addNode] = true;
        if (flag)
        {
            sourceNode.append(",");
            sourceNode.append(to_string(addNode));
            cout << endl;
        }
    }

    cout << endl;
    printFTHeader(srcNode, n);
    for (int i = 1; i < n + 1; i++)
    {
        outputStr = "";
        if (i != srcNode)
        {
            int temp = i;
            while (nodeIndex[temp] != srcNode)
            {
                temp = nodeIndex[temp];
            }
            forwardTable[i] = temp;
            cout << setw(13) << left << i;
            cout << setw(10) << internal;
            outputStr.append("{").append(to_string(srcNode)).append(",").append(to_string(forwardTable[i])).append("}");
            cout << outputStr << endl;
        }
    }
}

// print the table header for Link state routing steps
void printlsrHeader(const int srcNode, const int n)
{
    cout << string((n - 1) * 9 + 7 + 3 * n, '-') << endl;
    cout << "Step   N'" << string(3 * n, ' ');
    for (int i = 1; i <= n; i++)
    {
        if (i != srcNode)
        {
            cout << setw(9) << left << i;
        }
    }
    cout << endl;
    cout << string((n - 1) * 9 + 7 + 3 * n, '-') << endl;
}

// print the table header for forwarding table
void printFTHeader(const int srcNode, const int n)
{
    cout << "Forwarding Table:" << endl;
    cout << "Destination  |  Link  " << endl;
    cout << string(24, '-') << endl;
}
