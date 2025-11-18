#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int> > adjMatrix;

public:
    Graph(int v = 0) {
        vertices = v;
    adjMatrix.resize(v, vector<int>(v, 0));
    }

    // Lê grafo de arquivo .txt
    void readFromFile(const string& filename = "grafo.txt") {
    ifstream file(filename.c_str());
        if (!file) {
            cout << "Erro ao abrir arquivo " << filename << endl;
            return;
        }

        file >> vertices;
        adjMatrix.assign(vertices, vector<int>(vertices, 0));

        int u, v, w;
        while (file >> u >> v >> w) {
            if (u < vertices && v < vertices)
                adjMatrix[u][v] = w;
        }
        file.close();
        cout << "Grafo lido com sucesso de " << filename << endl;
    }

    // Inserção de arco
    void addEdge(int u, int v, int w = 1) {
        if (u < vertices && v < vertices) {
            adjMatrix[u][v] = w;
            cout << "Aresta inserida: " << u << " -> " << v << " peso " << w << endl;
        } else {
            cout << "Vertice invalido!\n";
        }
    }

    // Remoção de arco
    void removeEdge(int u, int v) {
        if (u < vertices && v < vertices && adjMatrix[u][v] != 0) {
            adjMatrix[u][v] = 0;
            cout << "Aresta removida: " << u << " -> " << v << endl;
        } else {
            cout << "Aresta nao encontrada!\n";
        }
    }

    // Exibe lista de adjacência
    void printList() {
        cout << "\nLista de adjacencia:\n";
        for (int i = 0; i < vertices; i++) {
            cout << i << " -> ";
            for (int j = 0; j < vertices; j++) {
                if (adjMatrix[i][j] != 0)
                    cout << j << "(" << adjMatrix[i][j] << ") ";
            }
            cout << endl;
        }
    }

};

// Pequeno main de teste
int main() {
    Graph G(5);
    G.addEdge(0,1,10);
    G.addEdge(0,2,5);
    G.addEdge(1,3,2);
    G.printList();
    return 0;
}