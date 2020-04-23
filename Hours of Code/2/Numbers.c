/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 27/Mar/2020
*/
#include "Numbers.h"

const int ONES_COUNT = 10;
const int TENS_COUNT = 8;
const int HUNDREDS_COUNT = 1;
const int SPECIAL_COUNT = 19;

char* ones[] = {
  "cero",
  "uno",
  "dos",
  "tres",
  "cuatro",
  "cinco",
  "seis",
  "siete",
  "ocho",
  "nueve"
};

char* tens[] = {
  "veinte",
  "treinta",
  "cuarenta",
  "cincuenta",
  "sesenta",
  "setenta",
  "ochenta",
  "noventa"
};

char* hundreds[] = {
  "cien"
};

char* special[] = {
  "diez",
  "once",
  "doce",
  "trece",
  "catorce",
  "quince",
  "dieciseis",
  "diecisiete",
  "dieciocho",
  "diecinueve",
  "veintiuno",
  "veintidos",
  "veintitres",
  "veinticuatro",
  "veinticinco",
  "veintiseis",
  "veintisiete",
  "veintiocho",
  "veintinueve"
};

int isInOnes(const char* s) {
  for (int i = 0; i < ONES_COUNT; i++) {
    if (strcmp(s, ones[i]) == 0) {
      return i;
    }
  }

  return -1;
}

int isInTens(const char* s) {
  for (int i = 0; i < TENS_COUNT; i++) {
    if (strcmp(s, tens[i]) == 0) {
      return i;
    }
  }

  return -1;
}

int isInHundreds(const char* s) {
  for (int i = 0; i < HUNDREDS_COUNT; i++) {
    if (strcmp(s, hundreds[i]) == 0) {
      return i;
    }
  }

  return -1;
}

int isInSpecial(const char* s) {
  for (int i = 0; i < SPECIAL_COUNT; i++) {
    if (strcmp(s, special[i]) == 0) {
      return i;
    }
  }
  
  return -1;
}

int mapOnesToNumber(int index) {
  if (index < 0 || index >= ONES_COUNT) {
    return 0;
  }

  return index;
}

int mapTensToNumber(int index) {
  if (index < 0 || index >= TENS_COUNT) {
    return 0;
  }

  return (index + 2) * 10;
}

int mapHundredsToNumber(int index) {
  if (index < 0 || index >= HUNDREDS_COUNT) {
    return 0;
  }

  return (index + 1) * 100;
}

int mapSpecialToNumber(int index) {
  if (index < 0 || index >= SPECIAL_COUNT) {
    return 0;
  }

  if (index >= 10) {
    return 20 + (index - 9);
  }
  
  return index + 10;
}