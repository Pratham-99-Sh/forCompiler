#include <iostream>
using namespace std;

class TreeNode {
  int *keys;
  int t;
  TreeNode **C;
  int n;
  bool leaf;

public:
  TreeNode(int temp, bool bool_leaf);
  void insertNonFull(int k);
  void splitChild(int i, TreeNode *y);
  void remove(int k);
  void removeFromLeaf(int idx);
  void removeFromNonLeaf(int idx);
  int getPred(int idx);
  int getSucc(int idx);
  void fill(int idx);
  void borrowFromPrev(int idx);
  void borrowFromNext(int idx);
  void merge(int idx);
  void inorder();
  void preorder();
  void postorder();

  friend class BTree;
};

class BTree {
  TreeNode *root;
  int t;

public:
  BTree(int temp) {
    root = NULL;
    t = temp;
  }

  void insert(int k);
  void remove(int k);
  void inorder();
  void preorder();
  void postorder();
};

TreeNode::TreeNode(int t1, bool leaf1) {
  t = t1;
  leaf = leaf1;

  keys = new int[2 * t - 1];
  C = new TreeNode *[2 * t];

  n = 0;
}

void BTree::insert(int k) {
  if (root == NULL) {
    root = new TreeNode(t, true);
    root->keys[0] = k;
    root->n = 1;
  } else {
    if (root->n == 2 * t - 1) {
      TreeNode *s = new TreeNode(t, false);
      s->C[0] = root;
      s->splitChild(0, root);
      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->C[i]->insertNonFull(k);
      root = s;
    } else
      root->insertNonFull(k);
  }
}

