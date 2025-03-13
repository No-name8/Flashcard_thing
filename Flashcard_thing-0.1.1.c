#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char *question;
char *answr; 
char *usransw;
int i = 0; //Preserves the variable i so it can be used throughout the code. 
int score = 0;
int numquestions;
char filename[20];

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
        
        
                if ( i % 2 != 0)
                {
                    question = malloc(strlen(fout) + 1);
                    strcpy(question, fout);
                }
                else 
                {
                    answr = malloc(strlen(fout) + 1);
                    strcpy(answr, fout);
                }
            }   
            } while( *fout != '\n' && *fout != EOF);
        i++; 
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
    numquestions = strtol(buffer, NULL, 10);

    while (getchar() != '\n');

    printf("Enter the name of the file for questions\n");
    scanf("%s", filename);
    filename[strcspn(filename, "\n")] = 0;
    
    FILE *file = fopen( "name.txt", "r");
   
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
                usransw = malloc(sizeof(answr));
                }    
                else if ( strcmp( answr, question) > 0)
                { 
                usransw = malloc(sizeof(question));
                }    
                else
                {
                usransw = malloc(sizeof(answr));
                }
        }
    scanf("%s", usransw);
    

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
                free(question);
                free(answr);
                free(usransw);
                fclose(file);
                return 1; 
            }        
        }
    }