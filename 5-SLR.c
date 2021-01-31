// SLR

/*
E->E+T | T
T->id
*/

#include<stdio.h>
#include<string.h>

int actionTable[6][3][2] = 
{
          /*  +       i         $     */
/* 0 */  { {-1,-1}, {100,3}, {-1,-1} },
/* 1 */  { {100,4}, {-1,-1}, {102,102} },
/* 2 */  { {101,2}, {-1,-1}, {101,2} },
/* 3 */  { {101,3}, {-1,-1}, {101,3} },
/* 4 */  { {-1,-1}, {100,3}, {-1,-1} },
/* 5 */  { {101,1}, {-1,-1}, {101,1} }
};
int goTo[6][2] =
{
      /* E  T */ 
/* 0 */  1, 2,
/* 1 */ -1, -1,
/* 2 */ -1, -1,
/* 3 */ -1, -1,
/* 4 */ -1, 5,
/* 5 */ -1,  -1
};
int states[20], stateTop=-1, inputTop=-1;
char inputStack[20], input[20]="\0";

void pushState(int stateNum); // To push state num to stack
void pushInput(char inputSymbol); // To push input symbol to stack
void popState(); // To pop state num from stack
void popInput(); // To pop input symbol from stack
void displayStack(); // To display stack
void displayInput(int beg); // To display input
void reduce(int productionNum); // To reduce the given production from stack

int main()
{
  int i, row, col;

  printf("\nEnter the string (add $ to the end): ");
  scanf("%s", input);
  printf("\nStack\t\tInput\n__________________________\n\n");

  pushState(0);
  displayStack();
  displayInput(0);
  for(i=0;input[i]!='\0';)
  {
    row = states[stateTop];
    switch(input[i])
    {
      case '+': col=0; break;
      case 'i': col=1; break;
      case '$': col=2; break;
      default: printf("Error!!!"); break;
    }
    //printf("\n%d  %d %d\n", row, col,actionTable[row][col][0]);
    if(actionTable[row][col][0]==100) // Shift
    {
      pushInput(input[i]);
      pushState(actionTable[row][col][1]);
      displayStack();
      i++;
      displayInput(i);
    }
    else if (actionTable[row][col][0]==101)
    {
      reduce(actionTable[row][col][1]);
      displayStack();
      displayInput(i);
    }
    else if (actionTable[row][col][1]==102)
    {
      printf("\n\nGiven string is accepted\n");
      break;
    }
    else
    {
      printf("\n\nGiven string is rejected\n");
      break;
    }
  }
  return 0;
}

void pushState(int stateNum)
{
  if(stateTop<19)
  {
    states[++stateTop]=stateNum;
  }
}

void pushInput(char inputSymbol)
{
  if(inputTop<19)
  {
    inputStack[++inputTop]=inputSymbol;
  }
}

void popState()
{
  if(stateTop>=0)
  {
    stateTop--;
  }
}

void popInput()
{
  if(inputTop>=0)
  {
    inputStack[inputTop--]='\0';
  }
}

void displayStack()
{
  int i;
  for(i=0; i<=stateTop; i++)
  {
    printf("%d%c",states[i],inputStack[i]);
  }
}

void displayInput(int beg)
{
  int i;
  printf("\t\t");
  for(i=beg; input[i]!='\0'; i++)
  {
    printf("%c",input[i]);
  }
   printf("\n");
}

void reduce(int productionNum)
{
  char src, *dest;
  int i, row, col;

  switch(productionNum)
  {
    case 1: src='E'; dest="E+T"; break;
    case 2: src='E'; dest="T"; break;
    case 3: src='T'; dest="i"; break;
    default: src='\0'; dest="\0"; break;
  }

  for(i=0; i<strlen(dest); i++)
  {
    popState();
    popInput();
  }

  pushInput(src);
  row = states[stateTop];
  switch(src)
  {
    case 'E': col=0; break;
    case 'T': col=1; break;
    default: col=-1; break;
  }
  pushState(goTo[row][col]);
}

/*

Enter the string (add $ to the end): i+i$

Stack       Input
__________________________

0       i+i$
0i3     +i$
0T2     +i$
0E1     +i$
0E1+4       i$
0E1+4i3     $
0E1+4T5     $
0E1     $


Given string is accepted

*/