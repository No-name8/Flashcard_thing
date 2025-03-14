#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char *question;
char *answr; 
char *usransw;
int i = 0; //Preserves the variable i so it can be used throughout the code. 
int score = 0;
int nq;
char filename[20];
char review[2][]

// takes questions from file
char getinpt(FILE *file)
{
    size_t buffersize = 20;
    char *fout = malloc(buffersize * sizeof(char));
do {
        if( fgets(fout, buffersize, file) != NULL) 
        {
            while (fout[strlen(fout) - 1] != '\n' && !feof(file))
            {
                buffersize *= 2;
                fout = realloc(fout, buffersize * sizeof(char));
                fgets(fout + strlen(fout), buffersize / 2, file);
            }
        
        
                if ( i % 2 )
                {
                    question = malloc(strlen(fout) + 1);
                    strcpy(question, fout);
                    i++;
                    break;
                }
                else 
                {
                    answr = malloc(strlen(fout) + 1);
                    strcpy(answr, fout);
                    i++;
                }
            }

            } while( *fout != '\n' || *fout != EOF);
        
        free(fout);   
        return 1;
    
}
// give questions to user

// if true mark as learned

// else mark as needing review 

int main()
{
    char buffer[10];

    printf("welcome to Flashcard Thing\n");
    printf("How many questions would you like to answer?\n");
    fgets(buffer, sizeof(buffer), stdin);
    nq = strtol(buffer, NULL, 10);

    int **review = malloc(sizeof(int) * 2);

`   for (int j =0; j < nq; j++)
    {
        review[j] = malloc(sizeof(int) *2);
    }

    fflush(stdin);

    printf("Enter the name of the file for questions\n");
    scanf("%s", filename);
    
    fflush(stdin);

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

        

            if ( strcmp( answr, question) < 0)
                {
                usransw = malloc(100);
                }    
                else if ( strcmp( answr, question) > 0)
                { 
                usransw = malloc(100);
                }    
                else
                {
                usransw = malloc(100);
                }

                fflush(stdin);

                printf("Please enter an answer:"); 
                fgets(usransw, strlen(answr), stdin);

                int n = 0; 

                if (usransw == NULL || usransw == "\n")
                {
                    printf("Please enter an answer:");
                    fgets(usransw, strlen(answr), stdin);
                } 
                  
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
                printf("your answer: %s", usransw);
                score--;
                }
                fflush(stdin);
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
                free(question);
                free(answr);
                free(usransw);
                fclose(file);
                return 1; 
            }        
        }
    }