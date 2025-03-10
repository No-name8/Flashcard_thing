#include <stdio.h>
#include <string.h>

char question[64];
char answr[64]; 
char usransw;
int i = 0; //Preserves the variable i so it can be used throughout the code. 



// takes questions from file
char getinpt(FILE *file)
{

    char fout[64];

    do {
       fgets(fout, 64, file);

        if(i % 2)
        {
        strcpy(answr, fout);
        } 
        else
        {
        strcpy(question, fout);
        }
        if (i  % 2)
        {
            i++;
            break;
        }
    i++;      
    } while( i <=20 );

   return 1;
}

// store questions and match them to answers

// give questions to user

// compare users answer to question answer

// if true mark as learned

// else mark as needing review 

int main()
{
     FILE *file = fopen("name.txt", "r");
   if ((file == NULL)) 
   {
    perror("FILE does not exist"); 
    return 1;
   }
    while (1)
    {
        
    getinpt(file);

    printf("question: %s", question);

    printf("answer: %s", answr);

    }
    
    return 1;
}