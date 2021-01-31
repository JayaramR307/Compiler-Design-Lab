#include <stdio.h>
#include <string.h>

char stack[20], input[20], table[10][10], terminals[10], ch;
int n, top = 0, col, row;

void initializeNull(); // To initialze stack, input, table as null
void readOperatorTable(); // To read operator table
void displayTable(); // To display operator table
void parse(); // To parse input string

int main()
{
  initializeNull();
  printf("Enter the no.of terminals: ");
  scanf("%d", &n);
  printf("\nEnter the terminals: ");
  scanf("%s%c", terminals,&ch);
  readOperatorTable();
  displayTable();
  printf("\n\nEnter the input string (put $ at the end): ");
  scanf("%s", input);
  parse();
  printf("\n");

  return 0;
}

void initializeNull()
{
  int i, j;

  for (i = 0; i < 10; i++)
  {
    stack[i] = '\0';
    input[i] = '\0';
    for (j = 0; j < 10; j++)
    {
      table[i][j] = '\0';
    }
  }
}

void readOperatorTable()
{
  int i, j;

  printf("\nEnter the table values (<, >, =, A):\n");
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      printf("Enter the value for %c %c: ", terminals[i], terminals[j]);
      scanf("%c%c", &table[i][j],&ch);
    }
  }
}

void displayTable()
{
  int i, j;
  printf("\nOPERATOR PRECEDENCE TABLE:\n");
  for (i = 0; i < n; i++)
  {
    printf("\t%c", terminals[i]);
  }
  printf("\n");
  for (i = 0; i < n; i++)
  {
    printf("\n%c", terminals[i]);
    for (j = 0; j < n; j++)
    {
      printf("\t%c", table[i][j]);
    }
  }
}

void parse()
{
  int i, j, k;

  stack[top] = '$';
  printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n");
  printf("\n%s\t\t\t%s\t\t\t", stack, input);

  i = 0;
  while (i <= strlen(input))
  {
    for (k = 0; k < n; k++)
    {
      if (stack[top] == terminals[k]) //Find row no. of element in stack top
      {
        row = k;
      }
      if (input[i] == terminals[k]) //Find col no. of element in stack top
      {
        col = k;
      }
    }
    if ((stack[top] == '$') && (input[i] == '$')) // If $ $, then accept
    {
      printf("String is accepted");
      break;
    }
    else if ((table[row][col] == '<') || (table[row][col] == '=')) // if stack vs input is <=, then push 
    {
      stack[++top] = input[i];
      printf("Shift %c", input[i]);
      i++;
    }
    else
    {
      if (table[row][col] == '>') // if stack vs input is >, then pop 
      {
        top = top - 1;
        printf("Reduce");
      }
      else // Otherwise reject
      {
        printf("\nString is not accepted");
        break;
      }
    }
    printf("\n");
    for (k = 0; k <= top; k++)
    {
      printf("%c", stack[k]);
    }
    printf("\t\t\t");
    for (k = i; k < strlen(input); k++)
    {
      printf("%c", input[k]);
    }
    printf("\t\t\t");
  }
}
/*

Enter the no.of terminals:4

Enter the terminals:+*i$

Enter the table values (<, >, =, A):
Enter the value for + +:>
Enter the value for + *:<
Enter the value for + i:<
Enter the value for + $:>
Enter the value for * +:>
Enter the value for * *:>
Enter the value for * i:<
Enter the value for * $:>
Enter the value for i +:>
Enter the value for i *:>
Enter the value for i i:=
Enter the value for i $:>
Enter the value for $ +:<
Enter the value for $ *:<
Enter the value for $ i:<
Enter the value for $ $:A

OPERATOR PRECEDENCE TABLE:
    +   *   i   $

+   >   <   <   >
*   >   >   <   >
i   >   >   =   >
$   <   <   <   A

Enter the input string (put $ at the end): i+i*i$

STACK           INPUT STRING            ACTION

$           i+i*i$          Shift i
$i          +i*i$           Reduce
$           +i*i$           Shift +
$+          i*i$            Shift i
$+i         *i$         Reduce
$+          *i$         Shift *
$+*         i$          Shift i
$+*i            $           Reduce
$+*         $           Reduce
$+          $           Reduce
$           $           String is accepted

*/