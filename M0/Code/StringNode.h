/*
  StringNode.h
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 1/Mar/2020
*/
#pragma once
#include <stdlib.h>
#include <string.h>

// Structure that holds information about a list node.
typedef struct StringNode {
  char val[14];
  struct StringNode* next;
} StringNode;

/*
  stringNodeNew
  Creates a new string node with the given value.
  @param val Pointer to string to add to node.
  @return Pointer to newly created string node.
*/
StringNode* stringNodeNew(char* val);

/*
  stringNodePush
  Adds a new string node to an existing list.
  @param head Pointer to pointer to head node of list.
  @param str Pointer to string to add to the list.
*/
void stringNodePush(StringNode** head, char* str);