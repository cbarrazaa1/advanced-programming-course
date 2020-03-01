/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 22/Feb/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Make gender handling a bit easier to follow and read
#define GENDER_MALE 0
#define GENDER_FEMALE 1
typedef int gender_t;

// Structure to handle an agent's information
typedef struct {
  char name[20];
  char lastName[20];
  int age;
  gender_t gender;
  char mission[13];
} agent;

/*
  printAgent
  Shows an agent's information.
  @param agent Pointer to agent to show information from.
*/
void printAgent(const agent* agent) {
  printf("==AGENT %s %s==\n", agent->name, agent->lastName);
  printf("Age: %d\n", agent->age);
  printf("Gender: %c\n", agent->gender == GENDER_MALE ? 'M' : 'F');
  printf("Mission ID: %s\n", agent->mission);
}

/*
  validateName
  Validates that a name only has alpha characters.
  @param s Pointer to string to check.
  @return Whether the name is valid or not.
*/
bool validateName(const char* s) {
  for (int i = 0; i < strlen(s); i++) {
    if (!isalpha(s[i])) {
      return false;
    }
  }

  return true;
}

/*
  validateAgeString
  Validates that an age string is actually a number.
  @param s Pointer to string holding the age.
  @return Whether the age is valid or not.
*/
bool validateAgeString(const char* s) {
  for (int i = 0; i < strlen(s); i++) {
    if (!isdigit(s[i])) {
      return false;
    }
  }

  return true;
}

/*
  validateGender
  Validates that a gender is correct.
  @param gender Character denoting the gender to check.
  @return Whether the gender is valid or not.
*/
bool validateGender(char gender) {
  return gender == 'M' || gender == 'F';
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
  getUserInput
  Reads all the needed input from the user. Validates when needed.
  @param agent Pointer to agent whose information is being read.
*/
void getUserInput(agent* agent) {
  char gender = 0;
  char ageString[3];

  printf("Hello agent,\nPlease enter your name: ");
  scanf("%s", &agent->name);

  // validate name only has letters
  while (!validateName(agent->name)) {
    printf("Please enter a valid name (only letters): ");
    scanf("%s", &agent->name);
  }

  printf("Please enter your last name: ");
  scanf("%s", &agent->lastName);

  // validate last name only has letters
  while (!validateName(agent->lastName)) {
    printf("Please enter a valid last name (only letters): ");
    scanf("%s", &agent->lastName);
  }

  printf("Please enter your age: ");
  scanf("%s", &ageString);

  // validate age is a number
  while (!validateAgeString(ageString)) {
    printf("Please enter a valid age: ");
    scanf("%s", &ageString);
  }
  agent->age = atoi(ageString);

  printf("Please enter your gender (M or F): ");
  scanf(" %c", &gender);

  // validate gender
  while (!validateGender(gender)) {
    printf("Please enter a valid gender (M or F, case sensitive): ");
    scanf(" %c", &gender);
  }
  agent->gender = gender == 'M' ? GENDER_MALE : GENDER_FEMALE;

  printf("Please enter your mission ID: ");
  scanf("%s", &agent->mission);

  // validate mission ID
  while (!validateMissionID(agent->mission)) {
    printf("Please enter a valid mission ID (must be 12 characters long, start with 3 letters): ");
    scanf("%s", &agent->mission);
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
  agent agent;

  getUserInput(&agent);
  printAgent(&agent);
  return 0;
}