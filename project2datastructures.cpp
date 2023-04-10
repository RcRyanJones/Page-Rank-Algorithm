#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <math.h>
using namespace std;
//TAs that helped: Amay, Antonio, Yair, Andrew K, Andrew P, Sara, Nitin, Julia
class AdjacencyList {
private:
    //Think about what member variables you need to initialize
public:
    //Think about what helper functions you will need in the algorithm
    map<string, vector<string>> coolGraph;
    map<string, int> inDegMap;//map for in degree
    map <string, int> outDegMap;//map for out degree
    map <string, float> rankMap;//regular rank
    map <string, float> tempRankMap;//temp rank for 1 it behind rank map

    void addEdge(string one, string two);
    void inDegreeCalculator(string node, map<string, vector<string>> graph);
    void outDegreeCalculator(string node, map<string, vector<string>> graph);
    void pageRank(int power_iterations);
    void printer();
    bool compare(string a, string b);

};

void AdjacencyList::addEdge(string one, string two) {//cleaned it all up
    coolGraph[two].push_back(one);
    if (coolGraph.find(one) == coolGraph.end()) {
        coolGraph[one] = {};//adds, if it's already in there skip
    }
}

void AdjacencyList::outDegreeCalculator(string nodey, map<string, vector<string>> graph) {
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        for (int i = 0; i < (it->second.size()); i++) {
            if (it->second.at(i) == nodey) {
                outDegMap[nodey]++;//increments outdeg at given node
            }
        }
    }
}

void AdjacencyList::inDegreeCalculator(string nodey, map<string, vector<string>> graph) {
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        if (it->first == nodey) {
            inDegMap[nodey] = it->second.size();//sets in deg based on size of vect
        }
    }
}

void AdjacencyList::printer() {
    for (auto it = coolGraph.begin(); it != coolGraph.end(); ++it) {//here's where it repeats what is connected
        cout << it->first << " ";//<< rankMap[it->first] << endl;
        printf("%.2f", rankMap[it->first]);
        cout << endl;
    }
}

void AdjacencyList::pageRank(int power_iterations) {
    for (int i = 0; i < power_iterations - 1; i++) {//power could be a problem
        for (auto it = coolGraph.begin(); it != coolGraph.end(); ++it) {
            float sum = 0;
            for (int j = 0; j < it->second.size(); j++) {
                sum += rankMap[it->second.at(j)] / outDegMap[it->second.at(j)];
            }//sum = sum + sum += rankmap/outdeg at position
            tempRankMap[it->first] = sum;
        }
        for (auto it = coolGraph.begin(); it != coolGraph.end(); ++it) {
            rankMap[it->first] = tempRankMap[it->first];
        }
    }
    printer();//goes to print, remeber to format
}

bool compare(string a, string b) {
    return a < b;
}//avg compare func



int main() {
    AdjacencyList adjList;
    int no_of_lines, power_iterations;
    string from, to;
    cin >> no_of_lines;
    cin >> power_iterations; //basic code from class example
    for (int i = 0; i < no_of_lines; i++) {
        std::cin >> from; //
        std::cin >> to;
        adjList.addEdge(from, to); //adds edeg with from[to]
    }
    for (auto it = adjList.coolGraph.begin(); it != adjList.coolGraph.end(); ++it) {//cool graph as object of adjacency list class
        adjList.inDegreeCalculator(it->first, adjList.coolGraph);
        adjList.outDegreeCalculator(it->first, adjList.coolGraph);
    }//creates values to go into maps
    for (auto it = adjList.coolGraph.begin(); it != adjList.coolGraph.end(); ++it) {
        adjList.rankMap[it->first] = 1.0 / adjList.coolGraph.size();
        adjList.tempRankMap[it->first] = 1.0 / adjList.coolGraph.size();
    }//loops through adding to both maps
    adjList.pageRank(power_iterations);//sends to page rank calc which goes to printer
    return 0;
}