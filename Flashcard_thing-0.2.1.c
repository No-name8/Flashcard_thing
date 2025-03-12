#include <stdio.h>
#include <string.h>

char question[64];
char answr[64]; 
char usransw[64];
int i = 0; //Preserves the variable i so it can be used throughout the code. 
int score = 0;
int numquestions;

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
    printf("welcome to Flashcard Thing\n");
    printf("How many questions would you like to answer?\n");
    scanf("%d", &numquestions);
    FILE *file = fopen("name.txt", "r");
   if ((file == NULL)) 
   {
    perror("FILE does not exist"); 
    exit (27); 
   }
    
    
        
    getinpt(file);

    printf("question: %s", question);

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
    if (score == 20)
    {
        printf("Congratulations on finishing you scored: %d out of %d", score, numquestions);
        printf("Would you like to play again? (y/n)\n");
        char playagain;
        scanf("%c", &playagain);
        if (playagain == "y")
        {
            score = 0;
        }
        else
        {
            return 0; 
        }        
    }
       
    return 1;
}