void TreeNode::insertNonFull(int k) {
  int i = n - 1;

  if (leaf == true) {
    while (i >= 0 && keys[i] > k) {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = k;
    n = n + 1;
  } else {
    while (i >= 0 && keys[i] > k)
      i--;

    if (C[i + 1]->n == 2 * t - 1) {
      splitChild(i + 1, C[i + 1]);

      if (keys[i + 1] < k)
        i++;
    }
    C[i + 1]->insertNonFull(k);
  }
}

void TreeNode::splitChild(int i, TreeNode *y) {
  TreeNode *z = new TreeNode(y->t, y->leaf);
  z->n = t - 1;

  for (int j = 0; j < t - 1; j++)
    z->keys[j] = y->keys[j + t];

  if (y->leaf == false) {
    for (int j = 0; j < t; j++)
      z->C[j] = y->C[j + t];
  }

  y->n = t - 1;
  for (int j = n; j >= i + 1; j--)
    C[j + 1] = C[j];

  C[i + 1] = z;

  for (int j = n - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[t - 1];
  n = n + 1;
}

void BTree::remove(int k) {
  if (!root) {
    cout << "The tree is empty\n";
    return;
  }

  root->remove(k);

  if (root->n == 0) {
    TreeNode *tmp = root;
    if (root->leaf)
      root = NULL;
    else
      root = root->C[0];

    delete tmp;
  }
}

void TreeNode::remove(int k) {
  int idx = 0;
  while (idx < n && keys[idx] < k)
    idx++;

  if (idx < n && keys[idx] == k) {
    if (leaf)
      removeFromLeaf(idx);
    else
      removeFromNonLeaf(idx);
  } else {
    if (leaf) {
      cout << "The key " << k << " does not exist in the tree\n";
      return;
    }

    bool flag = (idx == n);

    if (C[idx]->n < t)
      fill(idx);

    if (flag && idx > n)
      C[idx - 1]->remove(k);
    else
      C[idx]->remove(k);
  }
}

void TreeNode::removeFromLeaf(int idx) {
  for (int i = idx + 1; i < n; ++i)
    keys[i - 1] = keys[i];

  n--;
}

void TreeNode::removeFromNonLeaf(int idx) {
  int k = keys[idx];

  if (C[idx]->n >= t) {
    int pred = getPred(idx);
    keys[idx] = pred;
    C[idx]->remove(pred);
  } else if (C[idx + 1]->n >= t) {
    int succ = getSucc(idx);
    keys[idx] = succ;
    C[idx + 1]->remove(succ);
  } else {
    merge(idx);
    C[idx]->remove(k);
  }
}

int TreeNode::getPred(int idx) {
  TreeNode *cur = C[idx];
  while (!cur->leaf)
    cur = cur->C[cur->n];

  return cur->keys[cur->n - 1];
}

int TreeNode::getSucc(int idx) {
  TreeNode *cur = C[idx + 1];
  while (!cur->leaf)
    cur = cur->C[0];

  return cur->keys[0];
}

void TreeNode::fill(int idx) {
  if (idx != 0 && C[idx - 1]->n >= t)
    borrowFromPrev(idx);
  else if (idx != n && C[idx + 1]->n >= t)
    borrowFromNext(idx);
  else {
    if (idx != n)
      merge(idx);
    else
      merge(idx - 1);
  }
}

void TreeNode::borrowFromPrev(int idx) {
  TreeNode *child = C[idx];
  TreeNode *sibling = C[idx - 1];

  for (int i = child->n - 1; i >= 0; --i)
    child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
    for (int i = child->n; i >= 0; --i)
      child->C[i + 1] = child->C[i];
  }

  child->keys[0] = keys[idx - 1];

  if (!child->leaf)
    child->C[0] = sibling->C[sibling->n];

  keys[idx - 1] = sibling->keys[sibling->n - 1];

  child->n += 1;
  sibling->n -= 1;
}

void TreeNode::borrowFromNext(int idx) {
  TreeNode *child = C[idx];
  TreeNode *sibling = C[idx + 1];

  child->keys[(child->n)] = keys[idx];

  if (!(child->leaf))
    child->C[(child->n) + 1] = sibling->C[0];

  keys[idx] = sibling->keys[0];

  for (int i = 1; i < sibling->n; ++i)
    sibling->keys[i - 1] = sibling->keys[i];

  if (!sibling->leaf) {
    for (int i = 1; i <= sibling->n; ++i)
      sibling->C[i - 1] = sibling->C[i];
  }

  child->n += 1;
  sibling->n -= 1;
}

void TreeNode::merge(int idx) {
  TreeNode *child = C[idx];
  TreeNode *sibling = C[idx + 1];

  child->keys[t - 1] = keys[idx];

  for (int i = 0; i < sibling->n; ++i)
    child->keys[i + t] = sibling->keys[i];

  if (!child->leaf) {
    for (int i = 0; i <= sibling->n; ++i)
      child->C[i + t] = sibling->C[i];
  }

  for (int i = idx + 1; i < n; ++i)
    keys[i - 1] = keys[i];

  for (int i = idx + 2; i <= n; ++i)
    C[i - 1] = C[i];

  child->n += sibling->n + 1;
  n--;

  delete (sibling);
}

void BTree::inorder() {
  if (root != NULL) {
    root->inorder();
    cout << endl;
  }
}

void BTree::preorder() {
  if (root != NULL) {
    root->preorder();
    cout << endl;
  }
}

void BTree::postorder() {
  if (root != NULL) {
    root->postorder();
    cout << endl;
  }
}

void TreeNode::inorder() {
  int i;
  for (i = 0; i < n; i++) {
    if (leaf == false)
      C[i]->inorder();
    cout << " " << keys[i];
  }

  if (leaf == false)
    C[i]->inorder();
}

void TreeNode::preorder() {
  int i;
  for (i = 0; i < n; i++) {
    cout << " " << keys[i];
    if (leaf == false)
      C[i]->preorder();
  }

  if (leaf == false)
    C[i]->preorder();
}

void TreeNode::postorder() {
  int i;
  for (i = 0; i < n; i++) {
    if (leaf == false)
      C[i]->postorder();
    cout << " " << keys[i];
  }

  if (leaf == false)
    C[i]->postorder();
}

int main() {
  BTree t(3);
  t.insert(8);
  t.insert(9);
  t.insert(10);
  t.insert(11);
  t.insert(15);
  t.insert(16);
  t.insert(17);
  t.insert(18);
  t.insert(20);
  t.insert(23);

  cout << "Inorder traversal: ";
  t.inorder();

  cout << "Preorder traversal: ";
  t.preorder();

  cout << "Postorder traversal: ";
  t.postorder();

  t.remove(10);
  cout << "\nThe B-tree after the deletion of 10 is: ";
  t.inorder();

  return 0;
}