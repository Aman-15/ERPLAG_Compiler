#ifndef lexer
#define lexer
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

struct token {
    char type[20];
    struct token *prev, *next;
    int line_num;
};

void appendSymbol(int id);
void addKeyword(char *keyword);
int isKeyword(char *word);
void matchSymbols(char *buf);
FILE* getStream(FILE *fp, char *buf);
void generateList(char *file);
void printlist();

#endif // lexer