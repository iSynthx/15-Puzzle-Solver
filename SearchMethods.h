/*Search Functions for the 15-Puzzle*/

#include <iostream>
#include <array>
#include <deque>
#include <limits>
#include <string>
#include <cmath>
#include <algorithm>

#include "Heuristics.h"

using namespace std;

//Prototype declarations
unsigned int inversions(Config &initialConfig);
bool solutionExists(Config &initialConfig, Config &finalConfig);
string GENERAL_SEARCH(Config &initialConfig, Config &finalConfig, int pos, unsigned int maxDepth);
string DFS(Config &initialConfig, Config &finalConfig);
string BFS(Config &initialConfig, Config &finalConfig);
string BFS(Config &initialConfig, Config &finalConfig, int i);
string LDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth);
string IDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth);
string ASTAR(Config &initialConfig, Config &finalConfig);
void GreedyWithHeuristics();

void insertionSort(array<Node*, 4> &v){
    for(size_t i=0; i<4 && v[i]!=NULL; i++){
        for(size_t j=i; j>0 && *v[j-1]>*v[j]; j--)
            swap(v[j-1], v[j]);
    }
}

//Function to check if we can reach a solution from the initial configuration
unsigned int inversions(Config &initialConfig){
    unsigned int n=0;

    array< array<int, 4>, 4> matrix = initialConfig.getMatrix();

    array<int, 16> arr;
    for(unsigned int i=0; i < 4; i++){
        for(unsigned int j=0; j < 4; j++)
            arr[i*4 + j] = matrix[i][j];
    }

    for(unsigned int i=0; i < 16; i++){
        n += arr[i];
        for(unsigned int j=0; j <= i; j++){
            if(arr[i] >= arr[j] && arr[i]!=0 && arr[j]!=0)
                n--;
        }
    }

    return n;
}

bool solutionExists(Config &initialConfig, Config &finalConfig){
    return ((inversions(initialConfig)%2 == 0) == (abs((int)initialConfig.getEmptyRowIndex()-4)%2 == 1)) == 
            ((inversions(finalConfig)%2 == 0) == (abs((int)finalConfig.getEmptyRowIndex()-4)%2 == 1));
}

//General Search Algorithm to search for a solution
string GENERAL_SEARCH(Config &initialConfig, Config &finalConfig, int pos, unsigned int maxDepth, unsigned int& generatedNodes){
    Node *initialNode = new Node(initialConfig);
    Node *solution = new Node(finalConfig);

    generatedNodes+=2;

    if(!solutionExists(initialConfig, finalConfig)){
        delete initialNode;
        delete solution;
        return "Solution not found";    //There is no solution
    }

    deque<Node*> q;  //Double-Ended QUEue to be able to insert in the front or the back, depending on the pos (or function iterator)
    q.push_back(initialNode);

    while(!q.empty()){
        Node *removed = q.front();
        q.pop_front();

        if(removed->getDepth() >= maxDepth)
            continue;
        else if(removed->getConfig() == solution->getConfig()){
            string str = removed->makePath();
            delete initialNode;
            delete solution;
            return str;
        }

        array<Node*, 4> descendantList = removed->makeDescendants();

// Se pos for 0, entao a funcao de inserir na fila vai inserir os elementos no inicio da fila
// Se pos for 1, entao a funcao de inserir na fila vai inserir os elementos no fim da fila

//em vez de pos meter um iterator
//adicionamos ao elemento q essa função para poder fazer q.begin() etc

        if(pos == 0){
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push_front(descendantList[i]);
            }
        }
        else if (pos == 1){
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push_back(descendantList[i]);
            }
        }
        else{   //pos == 2, using A*
            calcPathCost(descendantList,solution->getConfig()); //calculates the pathCost for each of the children Nodes
            insertionSort(descendantList);  //sorts array so that the children Node with the less pathCost enters first in the queue
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push_back(descendantList[i]);
            }
        }
    }

    delete initialNode;
    delete solution;

    return "Solution not found";
}

string DFS(Config &initialConfig, Config &finalConfig){ /*Depth first search function*/
    unsigned int generatedNodes = 0;
    string str = GENERAL_SEARCH(initialConfig, finalConfig, 0, 25, generatedNodes);
    cout << "Nós gerados: " << generatedNodes << endl;
    return str;
}

string BFS(Config &initialConfig, Config &finalConfig){ /*Breadth first search function*/
    unsigned int generatedNodes = 0;
    string str = GENERAL_SEARCH(initialConfig, finalConfig, 1, 25, generatedNodes);
    cout << "Nós gerados: " << generatedNodes << endl;
    return str;
}

/*BFS with Heuristics : has another argument "FLAG" : function overloading*/
string BFS(Config &initialConfig, Config &finalConfig, int i){
    unsigned int generatedNodes = 0;
    string str = GENERAL_SEARCH(initialConfig, finalConfig, i, 25, generatedNodes);
    cout << "Nós gerados: " << generatedNodes << endl;
    return str;
}

string LDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth){ /*Limited Breadth first search function*/
    unsigned int generatedNodes = 0;
    string str = GENERAL_SEARCH(initialConfig, finalConfig, 0, maxDepth, generatedNodes);
    cout << "Nós gerados: " << generatedNodes << endl;
    return str;
}

string IDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth){  /*Iterative Depth first search function*/
    for(unsigned int i=1; i<=maxDepth; i++){
        unsigned int generatedNodes = 0;
        string str = GENERAL_SEARCH(initialConfig, finalConfig, 0, i, generatedNodes);
        cout << "Altura: " << i << "   \tNós gerados: " << generatedNodes << endl;
        if(str != "Solution not found")
            return str;
    }

    return "Solution not found";
}
string ASTAR(Config &initialConfig, Config &finalConfig){   /*A* search function calls overloaded 2nd version of BFS*/
    return BFS(initialConfig, finalConfig, 2);
}

void GreedyWithHeuristics() /*Greedy with Heuristics search function*/
{}