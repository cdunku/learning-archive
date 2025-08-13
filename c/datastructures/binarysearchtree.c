#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  int data;
  struct node_t *right;
  struct node_t *left;
} node_t;

node_t *bst_insert(int data) {
  node_t *tmp = malloc(sizeof(node_t));

  if(!tmp) {
    printf("Node has not been allocated\n");
  }

  tmp->data = data;
  tmp->left = NULL;
  tmp->right = NULL;

  return tmp;
}

void bst_add_to_tree(node_t **root, node_t *node) {
  if(*root == NULL) {
    *root = node;
    return;
  }
  if((*root)->data == node->data) {
    printf("The number %d already exists\n", (*root)->data);
    return;
  }
  if((*root)->data < node->data) {
    bst_add_to_tree(&(*root)->right, node);
  }
  else {
    bst_add_to_tree(&(*root)->left, node);
  }
}

void bst_free(node_t **root) {
  if(!(*root)) { return; }

  bst_free(&(*root)->left);
  bst_free(&(*root)->right);
  free(*root);

  *root = NULL;
}

void bst_print(node_t **root) {
  if(!(*root)) { return; }

  bst_print(&(*root)->left);
  bst_print(&(*root)->right);

  printf("%d - ", (*root)->data);
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

  bst_free(&root);

  return 0;
}
