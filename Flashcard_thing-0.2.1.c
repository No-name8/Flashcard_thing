#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// fuck 3d arrays im just going tk use a sql db. 

int main()
{
    int score = 0;
    
    int attempted = 0;
  
    char *filename = malloc(sizeof(char)); 


    printf("Welcome to flashcard thing\n");
    
    do{
        char *temp = malloc(sizeof(char) * 3);

        char *buffer = malloc(sizeof(char) * 3);

        do{
            fgets(buffer, sizeof(buffer), stdin);

            strcat(temp, buffer);

            if (strchr(buffer, '\n') != NULL)
            {
                buffer = realloc(buffer, sizeof(temp) +2);
                temp = realloc(temp, sizeof(buffer) + 2);
                strcpy(buffer, temp);        
            }


        } while( strchr(buffer, '\n') == NULL);
    
    buffer[strlen(buffer) -1] = '\0';
    
    filename = realloc(filename, sizeof(buffer));
    
    strcpy(filename, buffer);
    } while (filename == NULL); 


    printf("Please enter the number of questions you would like to answer\n");

    fflush;
    
    int nq = 0;

    fgets(nq, sizeof(nq), stdin);

    if(nq <= 1)
    {
        perror("Invalid input");
        exit;
    }

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
    if ( file == NULL )
    {
      perror("file does not exist");
      exit(0);
    } // should check if file is working 
    
    int increment = 0;

    do
    {
    char *buffer = malloc (sizeof(char) *3);
    char *temp = malloc(sizeof(buffer) * 2);

    fgets(buffer, sizeof(buffer), file); // not working for some reason
// not getting any values odds are its a result of something wrong eith *file
        if (strchr(buffer, '\n') == NULL)
        {
            strcat(temp, buffer);

            buffer = realloc(buffer, sizeof(buffer) + 2);

            strcpy(buffer, temp); 
        }
        else 
        {
            buffer[strlen(buffer) - 1] = '\0'; 

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

    bool *review = malloc(sizeof(bool) * 2);

    for (int i = 0; i <= nq; i++)
    {
        review[i] = malloc(sizeof(bool) * 2);
    }

    do{
        int min = 0;
        unsigned int i = rand() <= nq; 
        int j = 0;
        char *useranswer = malloc(sizeof(char) * 3);

        char *buffer = malloc(sizeof(char) * 3);

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