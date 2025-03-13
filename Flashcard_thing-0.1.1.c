#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int q = 0;
int a = 0;
int ua = 0;
char question[q];
char answr[a]; 
char usransw[ua];
int i = 0; //Preserves the variable i so it can be used throughout the code. 
int score = 0;
int numquestions;
char filename[64];

// takes questions from file
char getinpt(FILE *file)
{

    char fout;
    do {
        do {
        fgets(fout, 1, file);

            if ( q == 0)
            {
                q = strlen(fout);
                question = malloc(sizof(fout));
            }
            else if (a == 0)
            {
                a = strlen(fout);
                answr = malloc(sizof(fout));
            }


                  
        } while( fout != '\n' || fout != EOF);
        
        if(i % 2)
        {
            a = strlen(fout);
            answr =realloc(answr, sizof(a));
            answr = fout;
            
        } 
        else
        {
            q = strlen(fout);
            question = realloc(question, sizeof(fout+q));
            question = fout; 
            
        }
        i++;
    } while(i <= numquestions);
   return 1;
}

// give questions to user

// if true mark as learned

// else mark as needing review 

int main()
{
    printf("welcome to Flashcard Thing\n");
    printf("How many questions would you like to answer?\n");
    scanf("%d", &numquestions);
    printf("Enter the name of the file for questions\n");
    scanf("%s", &filename);
    FILE *file = fopen( filename, "r");
   
   if (file == NULL) 
   {
    perror("FILE does not exist"); 
    exit (27); 
   } 
    while (i < numquestions)
    {
    getinpt(file);

    printf("question: %s", question);

    strcmp(question, answr);

    switch(strcmp(question, answr))
    {
        case 0:
            ua = strlen(answr);
            usransw = malloc(sizeof(ua));
            break;
        case >0:
            ua = strlen(question);
            usransw = malloc(sizeof(ua));
            break;
        case <0:
            ua = strlen(answr);
            usransw = malloc(sizeof(ua));
            break; 
    }

    scanf("%s", &usransw);
    

    if (strcmp(answr, usransw) == 0)
    {
        printf("Correct\n");
        score++; 
    }
    else
    {
        printf("Incorrect\n");
        // mark as incorrect somehow       
        printf("answer: %s", answr);
        score--;
    }
    if (score == numquestions )
    {
        printf("Congratulations on finishing you scored: %d out of %d", score, numquestions);
        printf("Would you like to play again? (y/n)\n");
        char playagain[2];
        scanf("%c", &playagain);
        if ((playagain == "y"))
        {
            score = 0;
        }
        else
        {
            return 1; 
        }        
    }
    }
}
