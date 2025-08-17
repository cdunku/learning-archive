#include <stdio.h>
#include <string.h>

// NOTE: THERE ARE NOT BUFFER OVERFLOW CHECKS!

#define MAX_SIZE 100

int size = 0;
// [MAX_SIZE] - how many keys I can store 
// [50] - how long the keys will be
char keys[MAX_SIZE][50];
int values[MAX_SIZE];

int get_index(char *key) {
  for(size_t i = 0; i < size; i++) {
    if(strcmp(keys[i], key) == 0) {
      return i;
    }
  }
  return -1;
}

void insert_value_key(char *key, int data) {
  
  int index = get_index(key);
  // Create new key
  if(index == -1) {
    strcpy(keys[size], key);
    values[size] = data;
    size++;
  }
  else {
    //Ket found
    values[index] = data;
  }
}

int get_value(char *key) {
  
  int index = get_index(key);

  if(index == -1) {
    printf("Value not found\n");
    return -1;
  }
  else { 
    return values[index];
  }
}

void print_dictionary() {
  for(size_t i = 0; i < size; i++) {
    printf("Key: %s | Value: %d\n", keys[i], values[i]);
  }
}

int main() {

  insert_value_key("John", 1);
  insert_value_key("Mary", 3);
  insert_value_key("Brian", 8);
  insert_value_key("Apples", 10);

  printf("Complete map value:\n");
  print_dictionary();
  printf("\n");

  printf("What number is Brian?\n");
  printf("Brian is number %d\n\n", get_index("Brian"));

  printf("How many Apples are there?\n");
  printf("Number of apples: %d\n", get_value("Apples"));
  return 0;
}
