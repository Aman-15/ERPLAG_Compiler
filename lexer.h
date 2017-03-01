#ifndef lexer
#define lexer
#include <stdio.h>

#define BUFFER_SIZE 100

enum enum_token {
    DECLARE, DRIVER, PROGRAM, FOR, START, END, MODULE, GET_VALUE, PRINT, USE, WITH, PARAMETERS, TRUE, FALSE,
    TAKES, INPUT, RETURNS, AND, OR, SWITCH, CASE, BREAK, DEFAULT, WHILE, INTEGER, REAL, BOOLEAN, OF, ARRAY, 
    IN, ID, RNUM, NUM, COLON, ASSIGNOP, COMMA, NE, RANGEOP, GT, ENDDEF, GE, SEMICOL, EQ, MINUS, LT, DEF,
    LE, PLUS, MUL, COMMENTMARK, DIV, SQBO, SQBC, BO, BC, DRIVERDEF, DRIVERENDDEF, $, e
};

struct token {
    enum enum_token tokenID;
    char lexeme[20];
    struct token *prev, *next;
    int line_num;
};

void appendSymbol(int id);
void addKeyword(int id, char *keyword);
int isKeyword(char *word);
void addID(char *id);
void addNUM(int n_or_r, char *num);
void matchSymbols(char *buf);
FILE* getStream(FILE *fp, char *buf);
void generateList(char *file);
struct token* getNextToken();
void printlist();
void removeComments(char *testcaseFile, char *cleanFile);

#endif // lexer