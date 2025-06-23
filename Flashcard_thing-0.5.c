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


int insert_data(char *, int);

int create_table(char *);

int mark_as_learned(char *, void *);

bool check_status_of_db(char *, int);

int read_data(char *, void *);

int callback(void *, int, char **, char **);

int answer(void *, int, int, int, char *);

int main()
{
    Variables var;

    char *filename = malloc(sizeof(char) + 4);

    filename[0] = '\0';

    int score = 0;

    int attempted = 0;

    var.question = NULL;
    var.answer = NULL;
    var.count = 0;

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
            buffer[strlen(buffer) - 1] = '\0';
        }

        filename = realloc(filename, strlen(buffer) + 1);
        filename[0] = '\0';

        strcpy(filename, buffer);

        free(buffer);

    } while (filename == NULL);
    if ( strlen(filename ) <= 3)
    {
        filename = realloc(filename, 13);
        strcpy(filename, "flashcard.db");
    }


    char *tmp_nq = malloc(256);
    tmp_nq[0] = '\0';

    printf("Please enter the number of questions\n");

    fgets(tmp_nq, 256, stdin);

    int nq = atoi(tmp_nq);

    free(tmp_nq);

    if (check_status_of_db(filename, nq) == true)
    {
        answer(&var, nq, score, attempted, filename);
    }
    else
    {
        printf("Chosen database is invalid or not long enough. would you like to edit it?\n");
        char *buffer = malloc(256);
        buffer[0] = '\0';
        fgets(buffer, 256, stdin);

        if ( strchr(buffer, 'Y') || strchr(buffer, 'y'))
        {
            if (create_table(filename) == 0)
            {
            insert_data(filename, nq);
            }
        }
        else if (strchr(buffer,'N') || strchr(buffer,'n'))
        {
            printf("Quiting");

            exit(0);
        }

        free(buffer);
    }
    if(check_status_of_db(filename, nq) == true)
    {
        for ( int i = 0; i < nq; i++){
        answer(&var, nq, score, attempted, filename);
        }
    }

    free(filename);

    return 1;
}

