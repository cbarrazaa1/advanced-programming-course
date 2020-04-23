/*
  Authors: 
    César Francisco Barraza Aguilar, A01176786
    Patricio Andrés Saldivar Flores, A01282504
  Date: 21/Apr/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef int (*BinaryToIntFunc)(const char*);
typedef int (*HexToIntFunc)(const char*);
typedef double (*AsciiToDoubleFunc)(const char*);

/*
  asciiBinaryToInt
  @param s String to convert to int.
  @return Integer conversion from binary string.
*/
int main(int argc, const char** argv) {
  int iRes = 0; 
  double dRes = 0;
  BinaryToIntFunc asciiBinaryToInt = NULL;
  HexToIntFunc asciiHexToInt = NULL;
  AsciiToDoubleFunc asciiToDouble = NULL; 
  HMODULE dll = LoadLibraryA("P13.dll");

  if (dll == NULL) {
    fprintf(stderr, "Error loading DLL with error code: %d.\n", GetLastError());
    exit(-1);
  }

  // load functions
  asciiBinaryToInt = (BinaryToIntFunc)GetProcAddress(dll, "asciiBinaryToInt");
  asciiHexToInt = (HexToIntFunc)GetProcAddress(dll, "asciiHexToInt");
  asciiToDouble = (AsciiToDoubleFunc)GetProcAddress(dll, "asciiToDouble");

  if (
    asciiBinaryToInt == NULL
    || asciiHexToInt == NULL
    || asciiToDouble == NULL
  ) {
    fprintf(stderr, "Error loading DLL functions.\n");
    exit(-1);
  }

  // use functions
  iRes = asciiBinaryToInt("1111");
  printf("1111 Bin = %d Dec\n", iRes);

  iRes = asciiHexToInt("CAFE");
  printf("CAFE Hex = %d Dec\n", iRes);

  dRes = asciiToDouble("1.234");
  printf("%lf\n", dRes);
  return 0;
}