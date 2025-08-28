#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_TABLE_INITIAL_CAPACITY 16

typedef struct hash_info {
  char *name;
  char *key; // Current key of the hash

  struct hash_info *next; // Linked list for each index for handling collisions
} hash_info;

typedef struct hash_table {
  size_t length; // Current table length
  size_t capacity; // Maximum capacity of a table 

  hash_info **items; // Array holding the hash buckets (linked list inside each bucket) 
} hash_table;

size_t hash_key(char *k) {

  // FNV-1A hashing function
  size_t hash = 14695981039346656037ULL;

  for(unsigned char *p = (unsigned char*)k; *p; p++) {
    hash ^= (size_t)*p;
    hash *= 1099511628211ULL;
  }

  return hash;
}

char *get_hash_value(hash_table *table, char *k) {

  size_t index = hash_key(k) % table->capacity;
  hash_info *item = table->items[index];

  while(item != NULL) {
    if(strcmp(item->key, k) == 0) { 
      return item->name; 
    } 
    item = item->next; 
  }
  return NULL;
}
void set_hash_value(hash_table *table, char *k, char *v) {

  size_t index = hash_key(k) % table->capacity;
  hash_info *item = table->items[index];

  // Checks whether if this hash inside a bucker already exists
  while(item != NULL) {
    // Key found, replace the value
    if(strcmp(item->key, k) == 0) {
      // Free the value from memory, so the result is NULL
      free(item->name);

      // Replace the old value with the new one 
      item->name = strdup(v);
      return;
    }
    item = item->next;
  }

  hash_info *item_add = malloc(sizeof(hash_info));

  // Add a new key-value pair
  item_add->name = strdup(v);
  item_add->key = strdup(k);

  // Prepend the new node to the list
  item_add->next = table->items[index];
  table->items[index] = item_add;

  // Updates the length of the list
  table->length++;
}

hash_table *create_hash_table() {
  hash_table *table = malloc(sizeof(hash_table));

  if(!table) {
    printf("Table not allocated properly\n");
    return NULL;
  } 

  // Set the initial capacity of this specific table
  table->capacity = HASH_TABLE_INITIAL_CAPACITY;
  // Helps us determine how many buckets are used
  table->length = 0;

  // Allocate memory to the table
  table->items = calloc(table->capacity, sizeof(hash_info *));

  if(!table->items) {
    printf("Table not properly created\n");
    free(table);
    return NULL;
  }

  return table;
}
void resize_hash_table(hash_table *table) {
  // Avoiding the table to be full helps us avoid O(n)
  if(!(table->length >= table->capacity / 2)) return;

  // Increase the table capacity
  table->capacity *= 2;

  hash_info **new_items = calloc(table->capacity, sizeof(hash_info *));

  for(size_t i = 0; i < table->capacity / 2; i++) {
    hash_info *node = table->items[i];
    while(node != NULL) {
      size_t rehash_index = hash_key(node->key) % table->capacity;
      hash_info *next = node->next;

      node->next = new_items[rehash_index];
      new_items[rehash_index] = node;

      node = next;
    } 
  }
  free(table->items);
  table->items = new_items;
}
void hash_table_free(hash_table *table) {

  // Since we delete the table the length is 0
  table->length = 0;

  for(size_t i = 0; i < table->capacity; i++) {
    hash_info *node = table->items[i];
    while(node != NULL) {
      hash_info *next = node->next;
      
      free(node->name);
      free(node->key);
      free(node);

      node = next;
    }
    table->items[i] = NULL;
  }
  free(table->items);
  free(table);
}
void hash_delete_bucket(hash_table *table, char *k) {
  size_t index = hash_key(k) % table->capacity;
  hash_info* bucket = table->items[index];
  
  while(bucket != NULL) {
    hash_info* next = bucket->next;

    free(bucket->name);
    free(bucket->key);
    free(bucket);

    bucket = next;

    table->length--;
  }

  table->items[index] = NULL;
}

int main(void) {
    // 1. Create table
    hash_table *ht = create_hash_table();
    if (!ht) {
        printf("Failed to create table\n");
        return 1;
    }

    // 2. Insert some keys
    set_hash_value(ht, "name", "Alice");
    set_hash_value(ht, "age", "25");
    set_hash_value(ht, "city", "Vienna");
    set_hash_value(ht, "language", "C");
    set_hash_value(ht, "university", "TU Wien");

    // 3. Retrieve keys
    printf("name -> %s\n", get_hash_value(ht, "name"));
    printf("age -> %s\n", get_hash_value(ht, "age"));
    printf("city -> %s\n", get_hash_value(ht, "city"));
    printf("language -> %s\n", get_hash_value(ht, "language"));
    printf("university -> %s\n", get_hash_value(ht, "university"));

    // 4. Replace value
    set_hash_value(ht, "city", "Graz");
    printf("city (updated) -> %s\n", get_hash_value(ht, "city"));

    // 5. Force resize (insert many keys)
    for (int i = 0; i < 50; i++) {
        char key[32], val[32];
        sprintf(key, "key%d", i);
        sprintf(val, "val%d", i);
        set_hash_value(ht, key, val);
    }
    resize_hash_table(ht);
    printf("After resize: capacity = %zu, length = %zu\n", ht->capacity, ht->length);

    // 6. Retrieve a couple after resize
    printf("key10 -> %s\n", get_hash_value(ht, "key10"));
    printf("key42 -> %s\n", get_hash_value(ht, "key42"));

    // 7. Delete a bucket (fixed implementation!)
    // Let's delete "name"
    hash_delete_bucket(ht, "name");
    printf("name after delete -> %s\n", get_hash_value(ht, "name"));

    // 8. Free entire table
    hash_table_free(ht);

    printf("All tests finished.\n");
    return 0;
}