bool check_status_of_db(char *filename, int nq)
{
    sqlite3 *db;

    sqlite3_stmt *stmt;

    int rc;

    rc = sqlite3_open(filename, &db); // 848 bytes in 1 blocks are definitely lost in loss record 228 of 228

    if ( rc != SQLITE_OK)
    {
        fprintf(stderr, "ERROR 142: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        return false;
    }
    else
    {
        const char *last = "SELECT id FROM flashcard";


        rc = sqlite3_prepare_v2(db, last, -1, &stmt, NULL);

        if (rc != SQLITE_OK)
        {
           // fprintf(stderr, "ERROR: %s", sqlite3_errmsg(db));
            sqlite3_close(db);
            return false;
        }

        rc = sqlite3_step(stmt);

        if ( rc <= nq )
        {
            rc = sqlite3_finalize(stmt);

            return false;
        }
        else
        {
            rc = sqlite3_finalize(stmt);

            return true;
        }

        sqlite3_close(db);

    }

    sqlite3_close(db);
    return false;
}

int read_data(char *filename, void *structs )
{
    sqlite3 *db;

    sqlite3_stmt *stmt;

    Variables *var = (Variables *) structs;

    int rc;

    rc = sqlite3_open(filename, &db);

    if (rc != SQLITE_OK )
    {
        fprintf(stderr, "ERROR 200: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit(311);
    }
    const char *read = "SELECT id, question, answer FROM flashcard LIMIT 1;";

    rc = sqlite3_prepare_v2(db, read, -1, &stmt, NULL);

    if ( rc != SQLITE_OK )
    {
        fprintf(stderr, "ERROR 212: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit(321);
    }

    rc = sqlite3_step(stmt);

    // get col names using sql function then compare and then assign variables
    // create var like azColName
    //create var like argv
    //then compare and go from there

    if ( rc != SQLITE_OK )
    {
        fprintf(stderr, "ERROR 228: %s", sqlite3_errmsg(db)); // ERROR: another row available

        sqlite3_close(db);

        exit(331);
    }

    rc = sqlite3_close(db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "ERROR 238: %s", sqlite3_errmsg(db));
    }

    return 1;
}

int mark_as_learned(char *filename, void *data)
{
    sqlite3 *db;

    sqlite3_stmt *stmt;

    Variables *var = (Variables *) data;

    const char *mark = "UPDATE flashcard SET review = review + 1 WHERE id = ?";

    int rc;

    rc = sqlite3_open(filename, &db);

    if ( rc != SQLITE_OK )
    {
        fprintf(stderr, "ERROR 258: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit(312);
    }

    sqlite3_prepare_v2(db, mark, -1, &stmt, NULL);

    if ( rc != SQLITE_OK)
    {
        fprintf(stderr, "ERROR 271: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit(322);
    }

    sqlite3_bind_int(stmt, 1, var->id);

    rc = sqlite3_step(stmt);

    if ( rc != SQLITE_OK )
    {
        fprintf(stderr, "ERROR 284: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit(332);
    }

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return 1;
}

int create_table(char *filename)
{
    sqlite3 *db;

    sqlite3_stmt *stmt;

    int rc = sqlite3_open(filename, &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "ERROR 308: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit (313);

    }

    const char *create = "CREATE TABLE IF NOT EXISTS flashcard(id INT PRIMARY KEY, question TEXT, answer TEXT, review INT)";

    rc = sqlite3_prepare_v2(db, create, -1, &stmt, NULL);
    if ( rc != SQLITE_OK )
    {
        fprintf(stderr, "ERROR 321: %s", sqlite3_errmsg(db));
        sqlite3_close(db);

        exit(323);
    }

    rc = sqlite3_step(stmt);

    if ( rc != SQLITE_OK )
    {
        fprintf(stderr, "ERROR 331: %s", sqlite3_errmsg(db)); // ERROR 331: no more rows available

        sqlite3_close(db);

        exit(333);
    }
    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return 0;
}

int answer(void *data, int nq, int score, int attempted, char *filename)
{

    Variables *var = (Variables *) data;

    char *useranswer = malloc(256);

    while (attempted < nq)
    {

    read_data(filename, &var);

    printf("%s", var->question); // Use of uninitialised value of size 8 // Invalid read of size 1

    fgets(useranswer, 256, stdin);

        useranswer[strcspn(useranswer, "\n")] = '\0';

    if (strcmp(useranswer, var->answer) == 0) // Invalid read of size 1
    {
        printf("\nCorrect\n");
        mark_as_learned(filename, &var);

        score++;

    }
    else
    {
    printf("Incorrect\n");

    printf("Correct answer was: %s", var->answer);


    }
    attempted++;
    }
    free(useranswer);
    return score;
}

int insert_data(char *filename, int nq)
{
    sqlite3 *db;

    sqlite3_stmt *stmt;

    int rc = sqlite3_open(filename, &db);

    int id = 1;

    char *answer = malloc(256);

    char *question = malloc(256);

    answer[0] = '\0';

    question[0] = '\0';

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "ERROR 358: %s", sqlite3_errmsg(db));

        exit(314);
    }
    do
    {
        const char *insert = "INSERT INTO flashcard( id, answer, question, review) VALUES(?, ?, ?, 0)";

        rc = sqlite3_prepare_v2(db, insert, -1, &stmt, NULL);

        if ( rc != SQLITE_OK)
        {
            fprintf(stderr, "ERROR 416 %d: %s", id, sqlite3_errmsg(db));

            sqlite3_close(db);

            exit(324);
        }

        sqlite3_bind_int(stmt, 1, id);

        printf("please enter the question\n");

        fgets(question, 256, stdin);

        question[strlen(question) - 1] = '\0';

        printf("please enter the answer\n");

        fgets(answer, 256, stdin);

        answer[strlen(answer) - 1] = '\0';

        sqlite3_bind_text(stmt, 2, answer, -1, SQLITE_STATIC);

        sqlite3_bind_text(stmt, 3, question, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);

        if ( rc != SQLITE_OK )
        {
            fprintf(stderr, "ERROR 445 %d: %s", id, sqlite3_errmsg(db));

            sqlite3_close(db);

            exit(334);
        }
        sqlite3_reset(stmt);

        id++;
    } while (nq >= id);

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    free(answer);
    free(question);

    return 1;
}