#python code to make a tree

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

def printTree(root):

    if root is None:
        return

    printTree(root.left)
    print(root.data, end=" ")
    printTree(root.right)

def printTreePostOrder(root):
    
        if root is None:
            return
    
        printTreePostOrder(root.left)
        printTreePostOrder(root.right)
        print(root.data, end=" ")

def printTreePreOrder(root):
        
            if root is None:
                return
        
            print(root.data, end=" ")
            printTreePreOrder(root.left)
            printTreePreOrder(root.right)

def printTreeInOrder(root):
      