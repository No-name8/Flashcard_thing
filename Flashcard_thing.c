#include <stdio.h>
#include <string.h>

char question[64];
char answr[64]; 
char usransw;
int i = 0; //Preserves the variable i so it can be used throughout the code. 
int score = 0;


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

// give questions to user

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

    scanf("%s", &usransw);

    if (strcomp(answr, usransw) == 0)
    {
        printf("Correct\n");
        score++; 
    }
    else
    {
        printf("Incorrect\n");
        // mark as incorrect somehow
    }

    printf("answer: %s", answr);

    }
    
    return 1;
}