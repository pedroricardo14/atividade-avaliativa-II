#include <iostream>
using namespace std;

class Node {
public:
    int key;
    int count;
    Node *left, *right;
    Node(int k) : key(k), count(1), left(NULL), right(NULL) {}
};

class BST {
public:
    Node* root;
    BST() : root(NULL) {}

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else node->count++; // chave repetida
        return node;
    }
    void insert(int key) { root = insert(root, key); }

    Node* minValueNode(Node* node) {
        Node* cur = node;
        while (cur && cur->left) cur = cur->left;
        return cur;
    }

    Node* remove(Node* node, int key) {
        if (!node) return node;
        if (key < node->key) node->left = remove(node->left, key);
        else if (key > node->key) node->right = remove(node->right, key);
        else {
            // se contador > 1, só decrementa
            if (node->count > 1) {
                node->count--;
                return node;
            }
            // senão remove o nó fisicamente
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* temp = minValueNode(node->right);
                node->key = temp->key;
                node->count = temp->count;
                // reset do contador no nó que foi copiado (evita duplicação de contagem)
                temp->count = 1;
                node->right = remove(node->right, temp->key);
            }
        }
        return node;
    }
    void remove(int key) { root = remove(root, key); }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << "(" << node->count << ") ";
        inorder(node->right);
    }
};

int main() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(10);
    tree.insert(10);
    tree.insert(3);

    cout << "Antes: ";
    tree.inorder(tree.root);
    cout << "\n";

    tree.remove(10); // decrementa contador
    cout << "Depois de remover 10 (uma ocorrencia): ";
    tree.inorder(tree.root);
    cout << "\n";

    tree.remove(10);
    tree.remove(10); // agora todas as ocorrencias removidas
    cout << "Depois de remover 10 mais duas vezes: ";
    tree.inorder(tree.root);
    cout << "\n";
    return 0;
}
