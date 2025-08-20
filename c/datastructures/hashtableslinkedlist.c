#include <stdio.h>

typedef struct hash_info {
  char *name;
  int age;
  char *key; // Current key of the hash
} hash_info;

typedef struct hash_table {
  size_t length; // Current table length
  size_t capacity; // Maximum capacity of a table 

  hash_info *items; // Pointer to the hash items 
} hash_table;
