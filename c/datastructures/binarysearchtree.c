#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  int data;
  struct node_t *right;
  struct node_t *left;
} node_t;

node_t *bst_insert(int data) {
  // Allocate memory for a new node
  node_t *tmp = malloc(sizeof(node_t));

  if(!tmp) {
    printf("Node has not been allocated\n");
  }

  // Create a new node
  tmp->data = data;
  tmp->left = NULL;
  tmp->right = NULL;

  return tmp;
}

void bst_add_to_tree(node_t **root, node_t *node) {
  // If we find available space
  if(*root == NULL) {
    *root = node;
    return;
  }
  if((*root)->data == node->data) {
    printf("The number %d already exists\n", (*root)->data);
    return;
  }

  // Check where it is suitable to insert the node
  if((*root)->data < node->data) {
    bst_add_to_tree(&(*root)->right, node);
  }
  else {
    bst_add_to_tree(&(*root)->left, node);
  }
}

void bst_delete(node_t **root, int data) {
  if(!(*root)) {
    printf("The number entered (%d), does not exist\n", data);
    return;
  }
  
  // Check where the node is (if it exists)
  if((*root)->data > data) {
    bst_delete(&(*root)->left, data);
  }
  else if((*root)->data < data) {
    bst_delete(&(*root)->right, data);
  }
  // If the node exists
  else {
    // If it is a lead node
    if((*root)->left == NULL && (*root)->right == NULL) {

      free(*root);
      *root = NULL;

      return;
    }
    // If the node is a parent of a subtree (left or right)
    else if((*root)->left == NULL || (*root)->right == NULL) {
      node_t *subtree = ((*root)->left == NULL) ? (*root)->right : (*root)->left;
      free(*root);
      *root = subtree;
      
      return;
    }
    // Both the left & right subtrees contain values
    else {
      node_t *parent = *root;
      node_t *subtree = parent->right;

      // Iterate until we find the smallest node in the right subtree
      while(subtree->left != NULL) { 
        parent = subtree;
        subtree = subtree->left;
      }

      // Update the node we want to delete with the successor node 
      (*root)->data = subtree->data;

      // Remove the node we copied by linking its parent to its right child
      if(parent->left == subtree) {
        parent->left = subtree->right;
      } else {
        parent->right = subtree->right;
      }
     
      // Delete the successor node from the parent subtree;
      free(subtree);
      subtree = NULL;

      return;
    }
  }
}

void bst_free(node_t **root) {
  if(!(*root)) { return; }

  // Use recursion to go through each node and free it
  bst_free(&(*root)->left);
  bst_free(&(*root)->right);
  free(*root);

  *root = NULL;
}

void bst_print(node_t **root) {
  if(!(*root)) { return; }

  // Post-order
  // printf("%d - ", (*root)->data);
  bst_print(&(*root)->left);
  // In-order
  // printf("%d - ", (*root)->data);
  bst_print(&(*root)->right);

  // Post-order
  // printf("%d - ", (*root)->data);
}

int main(void) {
  node_t *root = NULL;

  bst_add_to_tree(&root, bst_insert(10));
  bst_add_to_tree(&root, bst_insert(5));
  bst_add_to_tree(&root, bst_insert(12));
  bst_add_to_tree(&root, bst_insert(2));
  bst_add_to_tree(&root, bst_insert(4));
  bst_add_to_tree(&root, bst_insert(13));

  bst_print(&root);
  printf("\n");

  bst_delete(&root, 10);
  bst_delete(&root, 5);
  bst_delete(&root, 15);

  bst_print(&root);
  printf("\n");

  bst_free(&root);

  return 0;
}
