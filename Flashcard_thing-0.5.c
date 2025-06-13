#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *question;
    char *answer;
    int id;
    int count;
}Variables;

int fill_db(int, char *);

int insert_data(char *);

int create_table(char *);

int mark_as_learned(char *, void *);

bool check_status_of_db(char *, int);

int read_data(char *, void *);

int callback(void *, int, char **, char **);

int main()
{
    Variables var;

    char *filename = malloc(sizeof(char) + 4);

    filename[0] = '\0';

    int score = 0;

    int attempted = 0;

    var.question = '\0';

    printf("Welcome to Flashcard_Thing\n");

    printf("Please enter the name of your db file if you have one if not just press enter\n");

    do
    { 
    
        char *buffer = malloc(256);
        buffer[0] = '\0';

        fgets(buffer, 256, stdin);

        if (strchr(buffer, '\n') == NULL)
        {
            break;
        }
        else if (strchr(buffer, '\n') != NULL)
        {
            buffer[strlen(buffer)] = '\0';
        }

        filename = realloc(filename, strlen(buffer) + 1);

        strcpy(filename, buffer);

        free(buffer);

    } while (filename == NULL);
    
    if ( strlen(filename ) <= 2)
    {
        filename = realloc(filename, 11);
        filename = "Flashcard.db";
    }
    else
    {
    FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("File does not exist. \r Using default name 'flashcards.db'\n");
        }

        fclose(file);
    }

    char *tmp_nq = malloc(256);

    printf("Please enter the number of questions\n");

    fgets(tmp_nq, 256, stdin);

    int nq = atoi(tmp_nq);

    free(tmp_nq);

    char *useranswer = malloc(256);

    if (check_status_of_db(filename, nq) == true)
    {
        read_data(filename, &var); 
                                        // these errrors only come about if nq exceeds the total number of values in the db i think
        printf("%s", var.question); // Conditional jump or move depends on uninitialised value(s)

        fgets(useranswer, 256, stdin);

        if (strcmp(useranswer, var.answer) == 0) // Use of uninitialised value of size 8
        // Invalid read of size 1 
        //  Access not within mapped region at address 0x0 (SIGSEGV)
        {
            printf("\nCorrect\n");

            mark_as_learned(filename, &var);

            score++;

        }
        else
        {
            printf("Incorrect\n");

            printf("Correct answer was: %s", var.answer);

            attempted++;
        }  
    }



    free(useranswer);
    free(filename);
    return 1;
}

bool check_status_of_db(char *filename, int nq)
{
    sqlite3 *db;

    int rc;

    rc = sqlite3_open(filename, &db);

    if ( rc != SQLITE_OK)
    {
        fprintf(stderr, "ERROR: %s", sqlite3_errmsg(db));

        sqlite3_close(db); 

        return false;
    }
    else
    {
        int last = sqlite3_last_insert_rowid(db); 

        if ( last < nq )
        {
            return false;
        }
        else 
        {
            return true;
        }
    }


    sqlite3_close(db);
    return false;
}

int read_data(char *filename, void *structs )
{
    sqlite3 *db;  

    char *errmsg;

    Variables *var = (Variables *) structs;
    
    int rc;

    rc = sqlite3_open(filename, &db);

    if (rc != SQLITE_OK )
    {
        fprintf(stderr, "ERROR: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit(1);
    }
    const char *read = "SELECT id, question, answer FROM flashcard";

    int exec;

    exec = sqlite3_exec(db, read, callback, &var, &errmsg);

    if ( exec != SQLITE_OK )
    {
        fprintf(stderr, "ERROR: %s", errmsg);

        sqlite3_close(db); 

        exit(1);
    }

    sqlite3_close(db);

    return 1; 
}

int mark_as_learned(char *filename, void *data)
{
    sqlite3 *db; 

    sqlite3_stmt *stmt;

    Variables *var = (Variables *) data;
    
    const char *mark = "UPDATE flashcard SET review + 1 WHERE id = ?"; 

    sqlite3_open(filename, &db);

    sqlite3_prepare_v2(db, mark, -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, var->id);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return 1; 
}

int callback(void *data, int argc, char **argv, char **azColName)
{
    Variables *var = (Variables *) data;

    var->count = 0;

    if (strcmp(azColName[var->count], "id") == 0)
    {
        var->id = atoi(argv[var->count]);
        var->count++;   
    }
    else if (strcmp(azColName[var->count], "answer") == 0)
    {
        var->answer = malloc(strlen(argv[var->count]) + 1);
        strcpy(var->answer, argv[var->count]);
        var->count++;
    }
    else if (strcmp(azColName[var->count], "question") == 0)
    {
        var->question = malloc(strlen(argv[var->count]) + 1);
        strcpy(var->question, argv[var->count]);
        var->count++;
    }
    
    return 0;
}

