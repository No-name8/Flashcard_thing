#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stqlite3.h>


// fuck 3d arrays im just going tk use a sql db. 

char fill_db(int, char);

int test_stmt(void *, int, char **, char **);

int callback(void *, int, char **, char **);

int main()
{
    char *errmsg = 0;
    sqlite3 *db;

    sqlite3_stmt *stmt;

    int score = 0;
    
    int attempted = 0;
  
    char *filename = malloc(sizeof(char)); 

    // declaring variables 

    printf("Welcome to flashcard thing\n");
    char *choice = malloc(sizeof(char) * 10);
    // determines the name of the database
    printf("If you already have a db then please enter Y if not enter N");
    fgets(choice, sizeof(choice), stdin);
    
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


    printf("Please enter the number of questions\n");

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
        filename = "flashcard.db";
        printf("No file name provided, using default: flashcard.db\n");
    }

    if (choice[0] == 'Y' || choice[0] == 'y')
    {
        printf("Using existing database: %s\n", filename);
    }
    else if (choice[0] == 'N' || choice[0] == 'n')
    {
        printf("Creating new database: %s\n", filename);
        fill_db(nq, filename);
    }
    else
    {
        fprintf(stderr, "Invalid choice. Please enter Y or N.\n");
        exit(1);
    }
    // should check if file is working 

    // sqlite db stuff here 

    int rc = sqlite3_open(filename, &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "cannot open database: %s\n", sqlite3_errmsg(open_db));
        exit(1);
    }
    const char *create =  "CREATE TABLE IF NOT EXISTS flashcard(id INTEGER PRIMARY KEY, question TEXT, answer TEXT, review INTEGER);"
    
    rc = sqlite3_exec(db, create, check_stmt, NULL, NULL);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error; %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    const char *SELECT = "SElECT id, question, answer FROM flashcard;";

    if (create == 0)
    {
        sqlite3_exec(db, SELECT, callback, (void *) nq, &errmsg);
    }

    

    sqlite3_prepare_v2(db, insert, -1, &stmt, NULL);
    printf("Please enter the question\n");
    

    return(0);
}

int test_stmt(void *notused, int argc, char **argv, char **azColName)
{
    if ( argv == NULL )
    {
        printf("No results found. Please choose a file with a wordlist included or you can create your own\n");
        return nmbc;
    }
    else 
    {
        for (int i = 0; i < argc; i++)
        {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
    }

    printf("\n");
    return 0;
}

int callback(void *nq, int argc, char **argv, char **azColName)
{
    char questions[];
    char useranswer[];
    char answers[];
    int attempted = 0;
     
    if (argv == NULL)
    {
        printf("No results found. Please choose a file with a wordlist included or you can create your own\n");
        return 0;
    }
    else
    {
        do {
        for (int j = 0; j < argc; j++)
        {
                
            /* questions = argv[i];
            answers = argv[j+1];
            printf("%s", questions);
            printf("please enter your answer\n");
            fgets(useranswer, sizeof(useranswer), stdin);
            if (strcmp(useranswer, answers) == 0)
            {
                printf("Correct!\n");
                score++;
            }
            else
            {   
                printf("Incorrect. The correct answer is %s\n", answers);
            } 
        attempted++ 
        }
            
        }while (nq >= attempted);
        plan is to add this all into a struct and then return it and either evaluate the data in the main function or create its own function*/ 
    }
 return score;   
}

int fill_db(int nq)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *errmsg = 0;
    
    int rc = sqlite3_open("flashcard.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    const char *insert = "INSERT INTO flashcard(question, answer, review) VALUES(?, ?, 0);"
    do{
        int added = 0;
        char question[];
        char answer[];
        // declaring variables for the question and answer

        rc = sqlite3_prepare_v2(db, insert, -1, &stmt, NULL);
        if (rc != SQLITE_OK) 
        {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }
    printf("Please enter the question\n");
    fgets(question, sizeof(question), stdin);
    printf("\n");
    printf("Please enter the answer\n");
    fgets(answer, sizeof(answer), stdin);
    printf("\n");

    sqlite3_bind_text(stmt, 1, question, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, answer, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_finalize(stmt);
    printf("Question and answer added successfully.\n");
    addded++;
    } while (added < nq);


}