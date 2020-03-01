/*
  Main.c
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 1/Mar/2020
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "AgentNode.h"
#include "StringNode.h"

/*
  deleteAllStrings
  Deletes a string linked list.
  @param head Pointer to pointer to head of linked list.
*/
void deleteAllStrings(StringNode** head) {
  StringNode* curr = *head;
  while (curr != NULL) {
    *head = (*head)->next;
    free(curr);
    curr = *head;
  }
}

/*
  deleteAllAgents
  Deletes an agent linked list.
  @param head Pointer to pointer to head of linked list.
*/
void deleteAllAgents(AgentNode** head) {
  AgentNode* curr = *head;

  while (curr != NULL) {
    *head = (*head)->next;

    // first delete the string lists
    deleteAllStrings(&curr->val.actives);
    deleteAllStrings(&curr->val.missions);
    free(curr);
    curr = *head;
  }
}

/*
  processAction
  Waits for an action to be processed...
*/
void processAction() {
  printf("Procesando accion...\n");
  sleep(1);
}

/*
  validateActiveCode
  @param code Pointer to the code string to check.
  @return Whether the mission ID is valid or not.
*/
bool validateActiveCode(const char* code) {
  int n = strlen(code);
  int letterCount = 0, numberCount = 0;

  if (n < 13) {
    return false;
  }

  // count letters
  for (int i = 0; i < n; i++) {
    if (isalpha(code[i])) {
      letterCount++;
    }
  }

  // count numbers
  for (int i = 0; i < n; i++) {
    if (isdigit(code[i])) {
      numberCount++;
    }
  }

  return letterCount == 4 && numberCount == 9;
}

/*
  validateMissionID
  Validates that a mission ID follows the ID rules.
  @param mission Pointer to the mission string to check.
  @return Whether the mission ID is valid or not.
*/
bool validateMissionID(const char* mission) {
  if (strlen(mission) < 12) {
    return false;
  }

  // make sure starts with three letters
  for (int i = 0; i < 3; i++) {
    if (!isalpha(mission[i])) {
      return false;
    }
  }

  // make sure the last nine are digits
  for (int i = 3; i < 12; i++) {
    if (!isdigit(mission[i])) {
      return false;
    }
  }

  return true;
}

/*
  createAgent
  Follows the input process to create a new agent.
  @param agents Pointer to pointer to head of list to add agent to.
*/
void createAgent(AgentNode** agents) {
  Agent agent = {0};
  char aux[20];

  printf("==NUEVO AGENTE==\n");
  printf("Nombre del agente: ");
  scanf("%s", &agent.name);

  printf("Apellido del agente: ");
  scanf("%s", &agent.lastName);

  printf("Activos de inteligencia asignados al agente (escribir '$' sin apostrofe para terminar lista):\n");
  while (true) {
    scanf("%s", &aux);
    
    // allow breaking out of loop
    if (strcmp(aux, "$") == 0) {
      break;
    }

    while (!validateActiveCode(aux)) {
      printf("Un activo debe tener 4 letras y 9 digitos.\n");
      scanf("%s", &aux);
    }

    // add to actives list
    stringNodePush(&agent.actives, aux);
  }

  printf("Edad: ");
  scanf("%d", &agent.age);

  printf("Misiones (escribir '&' sin apostrofes para terminar lista):\n");
  while (true) {
    scanf("%s", &aux);

    // allow breaking out of loop
    if (strcmp(aux, "$") == 0) {
      break;
    }

    while (!validateMissionID(aux)) {
      printf("Una mision debe tener 3 letras seguidas por 9 digitos.\n");
      scanf("%s", &aux);
    }

    // add to missons list
    stringNodePush(&agent.missions, aux);
  }

  // add to agents list
  agentNodePush(agents, &agent);
}

/*
  deleteAgent
  Handles input necessary to delete an agent.
  @param agents Pointer to pointer to agent list.
*/
void deleteAgent(AgentNode** agents) {
  int pos = 0;
  printf("Indicar el numero de agente que desea eliminar (si no existe, no hara nada): ");
  scanf("%d", &pos);
  agentNodeDelete(agents, pos);
}

/*
  printStringList
  Traverses and prints a string linked list.
  @param head Pointer to head of list.
*/
void printStringList(StringNode* head) {
  StringNode* curr = head;

  while (curr != NULL) {
    printf("%s", curr->val);
    if (curr->next != NULL) {
      printf(", ");
    }

    curr = curr->next;
  }

  printf("\n");
}

/*
  showAgents
  Prints the information of all agents.
  @param agents Pointer to agent list.
*/
void showAgents(AgentNode* agents) {
  AgentNode* curr = agents;
  int index = 0;

  if (curr == NULL) {
    printf("No hay agentes registrados.\n");
    return;
  }
  
  while (curr != NULL) {
    Agent agent = curr->val;
    printf("==AGENTE #%d %s %s==\n", index++, agent.name, agent.lastName);
    printf("Age: %d\n", agent.age);
    printf("Activos de inteligencia: ");
    printStringList(agent.actives);
    printf("Misiones: ");
    printStringList(agent.missions);
    printf("\n");
    curr = curr->next;
  }
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  AgentNode* agents = NULL;
  int ans = 0;

  printf("Bienvenido agente.\n==MENU DE ACCIONES==\n");
  while (ans != 4) {
    printf("1 > Crear entrada\n");
    printf("2 > Eliminar entrada\n");
    printf("3 > Ver lista de entradas\n");
    printf("4 > Terminar ejecucion\n");
    printf("Ingrese el numero que corresponde a la accion: ");
    scanf("%d", &ans);

    switch (ans) {
      case 1:
        processAction();
        createAgent(&agents);
        break;
      case 2:
        processAction();
        deleteAgent(&agents);
        break;
      case 3:
        processAction();
        showAgents(agents);
        break;

      default:
        processAction();
        if (ans != 4) {
          printf("La accion %d no corresponde a nada del menu.\n", ans);
        }
    }
  }

  // free all memory
  deleteAllAgents(&agents);
  
  return 0;
}