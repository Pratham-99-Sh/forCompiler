#include<iostream>
using namespace std;

class node{
    public:
        int data;
        node* left;
        node* right;
        node(int d){
            data = d;
            left = NULL;
            right = NULL;
        }
};

node* insert(node* root, int key){
    if(root==NULL) return new node(key);
    if(key<root->data) root->left = insert(root->left, key);
    else root->right = insert(root->right, key);
    return root;
}

void printInLine(node* root)
{
    if(root==NULL) return;
    printInLine(root->left);
    cout<<root->data<<" ";
    printInLine(root->right);
}

bool search(node* root, int key){
    if(root==NULL) return false;
    if(root->data==key) return true;
    if(key<root->data) return search(root->left, key);
    else return search(root->right, key);
}

node* findMin(node* root){
    if(root==NULL) return NULL;
    if(root->left==NULL) return root;
    return findMin(root->left);
}

node* remove(node* root, int key){
    if(root==NULL) return NULL;
    if(key<root->data) root->left = remove(root->left, key);
    else if(key>root->data) root->right = remove(root->right, key);
    else{
        if(root->left==NULL and root->right==NULL){
            delete root;
            root = NULL;
            return root;
        }

       else if(root->left==NULL){
            node* temp = root->right;
            delete root;
            return temp;
        }

        else if(root->right==NULL){
            node*temp = root->left;
            delete root;
            return temp;
        }
        else{
            node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
            return root;
        }
    }
    return root;
}

void printRange(node* root, int k1, int k2){
    if(root==NULL) return;
    if(k1<=root->data and k2>=root->data) {
        printRange(root->left, k1, k2);
        cout<<root->data<<" ";
        printRange(root->right, k1, k2);
    }
    else if(k2>root->data) printRange(root->right, k1, k2);
    else printRange(root->left, k1, k2);
}

int main()
{
    int arr[] = {5, 3, 7, 1, 4, 6, 8};
    node* root = NULL;
    for(auto x:arr)
    {
        root = insert(root, x);
    }

    printInLine(root);
    cout<<endl;
    //root = remove(root, 1);
    printRange(root,2,6);
    return 0;
}