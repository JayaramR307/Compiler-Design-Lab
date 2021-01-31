// First and Follow

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int checkNonTerminals(char nonTerminal);
void first(char[],char );
void follow(char[],char );
void addToResultSet(char[],char);

int numOfProductions, numofNonTerminals=0;
char productionSet[10][10], nonTerminals[20];
int main()

{
    int i, j;
    char choice;
    char c;
    char First[20], Follow[20];
    printf("How many number of productions ? :");
    scanf(" %d",&numOfProductions);
    for(i=0;i<numOfProductions;i++)//read production string eg: E=E+T
    {
        scanf(" %s",productionSet[i]);
        if(isalpha(productionSet[i][0]) && checkNonTerminals(productionSet[i][0]))
        {
          nonTerminals[numofNonTerminals++]=productionSet[i][0];
        }

    }
    
    for(j=0;j<numofNonTerminals;j++)
    {
        first(First,nonTerminals[j]); //Compute FIRST; Get Answer in 'result' array
        printf("\n FIRST(%c)= { ",nonTerminals[j]);
        for(i=0;First[i]!='\0';i++)
        {
          printf(" %c ,",First[i]);       //Display result
        }
        printf("}\n");
    }
    printf("\n\n");

    for(j=0;j<numofNonTerminals;j++)
    {
        follow(Follow,nonTerminals[j]); //Compute FIRST; Get Answer in 'result' array
        printf("\n FOLLOW(%c)= { ",nonTerminals[j]);
        for(i=0;Follow[i]!='\0';i++)
        {
          printf(" %c ,",Follow[i]);       //Display result
        }
        printf("}\n");
    }

}

int checkNonTerminals(char nonTerminal)
{
  for(int i=0; i<numofNonTerminals; i++)
  {
    if(nonTerminals[i]==nonTerminal)
    {
      return 0;
    }
  }
  return 1;
}

/*
 *Function FIRST:
 *Compute the elements in FIRST(c) and write them
 *in Result Array.
 */
void first(char* Result,char c)
{
    int i,j,k;
    char subResult[20];
    int foundEpsilon;
    subResult[0]='\0';
    Result[0]='\0';
    //If X is terminal, FIRST(X) = {X}.
    if(!(isupper(c)))
    {
        addToResultSet(Result,c);
               return ;
    }
    //If X is non terminal
    //Read each production
    for(i=0;i<numOfProductions;i++)
    {
//Find production with X as LHS
        if(productionSet[i][0]==c)
        {
//If X ? ? is a production, then add ? to FIRST(X).
 if(productionSet[i][2]=='#') addToResultSet(Result,'#');
            //If X is a non-terminal, and X ? Y1 Y2 … Yk
            //is a production, then add a to FIRST(X)
            //if for some i, a is in FIRST(Yi),
            //and ? is in all of FIRST(Y1), …, FIRST(Yi-1).
      else
            {
                j=2;
                while(productionSet[i][j]!='\0')
                {
                foundEpsilon=0;
                first(subResult,productionSet[i][j]);
                for(k=0;subResult[k]!='\0';k++)
                    addToResultSet(Result,subResult[k]);
                 for(k=0;subResult[k]!='\0';k++)
                     if(subResult[k]=='#')
                     {
                         foundEpsilon=1;
                         break;
                     }
                 //No ? found, no need to check next element
                 if(!foundEpsilon)
                     break;
                 j++;
                }
            }
    }
}
    return ;
}
void follow(char* Result, char c)
{
  int i, j;
  Result[0]='\0';

  if(productionSet[0][0]==c)
  {
    addToResultSet(Result, '$' );
  }
  for(i=0; i<numOfProductions; i++)
  {
    for(j=2; j<strlen(productionSet[i]); j++)
    {
      if(productionSet[i][j]==c)
      {
        if(productionSet[i][j+1]!='\0')
        {
          first(Result, productionSet[i][j+1]);
        }
        if(productionSet[i][j+1]=='\0' && c!=productionSet[i][0])
        {
          follow(Result, productionSet[i][0]);
        }
      }
    }
  }
}

/* addToResultSet adds the computed
 *element to result set.
 *This code avoids multiple inclusion of elements
  */
void addToResultSet(char Result[],char val)
{
    int k;
    for(k=0 ;Result[k]!='\0';k++)
        if(Result[k]==val)
            return;
    Result[k]=val;
    Result[k+1]='\0';
}

/*
(1)
S=ABCDE
A=a
A=#
B=b
B=#
C=c
D=d
D=#
E=e
E=#
(2)
E=TA
A=+iA
A=#
T=i
*/

/*

How many number of productions ? :4 
E=TA
A=+iA
A=#
T=i

 FIRST(E)= {  i ,}

 FIRST(A)= {  + , # ,}

 FIRST(T)= {  i ,}



 FOLLOW(E)= {  $ ,}

 FOLLOW(A)= {  $ ,}

 FOLLOW(T)= {  + , # ,}

*/