#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXCHAR 500

typedef struct Movie Movie;
struct Movie
{
    char* title;
    int year;
    char * genre;
    int castSize;
    char** actors;
    struct Movie * next_movie;
};

char *dupstring(char *org)
{
    int org_size;
    static char *dup;
    char *dup_offset;

    /* Allocate memory for duplicate */
    org_size = strlen(org);
    dup = (char *)malloc(sizeof(char)*org_size+1);
    if( dup == NULL)
        return( (char *)NULL);

    /* Copy string */
    dup_offset = dup;
    while(*org)
    {
        *dup_offset = *org;
        dup_offset++;
        org++;
    }
    *dup_offset = '\0';

    return(dup);
}

Movie * create_movie_entry( char* title, int year, char * genre, int castSize, char** actors){
    Movie * new_movie = (Movie *)malloc(sizeof(Movie));
    new_movie->title = dupstring(title);
    new_movie->year = year;
    new_movie->genre = dupstring(genre);
    new_movie->castSize = castSize;
    new_movie->actors = actors;
    new_movie->next_movie = NULL;
    return new_movie;
}
struct Movie * find_tail_MovieList(struct Movie * head){
    Movie * tmp_head = head;
    while(tmp_head->next_movie != NULL)
        tmp_head = tmp_head->next_movie;
    return tmp_head;
}

char * remove_first_and_last_char(char * token)
{
    char * token_helper = token + 1;
    token_helper[strlen(token_helper) - 1] = '\0';
    return token_helper;
}

void get_actors_array(char * token,char ** actors)
{
    char * token_helper = remove_first_and_last_char(token);
    int index = 0;
    char * actor = strtok(token_helper, ",");

    while( actor != NULL ) 
    {
        actors[index] = dupstring(actor);
        actor = strtok(NULL, ",");
        ++index;
    }

    free(actor);
}

void remove_newline(char * path)
{
    path[strcspn(path, "\n")] = 0;
}

void print_movie_list(struct Movie * head){
    Movie * tmp_head = head;
    int i;

    while(tmp_head != NULL)
    {
        printf("Title: %s ", tmp_head->title);
        printf("Year: %d ", tmp_head->year);
        printf("Genre: %s ", tmp_head->genre);
        printf("CastSize: %d ", tmp_head->castSize);
        printf("Actors: [ ");
        for (i = 0; i < tmp_head->castSize; i++)
            printf("%s ", tmp_head->actors[i]);
        printf("]\n");
        tmp_head = tmp_head->next_movie;
    }
}

void init_movie_database_list(FILE* stream, struct Movie * head)
{
    char * movie;
    size_t bufsize = MAXCHAR;
    Movie * tail = NULL;
    Movie * helper;
    char * title;
    char * genre;
    int year,cast_size;
    char ** actors;
    int flag;
    helper = malloc(sizeof(struct Movie));
    movie = (char *)malloc(bufsize * sizeof(char));

    getline(&movie, &bufsize, stream);

    while ( 1 )
    {
        flag = getline(&movie, &bufsize, stream);

        if(flag == -1)
            break;
        else if(flag == 1)
            continue;

        title = strtok(movie, ",");
        year = atoi(strtok(NULL, ","));
        genre = strtok(NULL, ",");
        cast_size = atoi(strtok(NULL, ","));
        actors = (char **)malloc(cast_size * sizeof(char *));
        get_actors_array(strtok(NULL, "\n"), actors);

        if(tail == NULL)
        {
            *head = *(create_movie_entry(title, year, genre, cast_size, actors));
            tail = head;
        }
        else
        {
            helper = malloc(sizeof(struct Movie));
            *helper = *(create_movie_entry(title, year, genre, cast_size, actors));
            tail->next_movie = helper;
            tail = helper;
        }
    }
}

void read_input_file(char * path, struct Movie * head)
{
    FILE* stream;
    stream = fopen(path, "r");
    if (!stream)
    {
        fprintf(stderr, "Error opening file '%s'\n", path);
        exit(-1);
    }
    init_movie_database_list(stream, head);
}

void export_MovieList_to_file(char * token, struct Movie * head)
{
    FILE *fp;
    Movie * current;
    int i;
    fp = fopen(token, "w+");
    fprintf(fp,"Title,Year,Genre,CastSize,Actors\n");
    current = head;
    while (current != NULL)
    {
        fprintf(fp,"%s,%d,%s,%d,[", 
        current->title, 
        current->year, 
        current->genre,
        current->castSize);
        for (i = 0; i < current->castSize - 1; ++i)
            fprintf(fp,"%s,", current->actors[i]);

        fprintf(fp,"%s", current->actors[current->castSize - 1]);
        fprintf(fp,"]\n");

        current = current->next_movie;
    }
    fclose(fp);
}

void find_movie_in_list_and_remove(struct Movie * head, char * title)
{
    Movie * current = head;
    Movie * prev_current = head;
    int i;
    while (current != NULL)
    {
        if(!strcmp(current->title,title))
        {
            prev_current ->next_movie = current->next_movie;

            free(current->title);
            free(current->genre);
            for (i = 0; i < current->castSize; i++) {
                free(current->actors[i]);
            }

            if(current == head)
                *head = *head->next_movie;
            else
                free(current); 

            break;
        }
        prev_current = current;
        current = current->next_movie;
    }
}

void find_movie_in_list_and_update(struct Movie * head, char * title, char * field, char * value)
{
    Movie * current = head;
    Movie * prev_current = head;
    int i;
    while (current != NULL)
    {
        if(!strcmp(current->title,title))
        {
            if(!strcmp(field,"year"))
                current->year = atoi(value);
            else if(!strcmp(field,"genre"))
            {
                free(current->genre);
                current->genre = dupstring(remove_first_and_last_char(value));
            }
            else if(!strcmp(field,"actors"))
            {
                char ** actors;
                int cast_size;

                for (i = 0; i < current->castSize; i++)
                    free(current->actors[i]);
                free(current->actors);

                cast_size = 0;
                for(i = 0; i < strlen(value); ++i) 
                {  
                    if(value[i] == ',')  
                        ++cast_size;
                }
                ++cast_size;
                actors = (char **)malloc(cast_size * sizeof(char *));

                get_actors_array(value, actors);
                current->castSize = cast_size;
                current->actors = actors;
            }
            break;
        }
        current = current->next_movie;
    }
}
