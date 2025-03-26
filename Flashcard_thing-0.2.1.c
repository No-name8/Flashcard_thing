#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// buffer keeps values and \n so either need to empty it, limit it to a smaller scope so it can be brand new every time, or use another var in its place
// Seems to be main problem so far with the 3d array
int main()
{
    int score = 0;
    char *buffer = malloc(sizeof(char) * 3);
    int attempted = 0;
    bool *review = malloc(sizeof(bool) * 2); 
    char *temp = malloc(sizeof(buffer) + 2);

    printf("Welcome to flashcard thing\n");
    
    do{
    fgets(buffer, sizeof(buffer), stdin);

    strcat(temp, buffer);

    if (strchr(buffer, '\n') != NULL)
    {
        buffer = realloc(buffer, sizeof(temp));
        strcpy(buffer, temp);        
    }


    } while( strchr(buffer, '\n') == NULL);
    
    buffer[strlen(buffer) -1] = '\0';

    char *filename = malloc(sizeof(buffer)); 

    strcpy(filename, buffer);

    printf("Please enter the number of questions you would like to answer\n");

    fflush;

    fgets(buffer, sizeof(buffer), stdin);

    if(buffer <= 0)
    {
        perror("Invalid input");
        exit;
    }

    int nq = strtol(buffer, NULL, 10 );

    FILE *file = fopen( filename, "r");

    char ***questions = malloc(sizeof(char) * 3);

    for (int i = 0; i <= nq; i++)
    {
        questions[i] = malloc(sizeof(char) * 3);
        for (int j = 0; j <= nq; j++)
        {
            questions[i][j] = malloc(sizeof(char) * 3);
        }
    }

    if (filename == NULL)
    {
        printf("File does not exist");
        exit;
    }
    
    int increment = 0;

    do
    {
    char *temp = malloc(sizeof(buffer) * 2);

    fgets(buffer, sizeof(buffer), file); // not working for some reason

        if (strchr(buffer, '\n') == NULL)
        {
            strcat(temp, buffer);

            buffer = realloc(buffer, sizeof(buffer) + 2);

            strcpy(buffer, temp); 
        }
        else 
        {
            for (int i =0; i <= nq; i++){
                for (int j = 0; j <= 2; j++)
                {
                    for (int k = 0; k <= strlen(buffer); k++)
                    {
                        questions[i][j][k] = *buffer; // seg fault occuring after a number of iterations 
                    }
                }
            }
            increment++;
        }

    
    
    }while( increment <= nq );

    for (int i = 0; i <= nq; i++)
    {
        review[i] = malloc(sizeof(bool) * 2);
    }

    do{
    int min = 0;
    unsigned int i = rand() <= nq; 
    int j =0;
    char *useranswer = malloc(sizeof(char) * 3);

    buffer = realloc(buffer, sizeof(char) * 3);

    printf("%s", questions[i][j]);

    printf("\nplease enter an answer\n");

    do
    {
    char *temp = malloc(sizeof(buffer) * 2);

    fgets(buffer, sizeof(buffer), file);

        if (strchr(buffer, '\n') == NULL)
        {
            strcat(temp, buffer);

            buffer = realloc(buffer, sizeof(buffer) + 2);

            strcpy(buffer, temp); 
        }
        else
        {
            strcpy(useranswer, buffer); 
        }
    }while(useranswer == NULL);

    if (strcmp(useranswer, questions[i][j]) == 0)
    {
        printf("correct\n");
        score++;
    }
    else
    {
        printf("Incorrect\n");
        printf("%d", questions[i][j]);
        review[i] = true; 

    }

    i++;
    j++; 
    attempted++;
    }
    while( attempted <= nq);

    return(0);
}