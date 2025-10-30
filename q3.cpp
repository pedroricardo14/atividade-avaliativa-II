#include <iostream>
#include <vector>
#include <string>
using namespace std;

class PersonNode {
public:
    string nome;
    char sexo; // 'M' ou 'F'
    int idade;
    double peso;
    PersonNode *left, *right;

    PersonNode(string n, char s, int i, double p)
        : nome(n), sexo(s), idade(i), peso(p), left(NULL), right(NULL) {}
};

class PersonBST {
public:
    PersonNode* root;
    PersonBST() : root(NULL) {}

    PersonNode* insert(PersonNode* node, const string& nome, char sexo, int idade, double peso) {
        if (!node) return new PersonNode(nome, sexo, idade, peso);
        if (nome < node->nome) node->left = insert(node->left, nome, sexo, idade, peso);
        else if (nome > node->nome) node->right = insert(node->right, nome, sexo, idade, peso);
        else {
            // mesmo nome: atualizar campos (ou incrementar contador se desejado)
            node->sexo = sexo; node->idade = idade; node->peso = peso;
        }
        return node;
    }
    void insert(const string& nome, char sexo, int idade, double peso) {
        root = insert(root, nome, sexo, idade, peso);
    }

    // gera duas listas ordenadas por nome (in-order traversal)
    void gerarListas(PersonNode* node, vector<PersonNode*>& homens, vector<PersonNode*>& mulheres) {
        if (!node) return;
        gerarListas(node->left, homens, mulheres);
        if (node->sexo == 'M') homens.push_back(node);
        else if (node->sexo == 'F') mulheres.push_back(node);
        gerarListas(node->right, homens, mulheres);
    }
};

int main() {
    PersonBST tree;
    tree.insert("Carlos", 'M', 30, 75.5);
    tree.insert("Ana", 'F', 25, 60.0);
    tree.insert("Bruno", 'M', 40, 82.0);
    tree.insert("Diana", 'F', 22, 55.3);
    tree.insert("Beatriz", 'F', 28, 62.1);

    vector<PersonNode*> homens;
    vector<PersonNode*> mulheres;
    tree.gerarListas(tree.root, homens, mulheres);

    cout << "Homens (ordenados por nome):\n";
    for (size_t i=0;i<homens.size();++i) { PersonNode* p = homens[i]; cout << p->nome << " - " << p->idade << " anos\n"; }

    cout << "\nMulheres (ordenadas por nome):\n";
    for (size_t i=0;i<mulheres.size();++i) { PersonNode* p = mulheres[i]; cout << p->nome << " - " << p->idade << " anos\n"; }

    return 0;
}
