#include<iostream>
#include<queue>
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

node* buildTree(){
    int d;
    cin>>d;
    if(d==-1) return nullptr;
    node* n = new node(d);
    n->left = buildTree();
    n->right = buildTree();
    return n;
}

void print(node* root){
    if(root == NULL) return;
    cout<<root->data<<" ";
    print(root->left);
    print(root->right);
}

node* buildLevel(){
    int d;
    cin>>d;
    if(d==-1) return nullptr;
    node* root = new node(d);
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        node* nd = q.front();
        q.pop();
        int c1,c2;
        cin>>c1>>c2;
        if(c1!=-1){
            nd->left = new node(c1);
            q.push(nd->left);
        }
        if(c2!=-1){
            nd->right = new node(c2);
            q.push(nd->right);
        }
    }
    return root;
}

void printLevelOrder(node* root){
    queue<node*> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        node* nd = q.front();
        q.pop();
        if(nd == NULL){
            cout<<endl;
            if(!q.empty()) q.push(NULL);
            continue;
        }
        cout<<nd->data<<" ";
        if(nd->left != NULL) q.push(nd->left);
        if(nd->right != NULL) q.push(nd->right);
    }
}

int maxDepth(node* root){
    if(root == NULL) return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    return 1+max(left, right);
}

int minDepth(node* root){
    if(root == NULL) return 0;
    int left = minDepth(root->left);
    int right = minDepth(root->right);
    return 1+min(left, right);
}

int Diameter(node* root){
    if(root == NULL) return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    int op1 = left+right;
    int op2 = Diameter(root->left);
    int op3 = Diameter(root->right);
    return max(op1, max(op2, op3));
}

class HDpair{
    public :
    int height;
    int diameter;
};

HDpair fastDiameter(node* root){
    HDpair p;
    if(root == NULL){
        p.height = 0;
        p.diameter = 0;
        return p;
    }
    HDpair left = fastDiameter(root->left);
    HDpair right = fastDiameter(root->right);
    p.height = max(left.height, right.height)+1;
    int d1 = left.height+right.height;
    int d2 = left.diameter;
    int d3 = right.diameter;
    p.diameter = max(d1, max(d2, d3));
    return p;
}

bool isMirror(node*a, node*b){
    if(a == NULL && b == NULL) return true;
    if(a == NULL || b == NULL) return false;
    if(a->data != b->data) return false;
    return isMirror(a->left, b->right) && isMirror(a->right, b->left);
}

bool isSymmetric(node* root) {
    if(root == NULL) return true;
    return isMirror(root->left, root->right);
}

int evalTree(node* root){
    if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL) return root->data;
    int left = evalTree(root->left);
    int right = evalTree(root->right);
    if(root->data == '+') return left+right;
    if(root->data == '-') return left-right;
    if(root->data == '*') return left*right;
    if(root->data == '/') return left/right;
}

node* remove(node* root){
    if(root == NULL) return NULL;
    if(root->left) root->left = remove(root->left);
    if(root->right) root->right = remove(root->right);
    if((root->left!=NULL and root->right==NULL) or (root->left==NULL and root->right!=NULL)){
        if(root->left) root = root->left;
        else root = root->right;
        root = remove(root);
    }
    return root;
}

void inLine(node* root, vector<int>&v){
    if(root == NULL) return;
    inLine(root->left, v);
    v.push_back(root->data);
    inLine(root->right, v);
}

vector<int> removeHalfNodes(node *root)
{
    vector<int> v;
    if(root == NULL) return v;
    root = remove(root);
    inLine(root, v);
    return v;
}

int main(){
    node* root = buildLevel();
    printLevelOrder(root);
    cout<<endl<<minDepth(root)<<endl;
    return 0;
}