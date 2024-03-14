# Trees
A **tree** is a data structure that stores data in a hierarchical fashion. We often use linked lists to build trees - the nodes would have two "next" pointers, one going left and one
going right. Trees serve as an alternative to linked lists and arrays when you need more organization of your data.

```
// a tree node could have 2 or more next pointers!
struct node {
  int value;
  node *left, *right; 
};

// Tree's root pointer is like linked list's head pointer
node* rootPtr; 
```
Basic Tree Facts 
- Trees are made of nodes
- Every tree has a "root" pointer
- The top node of a tree is called its "root" node
- Every node may have two or more "child" nodes
- A node with 0 children is called a "leaf" node
- A tree with no nodes is called an "empty tree"
- A subtree refers to a smaller portion of the overall tree. (each node technically holds a subtree in its left and right pointers!)

## Binary Trees (BT)
- A binary tree is a special type of tree where every node has at most 2 child nodes: a left and a right.
- A binary _**SEARCH**_ tree is a specific type of binary tree where the organization of nodes follows certain ordering rules. Do not confuse BST with a regular BT.

Implementing a BT
```
struct BTNODE {
  int val;
  BTNODE *left, *right;
}

main() {
  BTNODE *temp, *pRoot;

  pRoot = new BTNODE;
  pRoot->value = 5;

  temp = new BTNODE;
  temp->value = 7;
  temp->left = nullptr;
  temp->right = nullptr;
  pRoot->left = temp;

  temp = new BTNODE;
  temp->value = -3;
  temp->left = nullptr;
  temp->right = nullptr;
  pRoot->right = temp;
  // etc...
}
```

### Tree Traversal
