Binary Search tree
operation O(n)

Inorder(node):
    if node == nullptr:
        return
    Inorder(node->Left)
    Dosmth(node->value)
    Inorder(node->Right)

Preorder(node):
    if node == nullptr:
        return
    Dosmth(node->value)
    Preorder(node->Left)
    Preorder(node->Right)

Postorder(node):
    if node == nullptr:
        return
    Postorder(node->Left)
    Postorder(node->Right)
    Dosmth(node->value)

AVL tree - binary search tree
operation O(n)

balance = hl - hr