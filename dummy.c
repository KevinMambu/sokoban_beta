#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

int x = 20;
int y = 20;
int i;
int j;
const char const* raw = 'O';

char **l = (char * *)malloc(sizeof(char *)*x);
for(i = 0; i < x; i += 1)
{
l[i] = (char *)malloc(sizeof(char)*y);
}

for ( i = 0 ; i < x ; i += 1 ) 
{
for ( j = 0 ; j < x ; j += 1 )
{
l[i][j] = 'X';
printf("%c", l[i][j]);
}
printf("\n");
}

strcpy(&l[2][2], raw);

for ( i = 0 ; i < x ; i += 1 ) 
{
for ( j = 0 ; j < x ; j += 1 )
{
l[i][j] = 'X';
printf("%c", l[i][j]);
}
printf("\n");
}

return EXIT_SUCCESS;
}
