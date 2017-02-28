#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

int line_num = 1;
struct token *head=NULL, *last=NULL;

void appendSymbol(int id) {
    struct token *curr = (struct token*)malloc(sizeof(struct token));

    switch(id) {
        case 1 : strcpy(curr->type, "COLON\0");
            break;
        case 2 : strcpy(curr->type, "ASSIGNOP\0");
            break;
        case 3 : strcpy(curr->type, "COMMA\0");
            break;
        case 4 : strcpy(curr->type, "NE\0");
            break;
        case 5 : strcpy(curr->type, "RANGEOP\0");
            break;
        case 6 : strcpy(curr->type, "GT\0");
            break;
        case 7 : strcpy(curr->type, "ENDDEF\0");
            break;
        case 8 : strcpy(curr->type, "GE\0");
            break;
        case 9 : strcpy(curr->type, "SEMICOL\0");
            break;
        case 10 : strcpy(curr->type, "EQ\0");
            break;
        case 11 : strcpy(curr->type, "MINUS\0");
            break;
        case 12 : strcpy(curr->type, "LT\0");
            break;
        case 13 : strcpy(curr->type, "DEF\0");
            break;
        case 14 : strcpy(curr->type, "LE\0");
            break;
        case 15 : strcpy(curr->type, "PLUS\0");
            break;
        case 16 : strcpy(curr->type, "MUL\0");
            break;
        case 17 : strcpy(curr->type, "COMMENTMARK\0");
            break;
        case 18 : strcpy(curr->type, "DIV\0");
            break;
        case 19 : strcpy(curr->type, "SQBO\0");
            break;
        case 20 : strcpy(curr->type, "SQBC\0");
            break;
        case 21 : strcpy(curr->type, "BO\0");
            break;
        case 22 : strcpy(curr->type, "BC\0");
            break;
        case 23 : strcpy(curr->type, "DRIVERDEF\0");
            break;
        case 24 : strcpy(curr->type, "DRIVERENDDEF\0");
            break;
        case 25 : strcpy(curr->type, "NUM\0");
            break;
        case 26 : strcpy(curr->type, "RNUM\0");
            break;
        case 27 : strcpy(curr->type, "ID\0");
            break;
    }
    curr->next = NULL;
    curr->line_num = line_num;
    curr->prev = last;
    last->next = curr;
    last = last->next;
}

void addKeyword(char *keyword) {
    struct token *curr = (struct token*)malloc(sizeof(struct token));

    int i=0;
    while (keyword[i])
        keyword[i] = toupper(keyword[i++]);
    strcpy(curr->type, keyword);
    curr->next = NULL;
    curr->line_num = line_num;
    curr->prev = last;
    last->next = curr;
    last = last->next;
}

int isKeyword(char *word) {
    char *list[30] = {"declare\0", "driver\0", "program\0", "for\0", "start\0", "end\0", "module\0", "get_value\0", "print\0",
                    "use\0", "with\0", "parameters\0", "true\0", "false\0", "takes\0", "input\0", "returns\0", "AND\0", "OR\0", 
                    "switch\0", "case\0", "break\0", "default\0", "while\0", "integer\0", "real\0", "boolean\0", "of\0", "array\0",
                    "in\0" };
    int i=0;
    while (i < 30)
        if (strcmp(list[i++], word) == 0)
            return 1;
    return 0;
}

