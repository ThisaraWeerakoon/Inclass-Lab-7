#include <iostream>
using namespace std;

struct node {
  int key;
  struct node *left, *right;
};

// Inorder traversal
void traverseInOrder(struct node *root) {
    //left root right method
  if(root==NULL){
    return;
  }
  traverseInOrder(root->left);
  cout<<root->key<<" ";
  traverseInOrder(root->right);
  cout<<endl;
  

}

// Insert a node
struct node *insertNode(struct node *node, int key) {
  if(node==NULL){
    //create new node and insert it 
    struct node* newEmptyNode= (struct node*)malloc(sizeof(struct node));
    newEmptyNode->key = key;
    newEmptyNode->left = NULL;
    newEmptyNode->right=NULL;
    return newEmptyNode;

  }

  if (key < node->key){//check whether target val is lesser than the key 
        node->left = insertNode(node->left, key);
  }
  else if (key > node->key){//check whether target val is greater than the key 
      node->right = insertNode(node->right, key);
  }
 

  return node;



}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {

    
    if (root == NULL)//base case
        return root;
 
    
    if (key < root->key){ //check whether the target is less than the key.Then it should be in the left sub tree
        root->left = deleteNode(root->left, key);
    }
    
    else if (key > root->key){//check whether the target is greater than the key.Then it should be in the right sub tree
        root->right = deleteNode(root->right, key);
    }
 
    else { //when the key is equal to the element to be deleted
        
        if (root->right == NULL and root->left == NULL){//when the node is a leaf
          return NULL;
        }
            
 
        
        else if (root->left == NULL) { // node has no left child
            struct node* rightSubTree = root->right;
            free(root);
            return rightSubTree; //return whole right subtree of the node
        }
        else if (root->right == NULL) {// node has no right child
            struct node* leftSubTree = root->left;
            free(root);
            return leftSubTree;//return whole right subtree of the node
        }
        //when node has 2 children we should get the smallest in the right subtree 
  
        struct node* smallestValueRightSubTree = root->right;
        
        while (smallestValueRightSubTree && smallestValueRightSubTree->left != NULL){//finding the leftmost leaf
            smallestValueRightSubTree = smallestValueRightSubTree->left;
        }
        root->key = smallestValueRightSubTree->key;//replace the current value by smallest value of the subtree
 
        // Delete the smallest val of right subtree
        root->right = deleteNode(root->right, smallestValueRightSubTree->key);
    }
    return root;
 
}

// Driver code
int main() {
  struct node *root = NULL;

  int operation;
  int operand;
  cin >> operation;

  while (operation != -1) {
    switch(operation) {
      case 1: // insert
        cin >> operand;
        root = insertNode(root, operand);
        cin >> operation;
        break;
      case 2: // delete
        cin >> operand;
        root = deleteNode(root, operand);
        cin >> operation;
        break;
      default:
        cout << "Invalid Operator!\n";
        return 0;
    }
  }
  
  traverseInOrder(root);
}
