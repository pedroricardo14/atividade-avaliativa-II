#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node *left, *right;
    Node(int k) {
        key = k;
        left = right = NULL;
    }
};

class BST {
public:
    Node* root;
    BST() { root = NULL; }

    // F1: Inserção
    Node* insert(Node* node, int key) {
        if (node == NULL) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        return node;
    }

    void insert(int key) { root = insert(root, key); }

    // F2: Listagem (in-order)
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

    // F3: Remoção
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    Node* remove(Node* node, int key) {
        if (!node) return node;
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            if (!node->left)
                return node->right;
            else if (!node->right)
                return node->left;
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
        return node;
    }

    void remove(int key) { root = remove(root, key); }
};

int main() {
    BST t;
    int values[] = {20,5,12,36,27,45,9,2,6,17,40};
    int n = sizeof(values)/sizeof(values[0]);
    for (int i = 0; i < n; ++i) t.insert(values[i]);

    cout << "Arvore original (in-order): ";
    t.inorder(t.root); cout << endl;

    t.remove(9);
    t.remove(5);
    t.remove(20);

    cout << "Arvore apos remocoes (9,5,20): ";
    t.inorder(t.root); cout << endl;
}