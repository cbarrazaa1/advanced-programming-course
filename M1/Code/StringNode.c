/*
  StringNode.c
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 1/Mar/2020
*/
#include "StringNode.h"

StringNode* stringNodeNew(char* val) {
  StringNode* res = (StringNode*)malloc(sizeof(StringNode));
  strcpy(res->val, val);
  res->next = NULL;
  return res;
}

void stringNodePush(StringNode** head, char* str) {
  StringNode* curr = *head;
  if (curr == NULL) {
    *head = stringNodeNew(str);
    return;
  }

  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = stringNodeNew(str);
}