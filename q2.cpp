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

    // Função recursiva que encontra o maior valor
    Node* findMax(Node* node) {
        if (!node) return NULL;
        if (node->right == NULL) return node;
        return findMax(node->right);
    }
};

int main() {
    BST tree;
    int seq[] = {20, 5, 12, 36, 27, 45, 9, 2, 6, 17, 40};
    int n = sizeof(seq)/sizeof(seq[0]);
    for (int i = 0; i < n; ++i) tree.insert(seq[i]);

    Node* maxNode = tree.findMax(tree.root);
    if (maxNode) cout << "Maior valor na arvore: " << maxNode->key << "\n";
    else cout << "Arvore vazia.\n";
    return 0;
}