#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int data;
  struct node *next;
} node;


int main(int argc, char **argv) {
  // Creates a list where we store the values, this is the head of the list
  node *list = NULL;

  for(int i = 0; i < argc; i++) {
    // Turns the command line arguments to integers from a string
    int num = atoi(argv[i]);

    // Allocate memory for a new node
    node *n = malloc(sizeof(node));
    if(!n) {
      fprintf(stderr, "Memory not allocated to *n\n");
    }
    // The n->data gets the new value
    n->data = num;
    // The n->next points to the current head
    n->next = list;
    // Update the list to point to the new node (new head)
    list = n;
  }

  // Print the values stored in the linked list
  // Start from the head of the list
  node *ptr = list;

  // Loop the list until the end (NULL)
  while (ptr != NULL) {
    // Print the data in the current node
    printf("%d\n", ptr->data);
    // Move to the next node in the list
    ptr = ptr->next;
  }
  return 0;
}
