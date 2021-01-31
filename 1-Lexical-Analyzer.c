#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

struct symbolTable
{
  char symbol[30];
  char type[30];
  int attribute;
}table[50]; // Symbol table structure

int isKeyword(char buffer[]); // Check if buffer is keyword
int isOperator(char ch); // Check if character is operator
int isString(char ch); // Check if character is string
int isDelimeter(char ch); // Check if character is delimiter
int isConstant(char buffer[]); // Check if buffer is constant
int isIdentifier(char buffer[]); // Check if buffer is valid identifier

void parse(char str[]); // Parse the strings to find lexical tokens
void insertSymbol(char symbol[], char type[]); // Insert into symbol table
void displayTable(); // Display symbol table

char str[50], string[50], buffer[30];
char ch;
int n=0;

int main(void) 
{
  printf("\nEnter the program: \n");
  scanf("%[^~]%*c",str);

  printf("\nYour program: \n%s",str);
  printf("\nLexical Analyzer\n\n");

  parse(str);
  displayTable();
    
  return 0;
}

int isKeyword(char buffer[])
{
  char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","printf",
							"unsigned","void","volatile","while"};
  for(int j=0;j<32;j++)
  {
    if(strcmp(keywords[j],buffer)==0)
    {
      return 1;
      break;
    }
  }
  return 0;
}

int isOperator(char ch)
{
  char operators[] = "+-/*%=";

  for(int j=0; j<6; j++)
  {
    if(ch==operators[j])
    {
      return 1;
      break;
    }
  }
  return 0;
}

int isString(char ch)
{
  
  if(ch=='"')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int isDelimeter(char ch)
{
  char delimiters[12]=" ,;{}[]#<>()";

  for(int j=0; j<12; j++)
  {
    if(ch==delimiters[j])
    {
      return 1;
      break;
    }
  }
  return 0;
}

int isConstant(char buffer[])
{
  int flag=0;

  for(int j=0; buffer[j]!='\0'; j++)
  {
    if(!isdigit(buffer[j]))
    {
      flag=1;
      break;
    }
  }
  if(flag==1)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int isIdentifier(char buffer[])
{
  if(isConstant(&buffer[0]) || isDelimeter(buffer[0]) || buffer[0]==' ')
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

void parse(char str[])
{
  int i, k=0;
  for(i=0; str[i]!='\0'; i++) // Iterate through each character in pgm
  {

    ch=str[i];
    if(isalnum(ch))
    {
      buffer[k++]=ch;
    }
    else if(isString(ch))
    {
      int j=0;
      do
      {
        i++;
        string[j]=str[i];
        j++;
      }while(str[i]!='"');
      string[j-1]='\0';
      printf("%s is String\n",string);
      insertSymbol(string,"String");
    }
    else if(isDelimeter(ch) || isOperator(ch))
    {
      if(k!=0) //There is a string in buffer[]
      {
          buffer[k]='\0';
          k=0;
          if(isKeyword(buffer))
          {
            printf("%s is keyword\n",buffer);
            insertSymbol(buffer,"Keyword");
          }
          else if(isConstant(buffer))
          {
            printf("%s is constant\n", buffer);
            insertSymbol(buffer,"Constant");
          }
          else if(isIdentifier(buffer))
          {
            printf("%s is identifier\n", buffer);
            insertSymbol(buffer,"Identifier");
          }
      }
      if(isOperator(ch))
      {
        printf("%c is operator\n",ch);
        buffer[k]='\0'; // To print the identifier in the buffer 
        k=0;
        if(isIdentifier(buffer))
        {
          printf("%s is identifier\n", buffer);
          insertSymbol(buffer,"Identifier");
        }
      }
    }
  }
}
void insertSymbol(char symbol[], char type[])
{
  int j,flag=0;
  if(n==0)
  {
    strcpy(table[n].symbol,symbol);
    strcpy(table[n].type,type);
    table[n].attribute=n;
    n++;
  }
  else
  {
    for(j=0;j<n;j++)
    {
      if(strcmp(symbol,table[j].symbol)==0)
      {
        flag=1;
      }
    }
    if(flag==0)
    {
      strcpy(table[n].symbol,symbol);
      strcpy(table[n].type,type);
      table[n].attribute=n;
      n++;
      flag=0;
    }
  }
}

void displayTable()
{
  printf("\nSymbol-Table-->\n\nSymbol\tType\t Attribute\t Address\n______________________________________\n");
  for(int j=0;j<n;j++)
  {
    printf("%s\t %s\t id%d\t %p\n",table[j].symbol,table[j].type,table[j].attribute,table[j].symbol);
  }
}

/*
  OUTPUT


Enter the program: 
int main()
{
int a=10,b,c;
char d[10];
c=b+a+5;
printf("Hai");
return 0;
}
~

Your program: 
int main()
{
int a=10,b,c;
char d[10];
c=b+a+5;
printf("Hai");
return 0;
}

Lexical Analyzer

int is keyword
main is identifier
int is keyword
a is identifier
= is operator
10 is constant
b is identifier
c is identifier
char is keyword
d is identifier
10 is constant
c is identifier
= is operator
b is identifier
+ is operator
a is identifier
+ is operator
5 is constant
printf is keyword
Hai is String
return is keyword
0 is constant

Symbol-Table-->

Symbol  Type     Attribute   Address
______________________________________
int  Keyword     id0     0x6020c0
main     Identifier  id1     0x602100
a    Identifier  id2     0x602140
10   Constant    id3     0x602180
b    Identifier  id4     0x6021c0
c    Identifier  id5     0x602200
char     Keyword     id6     0x602240
d    Identifier  id7     0x602280
5    Constant    id8     0x6022c0
printf   Keyword     id9     0x602300
Hai  String  id10    0x602340
return   Keyword     id11    0x602380
0    Constant    id12    0x6023c0

*/