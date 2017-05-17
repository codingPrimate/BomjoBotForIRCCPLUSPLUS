#define SIZEBUFFER 1024
#define MAX_RECCONECT 5

typedef __SIZE_TYPE__ size_t;
typedef enum {INFO,WARNING,ERROR,DEBUG} _type;
void applog(short _type,const char*frmt,...);
long FindWhere(const char*buffer,const char*string);
size_t _strlen(const char*str);
char * _copy_string(const char*str);
void debug_on(int i);
long paramsComand(char*buffer,char ch);
unsigned long CountChar(char*buffer,char ch);
//char * _strtok(char*buffer,const char *what);
char * _strdup(char*buffer);
#pragma once
typedef const char* constchr ;
