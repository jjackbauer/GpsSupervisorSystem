#ifndef NMEASCANNER_H_
#define NMEASCANNER_H_
#include <stdio.h>
#include <string.h>
#include "USART.h"

#define Buffer 100

char currentSpelling[Buffer];  //string corrente
char mensage[Buffer];
int cSpelling;//topo da pilha
char currentChar;

char getCurrentChar(void);
void appendSpelling(char a);
void flushSpelling(void);
char* scanNmea(char* mensageCode);

#endif /* NMEASCANNER_H_ */