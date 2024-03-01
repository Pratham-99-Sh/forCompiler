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

class AVL{
    struct Node {
        Student data;
        Node *left;
        Node *right;
        int height;
    };
    Node *root;

    Node *createNode(Student data) {
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

    Node *insert(Node *node, Student data) {
        if (node == NULL) {
            return createNode(data);
        }
        if (data.rollNo < node->data.rollNo) {
            node->left = insert(node->left, data);
        } else if (data.rollNo > node->data.rollNo) {
            node->right = insert(node->right, data);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int bf = balanceFactor(node);

        if (bf > 1 && data.rollNo < node->left->data.rollNo) {
            return rightRotate(node);
        }
        if (bf < -1 && data.rollNo > node->right->data.rollNo) {
            return leftRotate(node);
        }
        if (bf > 1 && data.rollNo > node->left->data.rollNo) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (bf < -1 && data.rollNo < node->right->data.rollNo) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrder(Node *node) {
        if (node == NULL) {
            return;
        }
        inOrder(node->left);
        cout << node->data.rollNo << " " << node->data.firstName << " " << node->data.lastName << " " << node->data.CGPA << endl;
        inOrder(node->right);
    }

    Node *deleteNode(Node *node, int rollNo) {
        if (node == NULL) {
            return node;
        }
        if (rollNo < node->data.rollNo) {
            node->left = deleteNode(node->left, rollNo);
        } else if (rollNo > node->data.rollNo) {
            node->right = deleteNode(node->right, rollNo);
        } else {
            if (node->left == NULL || node->right == NULL) {
                Node *temp = node->left ? node->left : node->right;
                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node *temp = node->right;
                while (temp->left != NULL) {
                    temp = temp->left;
                }
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data.rollNo);
            }
        }
        if (node == NULL) {
            return node;
        }
        node->height = 1 + max(height(node->left), height(node->right));
        int bf = balanceFactor(node);
        if (bf > 1 && balanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }
        if (bf > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (bf < -1 && balanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        if (bf < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node *search(Node *node, int rollNo) {
        if (node == NULL || node->data.rollNo == rollNo) {
            return node;
        }
        if (node->data.rollNo < rollNo) {
            return search(node->right, rollNo);
        }
        return search(node->left, rollNo);
    }

    public:
    AVL() {
        root = NULL;
    }

    void insert(Student data) {
        root = insert(root, data);
    }

    void deleteNode(int rollNo) {
        root = deleteNode(root, rollNo);
    }

    void inOrder() {
        inOrder(root);
    }

    Student search(int rollNo) {
        Node *node = search(root, rollNo);
        if (node == NULL) {
            Student s;
            s.rollNo = -1;
            return s;
        }
        return node->data;
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

    ~AVL() {
        delete root;
    }
};

int main() {
    AVL avl;
    avl.readFromFile("students.txt");

    cout<<"Inorder Traversal of AVL Tree"<<endl;
    avl.inOrder();

    cout<<"\nSearching for roll number 102015118"<<endl;
    Student s = avl.search(102015118);
    cout << s.rollNo << " " << s.firstName << " " << s.lastName << " " << s.CGPA << endl;

    cout<<"\nInorder traversal after deleting roll number 102015118"<<endl;
    avl.deleteNode(102015118);
    avl.inOrder();
    return 0;
}