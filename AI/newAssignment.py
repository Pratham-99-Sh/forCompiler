# write a code to make tree of integer data

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.middle = None
        self.right = None

class tree:
    def __init__(self):
        self.root = None

    def insert(self, data):
        if self.root == None:
            self.root = Node(data)
        else:
            self.insertNode(data, self.root)

    def insertNode(self, data, node):
        if data < node.data:
            if node.left == None:
                node.left = Node(data)
            else:
                self.insertNode(data, node.left)
        elif data > node.data:
            if node.right == None:
                node.right = Node(data)
            else:
                self.insertNode(data, node.right)
        else:
            if node.middle == None:
                node.middle = Node(data)
            else:
                self.insertNode(data, node.middle)

    def printTree(self):
        if self.root != None:
            self.printNode(self.root)

    def printNode(self, node):
        if node != None:
            self.printNode(node.left)
            print(node.data)
            self.printNode(node.middle)
            self.printNode(node.right)


    def bfs(self, data):
        queueS = []
        if self.root == None:
            return False
        else:
            if(self.root.left != None):
                queueS.append(self.root.left)
            if(self.root.middle != None):
                queueS.append(self.root.middle)
            if(self.root.right != None):
                queueS.append(self.root.right)
            while(len(queueS) > 0):
                node = queueS.pop(0)
                print(node.data)
                if node.data == data:
                    return True
                if(node.left != None):
                    queueS.append(node.left)
                if(node.middle != None):
                    queueS.append(node.middle)
                if(node.right != None):
                    queueS.append(node.right)
            return False

    def dfs(self, data):
        stackS = []
        if self.root == None:
            return False
        else:
            if(self.root.left != None):
                stackS.append(self.root.left)
            if(self.root.middle != None):
                stackS.append(self.root.middle)
            if(self.root.right != None):
                stackS.append(self.root.right)
            while(len(stackS) > 0):
                node = stackS.pop()
                print(node.data)
                if node.data == data:
                    return True
                if(node.left != None):
                    stackS.append(node.left)
                if(node.middle != None):
                    stackS.append(node.middle)
                if(node.right != None):
                    stackS.append(node.right)
            return False

t = tree()
t.insert(1)
t.insert(2)
t.insert(3)
t.insert(4)
t.insert(5)
t.insert(6)
t.insert(7)

print(t.bfs(5))
#print(t.dfs(1))
