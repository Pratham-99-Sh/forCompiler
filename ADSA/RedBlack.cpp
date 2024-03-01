#include <iostream>

using namespace std;

enum Color {
    RED,
    BLACK
};

class RedBlack {
    struct Node {
        int data;
        Node *left;
        Node *right;
        Node *parent;
        Color color;
    };
    Node *root;
    Node *TNULL;

    Node *createNode(int data) {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->left = TNULL;
        newNode->right = TNULL;
        newNode->parent = TNULL;
        newNode->color = RED;
        return newNode;
    }

    void insertFix(Node *k) {
        Node *u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;

                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = BLACK;
    }

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void insert(int key) {
        Node *node = createNode(key);
        Node *y = nullptr;
        Node *x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insertFix(node);
    }

    void inOrder(Node *node) {
        if (node != TNULL) {
            inOrder(node->left);
            cout << node->data << " ";
            inOrder(node->right);
        }
    }

    void preOrder(Node *node) {
        if (node != TNULL) {
            cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void postOrder(Node *node) {
        if (node != TNULL) {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->data << " ";
        }
    }

   void rbTransplant(Node *u, Node *v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    Node *minimum(Node *node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    void deleteNode(Node *node, int data) {
        Node *z = TNULL;
        Node *x, *y;
        while (node != TNULL) {
            if (node->data == data) {
                z = node;
            }

            if (node->data <= data) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            cout << "Couldn't find key in the tree" << endl;
            return;
        }

        y = z;
        Color yOriginalColor = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (yOriginalColor == BLACK) {
            deleteFix(x);
        }
    }

    void deleteFix(Node *x) {
        Node *s;
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }




public:
    RedBlack() {
        TNULL = new Node;
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void add(int key) {
        insert(key);
    }

    void printinOrder() {
        inOrder(this->root);
    }

    void printpreOrder() {
        preOrder(this->root);
    }

    void printpostOrder() {
        postOrder(this->root);
    }

    void deleteNode(int data) {
        deleteNode(this->root, data);
    }

};

int main() {
    RedBlack rbt;
    rbt.add(70);
    rbt.add(20);
    rbt.add(40);
    rbt.add(30);
    rbt.add(50);
    rbt.add(60);
    rbt.add(10);
    rbt.add(80);
    rbt.add(90);
    rbt.add(100);
    rbt.add(110);
    rbt.add(120);
    rbt.add(130);
    cout << "Inorder: ";
    rbt.printinOrder();
    cout << endl;
    cout << "Preorder: ";
    rbt.printpreOrder();
    cout << endl;
    cout << "Postorder: ";
    rbt.printpostOrder();
    cout << endl;

    cout << "\nAfter deleting 100" << endl;
    rbt.deleteNode(100);
    cout << "Inorder: ";
    rbt.printinOrder();
    cout << endl;
    cout << "Preorder: ";
    rbt.printpreOrder();
    cout << endl;
    cout << "Postorder: ";
    rbt.printpostOrder();
    cout << endl;
    return 0;
}