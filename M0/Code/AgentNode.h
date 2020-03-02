/*
  AgentNode.h
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 1/Mar/2020
*/
#pragma once
#include <stdlib.h>

// Structure that holds information about the agent.
typedef struct Agent {
  char name[20];
  char lastName[20];
  struct StringNode* actives;
  int age;
  struct StringNode* missions;
} Agent;

// Structure that holds information about a list node.
typedef struct AgentNode {
  struct Agent val;
  struct AgentNode* next;
} AgentNode;

/*
  agentNodeNew
  Creates a new agent node with the given value.
  @param val Pointer to agent to add to node.
  @return Pointer to newly created agent node.
*/
AgentNode* agentNodeNew(Agent* val);

/*
  agentNodePush
  Adds a new agent node to an existing list.
  @param head Pointer to pointer to head node of list.
  @param agent Pointer to agent to add to the list.
*/
void agentNodePush(AgentNode** head, Agent* agent);

/*
  agentNodeDelete
  Delete an agent node from an existing list.
  If pos is not found, does nothing.
  @param head Pointer to pointer to head node of list.
  @param pos Position of the node to delete.
*/
void agentNodeDelete(AgentNode** head, int pos);
