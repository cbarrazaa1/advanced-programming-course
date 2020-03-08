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
#include <stdarg.h>
#include "AgentNode.h"
#include "StringNode.h"

// Determines if output should be encrypted or not.
bool isEncrypted;

/*
  print
  Prints information encrypted if neccessary.
  @param format The format to use to print.
  @param args Arguments to embed in format string.
*/
void print(const char* format, ...) {
  va_list args;
  char* copy = malloc(strlen(format) + 1);
  strcpy(copy, format);
  
  if (isEncrypted) {
    // encrypt by adding characters by themselves, plus 10
    // example: a = (a + a) + 10
    for (int i = 0; i < strlen(copy); i++) {
      if (copy[i] == '\n') {
        continue;
      }

      if (copy[i] == '#') {
        i++;
        continue;
      }

      copy[i] += copy[i] + 10;
    }

    printf(copy, args);
  } else {
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
  }

  free(copy);
}

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
  print("Procesando accion...\n");
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

  print("==NUEVO AGENTE==\n");
  print("Nombre del agente: ");
  scanf("%s", agent.name);

  print("Apellido del agente: ");
  scanf("%s", agent.lastName);

  print("Activos de inteligencia asignados al agente (escribir '$' sin apostrofe para terminar lista):\n");
  while (true) {
    scanf("%s", aux);
    
    // allow breaking out of loop
    if (strcmp(aux, "$") == 0) {
      break;
    }

    while (!validateActiveCode(aux)) {
      print("Un activo debe tener 4 letras y 9 digitos.\n");
      scanf("%s", aux);
    }

    // add to actives list
    stringNodePush(&agent.actives, aux);
  }

  print("Edad: ");
  scanf("%d", &agent.age);

  print("Misiones (escribir '$' sin apostrofes para terminar lista):\n");
  while (true) {
    scanf("%s", aux);

    // allow breaking out of loop
    if (strcmp(aux, "$") == 0) {
      break;
    }

    while (!validateMissionID(aux)) {
      print("Una mision debe tener 3 letras seguidas por 9 digitos.\n");
      scanf("%s", aux);
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
  print("Indicar el numero de agente que desea eliminar (si no existe, no hara nada): ");
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
    print("%s", curr->val);
    if (curr->next != NULL) {
      print(", ");
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
    print("No hay agentes registrados.\n");
    return;
  }
  
  while (curr != NULL) {
    Agent agent = curr->val;
    print("==AGENTE #%d %s %s==\n", index++, agent.name, agent.lastName);
    print("Age: %d\n", agent.age);
    print("Activos de inteligencia: ");
    printStringList(agent.actives);
    print("Misiones: ");
    printStringList(agent.missions);
    print("\n");
    curr = curr->next;
  }
}

/*
  editAgentNode
  Allows editing or deleting an agent node.
  @param head Pointer to pointer of head of agent list.
  @param curr Node to edit.
  @param index Node index from start of list.
*/
void editAgentNode(AgentNode** head, AgentNode* curr, int index) {
  int ans = 0, ans2 = 0;

  print("==AGENTE %s %s==\n", &curr->val.name, &curr->val.lastName);
  while (ans != 3) {
    print("1 > Editar\n");
    print("2 > Borrar\n");
    print("3 > Salir\n");
    print("Ingrese el numero que corresponde a la accion: ");
    scanf("%d", &ans);

    switch (ans) {
      case 1:
        while (ans2 != 3) {
          char aux[14];
          print("1 > Agregar mision\n");
          print("2 > Agregar activo\n");
          print("3 > Cancelar accion\n");
          print("Ingrese el numero que corresponse a la accion: ");
          scanf("%d", &ans2);

          if (ans2 == 1) {
            print("Introduzca la mision: ");
            scanf("%s", aux);

            while (!validateMissionID(aux)) {
              print("Una mision debe tener 3 letras seguidas por 9 digitos.\n");
              scanf("%s", aux);
            }

            stringNodePush(&curr->val.missions, aux);
            break;
          } else if (ans2 == 2) {
            print("Introduzca el activo: ");
            scanf("%s", aux);

            while (!validateActiveCode(aux)) {
              print("Un activo debe tener 4 letras y 9 digitos.\n");
              scanf("%s", aux);
            }
            
            stringNodePush(&curr->val.actives, aux);
            break;
          }
        }
        break;
      case 2:
        agentNodeDelete(head, index);
        print("El agente ha sido borrado.\n");
        return;
      
      default:
        if (ans != 3) {
          printf("La accion %d no corresponde a nada del menu.\n", ans);
        }
        break;
    }
  }
}

/*
  findByLastName
  Searchs for a node that matches the given last name.
  @param head Pointer to pointer to head of list.
  @param lastName Last name to search for.
*/
void findByLastName(AgentNode** head, char* lastName) {
  AgentNode* curr = *head;
  int index = 0;

  while (curr != NULL) {
    if (strcmp(curr->val.lastName, lastName) == 0) {
      editAgentNode(head, curr, index);
      return;
    }
    curr = curr->next;
    index++;
  }

  printf("No se encontro ningun agente con el apellido %s.\n", lastName);
}

/*
  findByActive
  Searchs for a node that matches the given active.
  @param head Pointer to pointer to head of list.
  @param active Active to search for.
*/
void findByActive(AgentNode** head, char* active) {
  AgentNode* curr = *head;
  int index = 0;

  while (curr != NULL) {
    StringNode* sCurr = curr->val.actives;
    
    while (sCurr != NULL) {
      if (strcmp(sCurr->val, active) == 0) {
        editAgentNode(head, curr, index);
        return;
      }
      sCurr = sCurr->next;
    }

    curr = curr->next;
    index++;
  }

  printf("No se encontro ningun agente con el activo %s.\n", active);
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  const char* CORRECT_PASSWORD = "hola123";
  AgentNode* agents = NULL;
  int ans = 0;
  char password[15], lastName[20], active[14];

  printf("Introduzca el password para usar el sistema: ");
  scanf("%s", password);
  isEncrypted = (strcmp(password, CORRECT_PASSWORD) != 0);

  print("Bienvenido agente.\n==MENU DE ACCIONES==\n");
  while (ans != 6) {
    print("1 > Crear entrada\n");
    print("2 > Eliminar entrada\n");
    print("3 > Ver lista de entradas\n");
    print("4 > Buscar agente por apellido\n");
    print("5 > Buscar agente por activo\n");
    print("6 > Terminar ejecucion\n");
    print("Ingrese el numero que corresponde a la accion: ");
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
      case 4:
        processAction();

        print("Introducir apellido: ");
        scanf("%s", lastName);
        findByLastName(&agents, lastName);
        break;
      case 5:
        processAction();

        print("Introducir activo: ");
        scanf("%s", active);
        findByActive(&agents, active);

      default:
        processAction();
        if (ans != 6) {
          printf("La accion %d no corresponde a nada del menu.\n", ans);
        }
    }
  }

  // free all memory
  deleteAllAgents(&agents);
  
  return 0;
}