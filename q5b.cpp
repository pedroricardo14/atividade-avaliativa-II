#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int key;
    int height;
    Node *left, *right;
    Node(int k) : key(k), height(1), left(NULL), right(NULL) {}
};

class AVL {
public:
    Node* root;
    AVL() : root(NULL) {}

    int height(Node* n) { return n ? n->height : 0; }
    int getBalance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, int key) {
    if (!node) return new Node(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node; // chaves iguais não inserem duplicatas (poderia usar contador)

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // LL
        if (balance > 1 && key < node->left->key) return rightRotate(node);
        // RR
        if (balance < -1 && key > node->right->key) return leftRotate(node);
        // LR
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // RL
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void insert(int key) { root = insert(root, key); }

    void inorder(Node* n) {
        if (!n) return;
        inorder(n->left);
        cout << n->key << " ";
        inorder(n->right);
    }

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
            // nó com 0 ou 1 filho
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) { // sem filhos
                    temp = node;
                    node = NULL;
                } else { // um filho
                    *node = *temp;
                }
                delete temp;
            } else {
                // nó com 2 filhos
                Node* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }

        if (!node) return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // balanceamentos
        if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void remove(int key) { root = remove(root, key); }

    Node* search(Node* node, int key) {
        if (!node || node->key == key) return node;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }
};

int main() {
    AVL tree;
    int opc, x;
    while (true) {
        cout << "\n1-Inserir\n2-Listar (in-order)\n3-Remover\n4-Consultar\n0-Sair\nOpcao: ";
        if (!(cin >> opc)) return 0;
        if (opc == 0) break;
        switch (opc) {
            case 1:
                cout << "Valor: "; cin >> x; tree.insert(x);
                break;
            case 2:
                cout << "AVL in-order: "; tree.inorder(tree.root); cout << "\n";
                break;
            case 3:
                cout << "Valor a remover: "; cin >> x; tree.remove(x);
                break;
            case 4:
                cout << "Valor a consultar: "; cin >> x;
                cout << (tree.search(tree.root, x) ? "Encontrado\n" : "Nao encontrado\n");
                break;
            default:
                cout << "Opcao invalida\n";
        }
    }
    return 0;
}
