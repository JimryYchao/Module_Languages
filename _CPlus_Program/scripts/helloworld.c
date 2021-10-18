#include <stdio.h>

extern char* HELLO;
extern char* WORLD;
int num = 1;
char Str[10];

int main(void)
{
    extern int num;
    extern char Str[10];
    puts(HELLO);
    puts(WORLD);
    return 0;
}

