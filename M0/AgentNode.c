/*
  AgentNode.c
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 1/Mar/2020
*/
#include "AgentNode.h"

AgentNode* agentNodeNew(Agent* val) {
  AgentNode* res = (AgentNode*)malloc(sizeof(AgentNode));
  res->val = *val;
  res->next = NULL;
  return res;
}

void agentNodePush(AgentNode** head, Agent* agent) {
  AgentNode* curr = *head;

  // the list is empty
  if (curr == NULL) {
    *head = agentNodeNew(agent);
    return;
  }

  // the list is not empty
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = agentNodeNew(agent);
}

void agentNodeDelete(AgentNode** head, int pos) {
  AgentNode* curr = *head;
  AgentNode* prev = NULL;
  int i = 0;

  if (curr != NULL && curr->next == NULL) {
    if (pos == 0) {
      prev = *head;
      *head = curr->next;
      free(prev);
    }
    return;  
  }

  // loop until we reach the index
  for (; i < pos && curr != NULL; i++) {
    prev = curr;
    curr = curr->next;
  }

  // we didn't find the index
  if (prev == NULL || curr == NULL) {
    return;
  }

  // we did find the index, so delete
  prev->next = curr->next;
  free(curr);
}
