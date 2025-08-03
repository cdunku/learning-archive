#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node; 

int main(int argc, char **argv) {
  node *head = NULL;

  for(int i = 1; i < argc; i++) {
    int number = atoi(argv[i]);

    node *n = malloc(sizeof(node));
    if(!n) {
      puts("Node has not been allocated!");
      return 1;
    }

    n->data = number;
    n->next = NULL;

    // If n->data is smaller than the first element in the list
    if(!head || n->data < head->data) {
      // Update so that the head is the following element
      n->next = head;
      head = n;
    } else {
      node *ptr = head;
      while(ptr != NULL) {
        // If it reaches the last node, then append to the list.
        if(ptr->next == NULL) {
          ptr->next = n;
          break;
        }
        // If the current data is smaller than the data in the next node 
        if(n->data < ptr->next->data) {
          // Link the new node to the next node (this is where it should go)
          n->next = ptr->next;

          // Insert the new node after the current node 
          ptr->next = n;
          break;
        }
        // Advance to the next node until we reach NULL
        ptr = ptr->next;
      }
    }
  }

  // Print the list 
  for(node *ptr = head; ptr != NULL; ptr = ptr->next) {
    printf("%d ", ptr->data);
  }
  printf("\n");

  // Free the memory, by iterating through each node one by one
  node *tmp;
  while(head != NULL) {
    tmp = head;
    head = head->next;
    free(tmp);
  }

  return 0;
}

