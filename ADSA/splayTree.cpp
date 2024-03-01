#include <iostream>
#include <climits>
#include <chrono>
using namespace std;

class SplayTree {
    struct Node {
        int data;
        Node *left;
        Node *right;
    };
    Node *root;

    Node *createNode(int data) {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        return x;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        return y;
    }

    Node *splayBottomUp(Node *root, int data) {
        if (root == NULL || root->data == data) {
            return root;
        }
        if (root->data > data) {
            if (root->left == NULL) {
                return root;
            }
            if (root->left->data > data) {
                root->left->left = splayBottomUp(root->left->left, data);
                root = rightRotate(root);
            } else if (root->left->data < data) {
                root->left->right = splayBottomUp(root->left->right, data);
                if (root->left->right != NULL) {
                    root->left = leftRotate(root->left);
                }
            }
            return (root->left == NULL) ? root : rightRotate(root);
        } else {
            if (root->right == NULL) {
                return root;
            }
            if (root->right->data > data) {
                root->right->left = splayBottomUp(root->right->left, data);
                if (root->right->left != NULL) {
                    root->right = rightRotate(root->right);
                }
            } else if (root->right->data < data) {
                root->right->right = splayBottomUp(root->right->right, data);
                root = leftRotate(root);
            }
            return (root->right == NULL) ? root : leftRotate(root);
        }
    }

    Node* splayTopDown(Node *root, int data) {
        if (root == NULL || root->data == data) {
            return root;
        }
        Node dummy;
        dummy.left = NULL;
        dummy.right = NULL;
        Node *leftMax = &dummy;
        Node *rightMin = &dummy;
        while (true) {
            if (root->data > data) {
                if (root->left == NULL) {
                    break;
                }
                if (root->left->data > data) {
                    root = rightRotate(root);
                    if (root->left == NULL) {
                        break;
                    }
                }
                rightMin->left = root;
                rightMin = root;
                root = root->left;
                rightMin->left = NULL;
            } else if (root->data < data) {
                if (root->right == NULL) {
                    break;
                }
                if (root->right->data < data) {
                    root = leftRotate(root);
                    if (root->right == NULL) {
                        break;
                    }
                }
                leftMax->right = root;
                leftMax = root;
                root = root->right;
                leftMax->right = NULL;
            } else {
                break;
            }
        }
        leftMax->right = root->left;
        rightMin->left = root->right;
        root->left = dummy.right;
        root->right = dummy.left;
        return root;
    }

    Node *insert(Node *root, int data) {
        if (root == NULL) {
            return createNode(data);
        }
        root = splayBottomUp(root, data);
        if (root->data == data) {
            return root;
        }
        Node *newNode = createNode(data);
        if (root->data > data) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = NULL;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = NULL;
        }
        return newNode;
    }

    void inOrder(Node *root) {
        if (root == NULL) {
            return;
        }
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }

    Node *deleteMin(Node *root) {
        if (root->left == NULL) {
            return root->right;
        }
        root->left = deleteMin(root->left);
        return root;
    }

    Node *deleteMax(Node *root) {
        if (root->right == NULL) {
            return root->left;
        }
        root->right = deleteMax(root->right);
        return root;
    }

    Node *deleteNode(Node *root, int data) {
        if (root == NULL) {
            return root;
        }
        root = splayBottomUp(root, data);
        if (root->data != data) {
            return root;
        }
        if (root->left == NULL) {
            return root->right;
        }
        if (root->right == NULL) {
            return root->left;
        }
        Node *temp = root;
        root = splayBottomUp(root->left, data);
        root->right = temp->right;
        return root;
    }

    void preOrder(Node *root) {
        if (root == NULL) {
            return;
        }
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }

    void postOrder(Node *root) {
        if (root == NULL) {
            return;
        }
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }

    pair<Node*, Node*> split(Node *root, int data) {
        if (root == NULL) {
            return {NULL, NULL};
        }
        root = splayBottomUp(root, data);
        if (root->data == data) {
            return {root->left, root->right};
        }
        if (root->data > data) {
            Node *left = root->left;
            root->left = NULL;
            return {left, root};
        } else {
            Node *right = root->right;
            root->right = NULL;
            return {root, right};
        }
    }

    Node *join(Node *left, Node *right) {
        if (left == NULL) {
            return right;
        }
        if (right == NULL) {
            return left;
        }
        left = splayBottomUp(left, INT_MAX);
        left->right = right;
        return left;
    }

public:
    SplayTree() {
        root = NULL;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void inOrder() {
        inOrder(root);
    }

    void preOrder() {
        preOrder(root);
    }

    void postOrder() {
        postOrder(root);
    }

    void deleteMin() {
        root = deleteMin(root);
    }

    void deleteMax() {
        root = deleteMax(root);
    }

    void deleteNode(int data) {
        root = deleteNode(root, data);
    }

    void split(int data) {
        pair<Node*, Node*> result = split(root, data);
        cout << "Inorder traversal of left tree: ";
        inOrder(result.first);
        cout << endl;
        cout << "Inorder traversal of right tree: ";
        inOrder(result.second);
        cout << endl;
    }

    void joinNodes(Node *left, Node *right) {
        root = join(left, right);
    }

    Node *createNewNode(int data) {
        return createNode(data);
    }

    void measureTime() {
        int data = 1000000;
        
        // Insert elements into the splay tree
        for (int i = 0; i < 1000000; i++) {
            insert(i);
        }

        // Measure time for splayBottomUp
        auto start = std::chrono::high_resolution_clock::now();
        splayBottomUp(root, data);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationBottomUp = end - start;
        std::cout << "Time taken by splayBottomUp: " << durationBottomUp.count() << " seconds" << std::endl;

        // Measure time for splayTopDown
        start = std::chrono::high_resolution_clock::now();
        splayTopDown(root, data);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationTopDown = end - start;
        std::cout << "Time taken by splayTopDown: " << durationTopDown.count() << " seconds" << std::endl;
    }
};

int main() {
    SplayTree tree;
    tree.insert(100);
    tree.insert(50);
    tree.insert(200);
    tree.insert(40);
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);
    tree.insert(45);
    tree.insert(55);
    tree.insert(150);
    tree.insert(250);

    cout << "Inorder traversal of the constructed splay tree is \n";
    tree.inOrder();
    cout << endl;

    tree.split(50);

    auto left = tree.createNewNode(30);
    auto right = tree.createNewNode(40);
    tree.joinNodes(left, right);
    cout << "Inorder traversal of the joined tree: ";

    tree.inOrder();
    cout << endl;    


    return 0;
}