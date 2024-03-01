#include <iostream>
#include <algorithm>
using namespace std;

class AVL {
    struct Node {
        int data;
        Node *left;
        Node *right;
        int height;
    };
    Node *root;

    Node *createNode(int data) {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    int height(Node *node) {
        if (node == NULL) {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(Node *node) {
        if (node == NULL) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    Node *insert(Node *node, int data) {
        if (node == NULL) {
            return createNode(data);
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        if (balance > 1 && data < node->left->data) {
            return rightRotate(node);
        }
        if (balance < -1 && data > node->right->data) {
            return leftRotate(node);
        }
        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    Node *deleteNode(Node *node, int data) {
        if (node == NULL) {
            return node;
        }
        if (data < node->data) {
            node->left = deleteNode(node->left, data);
        } else if (data > node->data) {
            node->right = deleteNode(node->right, data);
        } else {
            if (node->left == NULL || node->right == NULL) {
                Node *temp = node->left ? node->left : node->right;
                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                } else {
                    *node = *temp;
                }
                free(temp);
            } else {
                Node *temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }
        if (node == NULL) {
            return node;
        }
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);
        if (balance > 1 && balanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }
        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && balanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void preOrder(Node *node) {
        if (node != NULL) {
            cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void inOrder(Node *node) {
        if (node != NULL) {
            inOrder(node->left);
            cout << node->data << " ";
            inOrder(node->right);
        }
    }

    void postOrder(Node *node) {
        if (node != NULL) {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->data << " ";
        }
    }

public:
    AVL() {
        root = NULL;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void deleteNode(int data) {
        root = deleteNode(root, data);
    }

    void preOrder() {
        preOrder(root);
    }

    void inOrder() {
        inOrder(root);
    }

    void postOrder() {
        postOrder(root);
    }
};

int main() {
    AVL tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << "Inorder traversal of the constructed AVL tree is \n";
    tree.inOrder();

    tree.deleteNode(30);
    cout << "\n\nPreorder, Inorder and Postorder traversal after deletion of 30 : \n";
    tree.preOrder();
    cout << endl;
    tree.inOrder();
    cout << endl;
    tree.postOrder();
    cout << endl;
    return 0;
}