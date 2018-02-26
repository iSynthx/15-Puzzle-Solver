#include <iostream>
#include <array>
#include <limits>
#include <cstring>

#include "SearchMethods.h"

using namespace std;

int main(int argc, char const *argv[]){
    if(argc < 2 || (!strcmp(argv[1], "IDFS") && argc!=3)){
        cout << "Uso: " << argv[0] << " [Método de busca] [Opções de busca]" << endl;
        cout << "Tipos de busca:" << endl;
        cout << "   ASTAR -> efetua busca A*;" << endl;
        cout << "   GULOSA -> efetua busca Gulosa;" << endl;
        cout << "   BFS -> efetua busca em largura;" << endl;
        cout << "   DFS -> efetua busca em profundidade;" << endl;
        cout << "   IDFS [profundiade maxima] -> efetua busca em profundidade, onde profundidade máxima é o seu limite." << endl;
        return 1;
    }

    Node node = Node();
    node.display();

    array<int, 16> vec = {1, 0, 2, 4, 10, 11, 3, 7, 5, 15, 6, 8, 9, 13, 14, 12};
    Node node2 = Node(vec);
    node2.display();

    Config initialConfig = Config(vec);
    Config finalConfig = Config();

    clock_t clock1;
    clock_t clock2;

    if(!strcmp(argv[1], "DFS")){
        clock1 = clock();
        cout << "DFS path: " << DFS(initialConfig, finalConfig) << endl;
        clock2 = clock();
     }
     else if(!strcmp(argv[1], "IDFS")){
        clock1 = clock();
        cout << "IDFS path: " << IDFS(initialConfig, finalConfig, atoi(argv[2])) << endl;
        clock2 = clock();
    }
    else if(!strcmp(argv[1], "BFS")){
        clock1 = clock();
        cout << "BFS path: " << BFS(initialConfig, finalConfig) << endl;
        clock2 = clock();
    }
    else if(!strcmp(argv[1], "ASTAR")){
        clock1 = clock();
        cout << "A* path: " << ASTAR(initialConfig, finalConfig) << endl;
        clock2 = clock();
    }
    else
        cout << "Tipo de busca não existente." << endl;

    cout << "Tempo de execução: " << clock2-clock1 << endl;

    return 0;
}