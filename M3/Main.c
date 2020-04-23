/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 14/Apr/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "HashtagVector.h"

/*
  isColor
  Determines if a string is a hexadecimal color.
  @param s String to check
  @return Whether the string is a hexadecimal color or not.
*/
bool isColor(const char* s) {
  for (int i = 0; i < strlen(s); i++) {
    if (!((s[i] >= 'a' && s[i] <= 'f') || (s[i] >= '0' && s[i] <= '9'))) {
      return false;
    }
  }

  return true;
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  FILE* file = NULL;
  char fileName[30];

  // read file name from user
  printf("Enter file name to read: ");
  scanf("%s", fileName);

  // try to open file
  file = fopen(fileName, "r");
  while (file == NULL) {
    printf("Could not open file '%s'.\n", fileName);
    printf("Enter file name to read: ");
    scanf("%s", fileName);
    file = fopen(fileName, "r");
  }

  // start reading char by char
  HashtagVector* vec = hashtagVectorCreate();
  char ch, prev;
  char aux[100];
  int auxPos = 0;
  bool foundHashtag = false;
  bool inBody = false;
  bool foundBody = false;
  while ((ch = fgetc(file)) != EOF) {
    if (foundHashtag) {
      if (ch == '\n') {
        foundHashtag = false;
        auxPos = 0;
        continue;
      }

      // check if hashtag has ended
      if (ch == ' ' || ch == '"' || ch == '<') {
        foundHashtag = false;
        aux[auxPos++] = '\0';
        auxPos = 0;
        strcpy(aux, strlwr(aux));

        if (isColor(aux)) {
          continue;
        }

        Hashtag* hashtag = vec->find(vec, aux);
        if (hashtag == NULL) {
          Hashtag newHashtag;
          strcpy(newHashtag.name, aux);
          newHashtag.count = 1;
          vec->push(vec, &newHashtag);
        } else {
          hashtag->count++;
        }
      } else {
        aux[auxPos++] = ch;
      }
    }
  
    // found hashtag, start reading it in next iteration
    if (ch == '#') {
      foundHashtag = true;
    }

    // found
    if (ch == '<') {

    }

    prev = ch;
  }

  vec->print(vec);
  vec->destroy(vec);
  return 0;
}