void matchSymbols(char *buf) {
    int index=0;
    int len = strlen(buf);
    int flag=0;
    char front = buf[index];

    while (index < len) {

        if ((front >= 'A' && front <= 'Z') || (front >= 'a' && front <= 'z')) {
            char id[20];
            int i=0;
            id[i++] = front;
            index++;
            while ((buf[index]>='A' && buf[index]<='Z') || (buf[index]>='a' && buf[index]<='z') || buf[index]=='_' || (buf[index]>='0' && buf[index]<='9') && buf[index]!='\n')
                id[i++] = buf[index++];
            
            id[i] = '\0';
            if (isKeyword(id))
                addKeyword(id);
            else if (i > 8) {
                //printf(" Identifier at line %d is longer than the prescribed length\n", line_num);Handle the ERROR
            }
            else
                appendSymbol(27);
            index--;
        }
        
        else if (front >= '0' && front <= '9') {
            front = buf[++index];
            while (front >= '0' && front <= '9')
                front = buf[++index];

            if (front != '.')
                appendSymbol(25);

            else {
                if (buf[index+1] == '.')
                    appendSymbol(25);
                else {
                    front = buf[++index];
                    while (front >= '0' && front <= '9')
                        front = buf[++index];
                    if (front == 'E' || front == 'e') {
                        front = buf[++index];
                        if (front == '+' || front == '-')
                            front = buf[++index];
                        while (front >= '0' && front <= '9')
                            front = buf[++index];
                    }
                    appendSymbol(26);
                }
            }
            index--;
        }
        
        else if (front == ':') {
            if (buf[index+1] == '=') {
                index++;
                appendSymbol(2);
            }
            else
                appendSymbol(1);
        }
        else if (front == ',')
            appendSymbol(3);
        
        else if (front == '!') {
            if (buf[index+1] == '=') {
                index++;
                appendSymbol(4);
            }
            else
                ;// printf("Unknown Symbol !%c at line %d", buf[index+1], line_num);Handle the ERROR
        }

        else if (front == '.') {
            if (buf[index+1] == '.') {
                index++;
                appendSymbol(5);
            }
            else
                ;// printf("Unknown Symbol .%c at line %d", buf[index+1], line_num);Handle the ERROR
        }

        else if (front == '>') {
			if (buf[index+1] == '=') {			
			    appendSymbol(8);
				index++;			
			}
			else if (buf[index+1] == '>') {
				if (buf[index+2]=='>') {			
				    appendSymbol(24);
					index+=2;
				}
				else {
				    appendSymbol(7);
					index++;
				}
			}
			else
                appendSymbol(6);
		}
        else if (front == ';')
            appendSymbol(9);
        
        else if (front == '=') {
            if (buf[index+1] == '=') {
                index++;
                appendSymbol(10);
            }
            else
                ;// printf("Unknown Symbol =%c at line %d", buf[index+1], line_num);Handle the ERROR
        }
        else if (front == '-')
            appendSymbol(11);

        else if (front == '<') {
			if (buf[index+1] == '=') {			
			    appendSymbol(14);
				index++;			
			}
			else if (buf[index+1] == '<') {
				if (buf[index+2]=='<') {			
					appendSymbol(23);
					index+=2;
				}
				else {
				    appendSymbol(13);
					index++;
				}
			}
			else
                appendSymbol(12);
		}

        else if (front == '*') {
            if (buf[index+1] == '*') {
                appendSymbol(17);
                index++;
                if (!flag)
                    flag = 1;
                else {
                    flag = 0;
                    front = buf[++index];
                    continue;
                }

                while (!((buf[index] == '*') && (buf[index+1] == '*')) && (index < len))
				    index++;
                index--;
            }
            else
                appendSymbol(16);
        }

        else if (front == '+')
            appendSymbol(15);	
        else if (front == '/')
            appendSymbol(18);
        else if (front == '[')
            appendSymbol(19);
        else if (front == ']')
            appendSymbol(20);
        else if (front == '(')
            appendSymbol(21);
        else if (front == ')')
            appendSymbol(22);
        else if (front == '\n')
            line_num++;
        
        front = buf[++index];
		while (front == ' ' || front == '\t')
            front = buf[++index];
    }
}

FILE* getStream(FILE *fp, char *buf) {
    buf[0] = '\0';

    fgets(buf, BUFFER_SIZE+1, fp);
    if (buf[0] == '\0')
        return NULL;

    if (strlen(buf) == BUFFER_SIZE) {
        int i = BUFFER_SIZE-1;
        while (!(buf[i] != ' ' || buf[i] != '\t' || buf[i] != '\n'))
            i--;

        buf[i+1] = '\0';
        fseek(fp, -(BUFFER_SIZE-1-i), SEEK_CUR);
    }
    return fp;
}

void generateList(char *file) {
    FILE *read = fopen(file,"r");
    char buf[BUFFER_SIZE+1];
    head = (struct token*)malloc(sizeof(struct token));
    last = head;
    read = getStream(read, buf);
    while(read != NULL) {
        matchSymbols(buf);
        read = getStream(read, buf);
    }
}

void printlist() {
    struct token *temp = head->next;
    while (temp != NULL) {
        printf("%s\n",temp->type);
        temp = temp->next;
    }
}