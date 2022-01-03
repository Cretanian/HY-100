#include "utils.c"

int main(int argc, char **argv){

    struct Movie * head = malloc(sizeof(struct Movie));
    char * buffer;
    size_t bufsize = MAXCHAR;
    size_t characters;
    char * token;

    head->title = NULL;
    buffer = (char *)malloc(bufsize * sizeof(char));

    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    if(argc == 3 && !strcmp(argv[1],"import"))
        read_input_file(argv[2], head);

    while( 1 )
    {
        printf("Type action:\n 1)import /path/to/file/*.csv\n 2)add $title $year $gerne $actors\n 3)remove $title\n 4)update $title $field $value\n 5)export /path/to/file/*.csv\n 6)exit\n\n Input: ");
        getline(&buffer, &bufsize, stdin);

        token = strtok(buffer, " ");
        remove_newline(token);

        if      (!strcmp(token,"import"))
        {
            token = strtok(NULL, "\n");
            read_input_file(token,head);
        }
        else if (!strcmp(token,"add"))
        {
            int i;
            char * title = strtok(NULL, "\"");
            int year = atoi(strtok(NULL, " "));
            char * genre = strtok(NULL, "\"");
            char * all_casr = strtok(NULL, "\n");
            char ** actors;
            int cast_size;

            ++all_casr; /* removing first element */
            cast_size = 0;
            for(i = 0; i < strlen(all_casr); ++i) 
            {  
                if(all_casr[i] == ',')  
                    ++cast_size;  
            }
            ++cast_size;
            actors = (char **)malloc(cast_size * sizeof(char *));

            get_actors_array(all_casr, actors);
            if(head->title != NULL)
                find_tail_MovieList(head)->next_movie = create_movie_entry(title, year, genre, cast_size, actors);
            else
                head = create_movie_entry(title, year, genre, cast_size, actors);
        }
        else if (!strcmp(token,"remove"))
        {
            token = remove_first_and_last_char(strtok(NULL, "\n"));
            find_movie_in_list_and_remove(head, token);       
        }
        else if (!strcmp(token,"update"))
        {
            char * title = strtok(NULL, "\"");
            char * field = strtok(NULL, " ");
            char * value = strtok(NULL, "\n");
            find_movie_in_list_and_update(head, title, field, value);
        }
        else if (!strcmp(token,"export"))
        {
            token = strtok(NULL, "\n");
            export_MovieList_to_file(token,head);
        }
        else if (!strcmp(token,"exit"))
            return 0;

    }
}
