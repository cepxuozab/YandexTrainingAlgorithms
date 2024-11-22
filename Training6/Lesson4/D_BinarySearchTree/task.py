import sys


class Node:
    def __init__(self, value=None):
        self.value = value
        self.left = None
        self.right = None


class BinaryTree:
    def __init__(self):
        self.root = None

    def insert(self, value) -> bool:
        if self.root is None:
            self.root = Node(value)
            return True

        current = self.root
        while True:
            if value == current.value:
                return False
            if value < current.value:
                if not current.left:
                    current.left = Node(value)
                    break
                current = current.left
            else:
                if not current.right:
                    current.right = Node(value)
                    break
                current = current.right
        return True

    @staticmethod
    def search_impl(node: Node, value: int):
        if node is None:
            return False
        if node.value == value:
            return True
        if value < node.value:
            return BinaryTree.search_impl(node.left, value)
        else:
            return BinaryTree.search_impl(node.right, value)

    def search(self, value):
        return self.search_impl(self.root, value)

    @staticmethod
    def inorder_impl(node: Node, level=0):
        if node is None: return
        BinaryTree.inorder_impl(node.left, level + 1)
        s = '.' * level
        print(f"{s}{node.value}")
        BinaryTree.inorder_impl(node.right, level + 1)

    def inorder(self):
        self.inorder_impl(self.root)


if __name__ == '__main__':
    tree = BinaryTree()
    for line in sys.stdin:
        commands = list(line.rstrip().split())
        command = commands[0]
        if command == 'PRINTTREE':
            tree.inorder()
            continue
        val = int(commands[1])
        if command == 'ADD':
            print('ALREADY' if not tree.insert(val) else 'DONE')
        elif command == 'SEARCH':
            print('YES' if tree.search(val) else 'NO')
