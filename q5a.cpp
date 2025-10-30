#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node *left, *right;
    Node(int k) : key(k), left(NULL), right(NULL) {}
};

class BST {
public:
    Node* root;
    BST() : root(NULL) {}

    Node* insert(Node* n, int k) {
        if (!n) return new Node(k);
        if (k < n->key) n->left = insert(n->left, k);
        else n->right = insert(n->right, k);
        return n;
    }
    void insert(int k) { root = insert(root, k); }

    bool isFull(Node* n) {
        if (!n) return true; // árvore vazia é considerada cheia
        if (!n->left && !n->right) return true; // folha
        if (n->left && n->right) return isFull(n->left) && isFull(n->right);
        return false; // nó com só um filho
    }
};

int main() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    // árvore é cheia aqui (raiz tem dois filhos e ambos são folhas)
    cout << (tree.isFull(tree.root) ? "Arvore cheia\n" : "Arvore NAO cheia\n");

    tree.insert(2); // agora nó 5 terá só um filho -> não cheia
    cout << (tree.isFull(tree.root) ? "Arvore cheia\n" : "Arvore NAO cheia\n");

    return 0;
}
