// c++ program to convert BST to min heap
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
};

class BST
{
    Node *root;

    Node* insert(Node *root, int x)
    {
        if(root == NULL)
        {
            root = new Node;
            root->data = x;
            root->left = root->right = NULL;
        }
        else if(x < root->data)
            root->left = insert(root->left, x);
        else
            root->right = insert(root->right, x);

        return root;
    }

    void mirroredInorder(Node *root, vector<int> &arr)
    {
        if(root == NULL)
            return;

        mirroredInorder(root->right, arr);
        arr.push_back(root->data);
        mirroredInorder(root->left, arr);
    }

    void preorder(Node *root, vector<int> &arr)
    {
        if(root == NULL)
            return;

        root->data = arr.back();
        arr.pop_back();
        preorder(root->left, arr);
        preorder(root->right, arr);
    }

    void preorder(Node* root)
    {
        if(root == NULL)
            return;

        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }

    public:

        BST()
        {
            root = NULL;
        }

        void preorder()
        {
            preorder(root);
        }

        void updatePreorder(vector<int> &arr)
        {
            preorder(root, arr);
        }

        vector<int> extractArray()
        {
            vector<int> arr;
            mirroredInorder(root, arr);
            return arr;
        }

        void insert(int x)
        {
            root = insert(root, x);
        }

};

void convertBSTtoHeap(BST &bst)
{
    vector<int> arr = bst.extractArray();
    bst.updatePreorder(arr);
}

int main()
{
    BST bst;
    bst.insert(4);
    bst.insert(2);
    bst.insert(6);
    bst.insert(1);
    bst.insert(3);
    bst.insert(5);
    bst.insert(7);

    cout << "Preorder traversal of BST: ";
    bst.preorder();
    cout << endl;

    convertBSTtoHeap(bst);
    cout << "Preorder traversal after converted to min heap: ";
    bst.preorder();
    cout << endl << endl;

    return 0;
}