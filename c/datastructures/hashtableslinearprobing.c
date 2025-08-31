#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 17

typedef struct ht_info { 

  char *value;
  char *key;

} ht_info;

typedef struct ht {

  size_t capacity;
  size_t length;
  ht_info *items;

} ht;

ht *create_table() {
  ht *table = malloc(sizeof(ht));

  if(!table) {
    fprintf(stderr, "Table has not been created\n");
  }

  table->capacity = INITIAL_CAPACITY;
  table->length = 0;
  table->items = calloc(table->capacity, sizeof(ht));

  if(!table->items) {
    fprintf(stderr, "Table content has not been initialised\n");
  }

  return table;
}

int main(void) {


  return 0;
}
