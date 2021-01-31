// LL(1) Parser

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>

char productions[4][15] = {"E-> TA","A-> +iA","A-> #","T-> i"}; // Store productions
char parserTable[3][3][5]; // Stpre parser table
//char parserTable[3][3][5] = {{"TA","",""},{"","+iA","#"},{"i","",""}};
int sizeOfElement[3][3]; // Store size of table entries
int n, row, col;
char input[20], stack[20];

void displayGrammar(); // To display productions
void readParserTable(); // To read entries of parser table
void displayTable(); // To display parser table
void parse(); // To parse input string
void displayParsing(int i, int j); // To display parsing

int main()
{
  displayGrammar();
  readParserTable();
  displayTable();
  
  printf("\nEnter the input string: ");
  scanf("%s",input);

  parse();

  return 0;
}

void displayGrammar()
{
  int i;

  printf("\nGrammar: \n");
  for(i=0; i<4; i++)
  {
    printf("%s\n",productions[i]);
  }

}

void readParserTable()
{
  int i,j;
  char tableRow, tableCol;

  printf("\nEnter the elements in parsing table ('!' for Null entries): \n");
  for(i=0; i<3; i++) // row
  {
    for(j=0; j<3; j++) // column
    {
      switch(i)
      {
        case 0: tableRow='E'; break;
        case 1: tableRow='A'; break;
        case 2: tableRow='T'; break;
      }
      switch(j)
      {
        case 0: tableCol='i'; break;
        case 1: tableCol='+'; break;
        case 2: tableCol='$'; break;
      }
      printf("\nEnter RHS of production at row[%c] and column[%c]: ",tableRow,tableCol);
      scanf("%s",parserTable[i][j]);
    }
  }
}

void displayTable()
{
  int i,j;
  printf("\n\nParser table: \n \ti\t+\t$\n");
  for(i=0; i<3; i++) //row
  {
    switch(i)
    {
      case 0: printf("E\t"); break;
      case 1: printf("A\t"); break;
      case 2: printf("T\t");break;
    }
    for(j=0; j<3; j++) // column
    {
      if(parserTable[i][j][0]!='!')
      {
        printf("%s\t", parserTable[i][j]);
        sizeOfElement[i][j]=strlen(parserTable[i][j]); // Store size of entries
      }
      else
      {
        printf("  \t");
        sizeOfElement[i][j]=0;
      }
    }
    printf("\n");
  }
  
}

void parse()
{
  int TOS=0, TOI=0, k; // Top of stack & Top of input
  strcat(input, "$"); // Add $ at end of string

  n=strlen(input); 
  stack[0]='$'; stack[1]='E'; // Push $E to stack

  printf("\nStack input Production\n-----------------------\n");
  TOS=1; TOI=0;
  displayParsing(TOS, TOI);

  while(1)
  {
    if(stack[TOS]=='$' && input[TOI]=='$') // $ $ : Valid
    {
      printf("$$\nSUCCESS\n");
      break;
    }
    if(stack[TOS]==input[TOI]) // Same entries pop
    {
      TOS--; TOI++;
      
      if(stack[TOS]=='$' && input[TOI]!='$') // Invalid string
      {
        printf("ERROR-Invalid String!!!\n");
        break;
      }
      displayParsing(TOS, TOI);
    }
    else
    {
      switch(stack[TOS])
      {
        case 'E': row=0; break;
        case 'A': row=1; break;
        case 'T': row=2; break;
      }
      switch(input[TOI])
      {
        case 'i': col=0; break;
        case '+': col=1; break;
        case '$': col=2; break;
      }
      if(parserTable[row][col][0]=='!')
      {
        printf("\nERROR-No entry!!!\n");
        break;
      }
      else if(parserTable[row][col][0]=='#') // Reduce
      {
        TOS--;
        displayParsing(TOS, TOI);
      }
      else
      {
        for(k=sizeOfElement[row][col]-1; k>=0; k--)
        {
          stack[TOS]=parserTable[row][col][k];
          TOS++;
        }
        TOS--;
        displayParsing(TOS, TOI);
      }
    } 
  }
}

void displayParsing(int i, int j)
{
   int k;

  for(k=0; k<=i; k++)
  {
    printf("%c",stack[k]);
  }
  printf(" ");

  for(k=j; k<=n; k++)
  {
    printf("%c",input[k]);
  }
  printf("\n");
}

/*

Grammar: 
E-> TA
A-> +iA
A-> #
T-> i

Enter the elements in parsing table ('!' for Null entries): 

Enter RHS of production at row[E] and column[i]: TA

Enter RHS of production at row[E] and column[+]: !

Enter RHS of production at row[E] and column[$]: !

Enter RHS of production at row[A] and column[i]: !

Enter RHS of production at row[A] and column[+]: +iA

Enter RHS of production at row[A] and column[$]: #

Enter RHS of production at row[T] and column[i]: i

Enter RHS of production at row[T] and column[+]: !

Enter RHS of production at row[T] and column[$]: !


Parser table: 
    i   +   $
E   TA        
A       +iA #
T   i         

Enter the input string: i+i+i

Stack input Production
-----------------------
$E i+i+i$
$AT i+i+i$
$Ai i+i+i$
$A +i+i$
$Ai+ +i+i$
$Ai i+i$
$A +i$
$Ai+ +i$
$Ai i$
$A $
$ $
$$
SUCCESS

*/