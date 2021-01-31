// Recursive Descent Parser

#include <stdio.h>
#include <string.h>

/*
S=ABCD
A=a | #
B=b | #
C=c
D=d | #
C=c | #
E=e | #
*/

int i=0, error=0;
char input[20];

void S();
void A();
void B();
void C();
void D();
void E();


int main()
{
  printf("Enter an arithmetic expression :  ");
  scanf("%s", input);
  int length=strlen(input);
  S();
  if(strlen(input)==i && error==0)
  {
    printf("\n\nThe input string is valid\n");
  }
  else
  {
    printf("\n\nThe input string is invalid\n");
  }
  return 0;
}
void S()
{
  A();
  B();
  C();
  D();
  E();
}

void A()
{
  if(input[i]=='a')
  {
    i++;
  }
}

void B()
{
  if(input[i]=='b')
  {
    i++;
  }
}

void C()
{
  if(input[i]=='c')
  {
    i++;
  }
  else
  {
    error++;
  }
}

void D()
{
  if(input[i]=='d')
  {
    i++;
  }
}
void E()
{
  if(input[i]=='e')
  {
    i++;
  }
}