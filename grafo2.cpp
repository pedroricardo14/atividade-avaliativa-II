#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <direct.h> // _getcwd
using namespace std;

class Graph {
public:
    int vertices;
    vector<vector<int> > adjMatrix;

    Graph(int v = 0) : vertices(v) {
    adjMatrix.resize(v, vector<int>(v, 0));
    }

    bool readFromFile(const string& filename = "grafo.txt") {
    ifstream file(filename.c_str());
        if (!file) {
            // Se falhar, mostre diagnóstico de onde estamos tentando abrir o arquivo
            char buf[1024];
            if (_getcwd(buf, sizeof(buf)) != NULL) {
                cout << "Erro ao abrir arquivo '" << filename << "' no diretorio: " << buf << endl;
            } else {
                cout << "Erro ao abrir arquivo '" << filename << "' (diretorio atual desconhecido)" << endl;
            }
            return false;
        }

        file >> vertices;
        adjMatrix.assign(vertices, vector<int>(vertices, 0));

        int u, v, w;
        while (file >> u >> v >> w) {
            if (u < vertices && v < vertices)
                adjMatrix[u][v] = w;
        }
        file.close();
        cout << "Grafo carregado de " << filename << endl;
        return true;
    }

    // Exibe lista de adjacência
    void printAdjacencyList() {
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

    void floydWarshall() {
        const int INF = 99999;
    vector<vector<int> > dist(vertices, vector<int>(vertices));

        // Inicializa matriz de distâncias
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (i == j)
                    dist[i][j] = 0;
                else if (adjMatrix[i][j] != 0)
                    dist[i][j] = adjMatrix[i][j];
                else
                    dist[i][j] = INF;
            }
        }

        // Floyd-Warshall
        for (int k = 0; k < vertices; k++) {
            for (int i = 0; i < vertices; i++) {
                for (int j = 0; j < vertices; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        // Exibe matriz final de distâncias
        cout << "\nMatriz de distancias (Floyd-Warshall):\n";
        cout << "   ";
        for (int j = 0; j < vertices; j++) cout << setw(5) << j;
        cout << endl;
        for (int i = 0; i < vertices; i++) {
            cout << setw(3) << i;
            for (int j = 0; j < vertices; j++) {
                if (dist[i][j] == INF)
                    cout << setw(5) << "INF";
                else
                    cout << setw(5) << dist[i][j];
            }
            cout << endl;
        }
    }
};

int main(int argc, char* argv[]) {
    // Nome do arquivo: se o usuário passar argumento, usa argv[1], senão usa grafo.txt
    string filename = "grafo.txt";
    if (argc >= 2) filename = argv[1];

    Graph g;
    if (g.readFromFile(filename)) {
        cout << "Usando arquivo: " << filename << "\n";
        // Mostrar a lista de adjacência para que o usuário veja o grafo carregado
        g.printAdjacencyList();
        g.floydWarshall();
        return 0;
    } else {
        // Falha ao abrir arquivo; já exibimos mensagem em readFromFile
        cerr << "Nao foi possivel carregar o arquivo: " << filename << "\n";
        return 1;
    }
}
