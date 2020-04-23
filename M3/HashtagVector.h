/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 14/Apr/2020
*/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 3
#define private static

// Structure for holding information about a hashtag entry
typedef struct Hashtag {
  char name[100];
  int count;
} Hashtag;

// Structure for holding information about a hashtag vector
typedef struct HashtagVector HashtagVector;
struct HashtagVector {
  // Properties
  Hashtag* data;
  int head;
  int size;

  // Methods
  void (*destroy)(HashtagVector*);
  void (*push)(HashtagVector*, Hashtag*);
  Hashtag* (*find)(const HashtagVector*, char[100]);
  void (*print)(const HashtagVector*);
};

/*
  hashtagVectorDestroy
  Frees the memory allocated by the passed hashtag vector.
  @param self Hashtag vector to destroy.
*/
private void hashtagVectorDestroy(HashtagVector* self) {
  free(self->data);
  free(self);
}

/*
  hashtagVectorPush
  Pushes a new element into the vector, and resizes if necessary.
  @param self Hashtag vector to modify
  @param hastag Hashtag to insert into the vector.
*/
private void hashtagVectorPush(HashtagVector* self, Hashtag* hashtag) {
  Hashtag* ptr = self->data + self->head++;
  strcpy(ptr->name, hashtag->name);
  ptr->count = hashtag->count;

  // check to resize
  if (self->head >= self->size) {
    self->size *= 2;
    self->data = (Hashtag*)realloc(self->data, self->size);
  }
}

/*
  hashtagVectorFind
  Searches for an element by name in the hashtag vector.
  @param self Hashtag vector to search in
  @param name Name to search for in the vector
  @return Pointer to hashtag if found, NULL otherwise.
*/
private Hashtag* hashtagVectorFind(const HashtagVector* self, char name[100]) {
  for (int i = 0; i < self->head; i++) {
    if (strcmp(self->data[i].name, name) == 0) {
      return self->data + i;
    }
  }

  return NULL;
}

/*
  hashtagVectorPrint
  Prints a hashtag vector's elements in a formatted way.
  @param self Hashtag vector to print.
*/
private void hashtagVectorPrint(const HashtagVector* self) {
  for (int i = 0; i < self->head; i++) {
    printf("#%s: %d\n", self->data[i].name, self->data[i].count);
  }
}

/*
  hashtagVectorCreate
  Allocates a new hashtag vector.
  @return The newly allocated hashtag vector.
*/
HashtagVector* hashtagVectorCreate() {
  HashtagVector* res = (HashtagVector*)malloc(sizeof(HashtagVector));
  res->data = (Hashtag*)malloc(sizeof(Hashtag) * INITIAL_SIZE);
  res->head = 0;
  res->size = INITIAL_SIZE;
  res->destroy = hashtagVectorDestroy;
  res->push = hashtagVectorPush;
  res->find = hashtagVectorFind;
  res->print = hashtagVectorPrint;
  return res;
}