#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>


// fuck 3d arrays im just going tk use a sql db. 

typedef struct {
    char *question;
    char *answer;
    int id;
}variables;

typedef struct {
    variables *row;
    int count;
    int capacity;
}result;  

int fill_db(int, char *);

int callback(void *, int, char **, char **);

int main()
{
    char *errmsg = 0;
    sqlite3 *db;

    sqlite3_stmt *stmt;

    int score = 0;
    
    int attempted = 0;
  
    char *filename = malloc(sizeof(char)); 

    result results;
    results.count = 0; 
    results.capacity = 10;
    results.row = malloc(results.capacity * sizeof(variables));

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
        free(temp);
        free(buffer);
    } while (filename == NULL); 


    printf("Please enter the number of questions\n");

    fflush;
    
    char *nq_t = 0;

    fgets(nq_t, sizeof(char), stdin);

    int nq = atoi(nq_t);

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
        fprintf(stderr, "cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    const char *create =  "CREATE TABLE IF NOT EXISTS flashcard(id INTEGER PRIMARY KEY, question TEXT, answer TEXT, review INTEGER);";
    
    rc = sqlite3_prepare_v2(db, create, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK){
        fprintf(stderr, "SQL error; %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        exit(1);
    }
    sqlite3_finalize(stmt);

    const char *SELECT = "SELECT id, question, answer FROM flashcard;";

    char buffer[256];

    char *useranswer;
    if (create == 0)
    {
        
        
        sqlite3_exec(db, SELECT, callback, &results, &errmsg);
        
        for ( int i = 0; i < nq; i++)
        {
            printf("%s\n", results.row[i].question);
            printf("please enter the answer\n");

            fgets(buffer, sizeof(buffer), stdin);

            useranswer = malloc(strlen(buffer) + 1);
            strcpy(useranswer, buffer);

           

            if (strcmp(useranswer, results.row[i].answer) == 0)
            {
                printf("Correct!\n");
                score++;
                attempted++;
            }
            else
            {
                printf("Incorrect! The correct answer is: %s\n", results.row[i].answer);
                attempted++;
                sqlite3_prepare_v2(db, "UPDATE flashcard SET review = review + 1 WHERE id = ?;", -1, &stmt, NULL);
                sqlite3_bind_int(stmt, 1, results.row[i].id);
                rc = sqlite3_step(stmt);
                if (rc != SQLITE_DONE) 
                {
                fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                exit(1);
                }
                rc = sqlite3_finalize(stmt);
                if (rc != SQLITE_OK) 
                {
                fprintf(stderr, "Failed to finalize statement: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                exit(1);
                }

            }

        free(useranswer);
        }
    }
    free(filename);
    free(choice);
    free(results.row);
    free(nq_t);
    sqlite3_close(db);
    return(0);
}

int callback(void *data, int argc, char **argv, char **azColName)
{
    result *row = (result *)data;

    if (row->count >= row->capacity)
    {
        row->capacity *= 2;
        row->row = realloc(row->row, row->capacity * sizeof(variables));
    }
    
    variables *var = &row->row[row->count++];
    var->id = 0;
    var->question = NULL;
    var->answer = NULL;

    if (argv == NULL)
    {
        printf("No results found. Please choose a file with a wordlist included or you can create your own\n");
        return 0;
    }
    else
    {
        
        for (int i = 0; i < argc; i++)
        {
            if (strcmp(azColName[i], "question") == 0)
            {
                var->question = malloc(strlen(argv[i]) + 1); 
                strcpy(var->question, argv[i]);   
            }
            else if (strcmp(azColName[i], "answer") == 0)
            {
            var->answer = malloc(strlen(argv[i]) + 1);    
            strcpy(var->answer, argv[i]);
            }
            else if (strcmp(azColName[i], "id") == 0)
            {
                var->id = atoi(argv[i]);
            }
        }    // checks the column names and assigns the values to the variables in the struct
        
            
        
        // plan is to add this all into a struct and then return it and either evaluate the data in the main function or create its own function*/ 
    }
    free(var->question);
    free(var->answer);
 return 0;   
}

int fill_db(int nq, char *filename)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *errmsg = 0;
    int added = 0;
    
    int rc = sqlite3_open("flashcard.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    const char *insert = "INSERT INTO flashcard(question, answer, review) VALUES(?, ?, 0);";
    do{
        int added = 0;
        char *question = malloc(sizeof(char) * 256);
        char *answer = malloc(sizeof(char) * 256);
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
    question = realloc(question, strlen(question) - 1);
    printf("\n");
    printf("Please enter the answer\n");
    fgets(answer, sizeof(answer), stdin);
    answer = realloc(answer, strlen(answer) - 1);
    printf("\n");

    sqlite3_bind_text(stmt, 1, question, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, answer, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    free(question);
    free(answer);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_finalize(stmt);
    printf("Question and answer added successfully.\n");
    added++;
    } while (added < nq);

    sqlite3_close(db);
    
    free(errmsg);
    return 0;
}
