/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 27/Mar/2020
*/
#pragma once
#include <string.h>

extern const int ONES_COUNT;
extern const int TENS_COUNT;
extern const int HUNDREDS_COUNT;
extern const int SPECIAL_COUNT;
extern char* ones[];
extern char* tens[];
extern char* hundreds[];
extern char* special[];

/*
  isInOnes
  Check if a string is in the ones set.
  @param s String to check.
  @return Index of the string if found, -1 otherwise.
*/
int isInOnes(const char* s);

/*
  isInTens
  Check if a string is in the tens set.
  @param s String to check.
  @return Index of the string if found, -1 otherwise.
*/
int isInTens(const char* s);

/*
  isInHundreds
  Check if a string is in the hundreds set.
  @param s String to check.
  @return Index of the string if found, -1 otherwise.
*/
int isInHundreds(const char* s);

/*
  isInSpecial
  Check if a string is in the special set.
  @param s String to check.
  @return Index of the string if found, -1 otherwise.
*/
int isInSpecial(const char* s);

/*
  mapOnesToNumber
  Maps a number found in the ones set to its numerical representation.
  @param index Position in the set.
  @return The numerical representation.
*/
int mapOnesToNumber(int index);

/*
  mapTensToNumber
  Maps a number found in the tens set to its numerical representation.
  @param index Position in the set.
  @return The numerical representation.
*/
int mapTensToNumber(int index);

/*
  mapHundredsToNumber
  Maps a number found in the hundreds set to its numerical representation.
  @param index Position in the set.
  @return The numerical representation.
*/
int mapHundredsToNumber(int index);

/*
  mapSpecialToNumber
  Maps a number found in the special set to its numerical representation.
  @param index Position in the set.
  @return The numerical representation.
*/
int mapSpecialToNumber(int index);