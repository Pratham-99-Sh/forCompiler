#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Student {
    int rollNo;
    string firstName;
    string lastName;
    float CGPA;
};

enum Color {
    RED,
    BLACK
};

class RedBlack {
    struct Node {
        Student data;
        Node *left;
        Node *right;
        Node *parent;
        Color color;
    };
    Node *root;
    Node *TNULL;

    Node *createNode(Student data) {
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

    void rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        if (T2 != TNULL) {
            T2->parent = y;
        }

        x->parent = y->parent;
        if (y->parent == NULL) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        y->parent = x;
    }

    void leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        if (T2 != TNULL) {
            T2->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == NULL) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        x->parent = y;
    }

    void insert(Student data) {
        Node *node = createNode(data);
        Node *y = NULL;
        Node *x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data.rollNo < x->data.rollNo) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == NULL) {
            root = node;
        } else if (node->data.rollNo < y->data.rollNo) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == NULL) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == NULL) {
            return;
        }

        insertFix(node);
    }

    void inOrderHelper(Node *node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            printNode(node);
            inOrderHelper(node->right);
        }
    }

    void printNode(Node *node) {
        cout << node->data.rollNo << " ";
        cout << node->data.firstName << " ";
        cout << node->data.lastName << " ";
        cout << node->data.CGPA << " ";
        if(node->color == RED) {
            cout << "RED" << endl;
        } else {
            cout << "BLACK" << endl;
        }
    }

    void searchTreeHelper(Node *node, int key) {
        if (node != TNULL) {
            if (node->data.rollNo == key) {
                cout << "Found" << endl;
                printNode(node);
            }
            if (key < node->data.rollNo) {
                searchTreeHelper(node->left, key);
            } else {
                searchTreeHelper(node->right, key);
            }
        }
    }

    Node *minimum(Node *node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    Node *maximum(Node *node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    void fixDelete(Node *x) {
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

    void rbTransplant(Node *u, Node *v) {
        if (u->parent == NULL) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(Node *node, int key) {
        Node *z = TNULL;
        Node *x, *y;
        while (node != TNULL) {
            if (node->data.rollNo == key) {
                z = node;
            }

            if (node->data.rollNo <= key) {
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
        delete z;
        if (yOriginalColor == BLACK) {
            fixDelete(x);
        }
    }




public:
    RedBlack() {
        TNULL = new Node;
        TNULL->color = BLACK;
        TNULL->left = NULL;
        TNULL->right = NULL;
        root = TNULL;
    }

    void add(Student data) {
        insert(data);
    }

    void printTree() {
        if (root) {
            inOrderHelper(this->root);
        }
        cout << endl;
    }

   void searchTree(int rollNo) {
        searchTreeHelper(this->root, rollNo);
    }

    void deleteNode(int data) {
        deleteNodeHelper(this->root, data);
    }

    void readFromFile(string filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Student s;
            ss >> s.rollNo >> s.firstName >> s.lastName >> s.CGPA;
            insert(s);
        }
    }

    ~RedBlack() {
        delete root;
    }
};

int main() {
    RedBlack rbt;
    rbt.readFromFile("students.txt");
    cout << "Inorder Traversal of Red Black Tree" << endl;
    rbt.printTree();
    cout << "\nSearching for 102015022" << endl;
    rbt.searchTree(102015022);
    cout << "\nDeleting 102015022" << endl;
    rbt.deleteNode(102015022);
    cout << "\nInorder Traversal of Red Black Tree" << endl;
    rbt.printTree();
    return 0;
}