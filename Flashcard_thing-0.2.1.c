#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stqlite3.h>


// fuck 3d arrays im just going tk use a sql db. 



int main()
{

    sqlite3 *db;

    sqlite3_stmt *stmt;

    int score = 0;
    
    int attempted = 0;
  
    char *filename = malloc(sizeof(char)); 

    // declaring variables 

    printf("Welcome to flashcard thing\n");
    
    // determines the name of the database
    
    printf("Please enter the file name in the format name.db\n");
    
    do{
        char *temp = malloc(sizeof(char) * 3);

        char *buffer = malloc(sizeof(char) * 3);
        
        // allocating sizes of memory equal to the size of a char + 3 bytes 
      
        do{
            fgets(buffer, sizeof(buffer), stdin);
          
          // reads from standard input and enters the values into the variable buffer
          
            strcat(temp, buffer);

            if (strchr(buffer, '\n') != NULL)
            {
                buffer = realloc(buffer, sizeof(temp) + 2);
                temp = realloc(temp, sizeof(buffer) + 2);
                strcpy(buffer, temp);
                // checks if a new line character is in the input       
            }


        } while( strchr(buffer, '\n') == NULL);
    
        buffer[strlen(buffer) -1] = '\0';
    
        filename = realloc(filename, sizeof(buffer));
        // once the newline charachter is found it removes one bit if memory and replaces it with a null terminator
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

    // sqlite db stuff here 

    int rc = sqlite3_open(filename, &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "cannot open database: %s\n", sqlite3_errmsg(open_db));
        exit(1);
    }
    test = sqlite3_prepare_v2(filename, "SELECT question FROM flashcards WHERE id = ?", -1, &test_stmt, NULL);
    if (test != SQLITE_OK){
        fprintf(stderr, "SQL error; %s\n", sqlite3_errmsg(db));
        test = sqlite3_prepare_v2(filename, "SELECT question FROM flashcards WHERE id = ?", -1, &test_stmt, NULL);
        sqlite3_close(db);
        exit(1);
    }
    sqlite3_bind_int(test_stmt, 1, )

    do{

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

sqlite3_open(const char *filename, sqlite3 **ppDb)