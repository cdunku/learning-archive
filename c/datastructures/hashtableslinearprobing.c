#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// INITIAL_CAPACITY = 17, which is not a power of two.
// Use modulo (%) to compute indices correctly.
// Bitwise AND (hash & (capacity - 1)) only works if capacity is a power of two.
// AND is faster when capacity is always a power of two.
// Using % works for all sizes. More info: https://benhoyt.com/writings/hash-table-in-c/
#define INITIAL_CAPACITY 17


typedef struct ht_info { 

  char *value;
  char *key;
  // Helps us track whether if the node is deleted or not.
  // Much easier than freeing the deleted node and connecting everything again.
  bool tombstone;

} ht_info;

typedef struct ht {

  size_t capacity;
  size_t length;
  ht_info **items;

} ht;

size_t hash_key(char *k) {

  // FNV-1A hashing function
  size_t hash = 14695981039346656037ULL;

  for(unsigned char *p = (unsigned char*)k; *p; p++) {
    hash ^= (size_t)*p;
    hash *= 1099511628211ULL;
  }

  return hash;
}

ht *create_table() {
  ht *table = malloc(sizeof(ht));

  if(!table) {
    fprintf(stderr, "Table has not been created\n");
  }

  table->capacity = INITIAL_CAPACITY;
  table->length = 0;
  table->items = calloc(table->capacity, sizeof(ht *));

  if(!table->items) {
    fprintf(stderr, "Table content has not been initialised\n");
  }

  return table;
}

ht *table_expand(ht *table) {

  size_t ncapacity = table->capacity * 2;
  ht_info **nitems = calloc(ncapacity, sizeof(ht_info *));

  if(!nitems) {
    fprintf(stderr, "Failed to allocate memory to new table\n");
    return NULL;
  }

  for(size_t i = 0; i < table->capacity; i++) {
    // If the specific index in the old array is NULL, go to next index.
    if(table->items[i] == NULL || table->items[i]->tombstone) {
      continue;
    }
    // We rehash the key-value pairs because their position in the new array might change.
    // Something that was previously in index 3 can be in index 8.
    // This all depends on the capacity of the table.
    size_t hash_index = hash_key(table->items[i]->key) % ncapacity;
    
    // If the specific index already has a key-value pair, increment hash_index until it reaches NULL.
    while(nitems[hash_index] != NULL) {
      hash_index = (hash_index + 1) % ncapacity;
    }
    // If it reaches NULL then add the new key-value pair into that index.
    nitems[hash_index] = table->items[i];
  }

  // Free the previous table, and do the necessary updates.
  free(table->items);
  table->items = nitems;
  table->capacity = ncapacity;
  return table;
}

void set_key_val(ht* table, char *k, char *v) {

  if(table->length > table->capacity) { table = table_expand(table); }

  size_t index = hash_key(k) % table->capacity;

  size_t i = 0;
  size_t try = index;

  // Even if try == index, loop through the list at least once
  do {
    if(table->items[try] == NULL || table->items[try]->tombstone) {
      ht_info *item = malloc(sizeof(ht_info));

      item->value = strdup(v);
      item->key = strdup(k);
      table->items[try] = item;

      table->length++;

      return;
    }

    i++;
    try = (index + i) % table->capacity;

  } while(try != index);
}

void *get_key_val(ht* table, char *k) {

  size_t index = hash_key(k) % table->capacity;

  size_t i = 0;
  size_t try = index;

  while(table->items[try] != NULL || table->items[try]->tombstone) {
    if(strcmp(table->items[try]->key, k) == 0) {
      return table->items[try]->value;
    }

    i++;
    try = (index + i) % table->capacity; 
  }
  return NULL;
}

void delete_key_val(ht* table, char *k) {
  size_t index = hash_key(k) % table->capacity;
  
  size_t i = 0;
  size_t try = index;

  while(table->items[try] != NULL) {
    if(strcmp(table->items[try]->key, k) == 0) {
      table->items[try]->tombstone = true;
      return;
    }
    i++;
    try = (index + i) % table->capacity;
  }
  return;
}

void traverse_table(ht* table) {
  printf("Start\n");
  for(size_t i = 0; i < table->capacity - 1; i++) {
    if(table->items[i] == NULL) {
      printf("Index %d: (empty)\n", i);
    }
    else if(table->items[i]->tombstone) {
      printf("Index %d: (deleted)\n", i);
    }
    else {
      printf("Index: %d: key = %s, value = %s\n", i, table->items[i]->key, table->items[i]->value);
    }
  }
  printf("Total items: %zu\n", table->length);
  printf("Total capacity: %zu\n", table->capacity);
  printf("End\n");
}

void free_table(ht* table) {
  for(size_t i = 0; i < table->capacity; i++) {
    if(table->items[i] == NULL) { continue; }
    free(table->items[i]->key);
    free(table->items[i]->value);
    free(table->items[i]);
  }
  free(table->items);
  free(table);
}

int main(void) {
  ht* table = create_table();

  set_key_val(table, "name", "Alice");
  set_key_val(table, "age", "25");
  set_key_val(table, "city", "Vienna");
  set_key_val(table, "language", "C");
  set_key_val(table, "university", "TU Wien");

  printf("Initial table:\n");
  traverse_table(table);

  printf("Retrieve 'name': %s\n", (char*)get_key_val(table, "name"));
  printf("Retrieve 'city': %s\n", (char*)get_key_val(table, "city"));

  set_key_val(table, "city", "Graz");
  printf("Updated 'city': %s\n", (char*)get_key_val(table, "city"));

  for(int i = 0; i < 50; i++) {
    char key[32], val[32];
    sprintf(key, "key%d", i);
    sprintf(val, "val%d", i);
    set_key_val(table, key, val);
  }
  printf("After inserting 50 keys and resizing:\n");
  traverse_table(table);

  delete_key_val(table, "name");
  delete_key_val(table, "key10");
  delete_key_val(table, "key42");

  printf("After deletions (tombstones marked):\n");
  traverse_table(table);

  printf("Retrieve deleted 'name': %s\n", (char*)get_key_val(table, "name"));
  printf("Retrieve deleted 'key10': %s\n", (char*)get_key_val(table, "key10"));

  set_key_val(table, "new_key1", "new_val1");
  set_key_val(table, "new_key2", "new_val2");

  printf("After inserting new keys (should reuse tombstones):\n");
  traverse_table(table);

  free_table(table);

  return 0;
}

