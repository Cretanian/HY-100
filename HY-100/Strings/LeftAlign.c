#include <stdio.h>
#include <stdlib.h>

unsigned long strlen(const char* str)
{
    int count = 0;
    for(count = 0; *str != '\0'; ++count)
        ++str;
    return count;
}

void remove_starting_whitespaces(int* pointer_to_string,int* count_of_chars, char* input_string)
{
    while(input_string[*pointer_to_string] == ' ')
    {        
        ++(*pointer_to_string);
        if(count_of_chars != NULL)
            --(*count_of_chars);
    }
}

void print(int SPstart, int SPend, int STstart, int STend, char* string)
{
    int j = 0;
    for(j = SPstart; j < SPend; ++j)
        printf(" ");  

    for(j = STstart; j <= STend; ++j)
        printf("%c", string[j]);

    printf("\n");
}

int find_char_before_space(int pointer_to_string, char* input_string)
{
    int position = pointer_to_string;
    while(input_string[position] == ' ')
        --position;

    return position;
}

int find_space_before_char(int pointer_to_string, char* input_string)
{
    int position = pointer_to_string;
    while(input_string[position] != ' ' )
        --position;

    return position;
}

void recursion(int* count_of_chars, int* pointer_to_string, int N, char* input_string)
{
    if(*count_of_chars <= 0)
        return;
    else if(*count_of_chars <= N)
    {
        print(0, N - *count_of_chars, *pointer_to_string, *pointer_to_string + *count_of_chars -1, input_string);
        pointer_to_string = NULL;
        count_of_chars = NULL;
        return;
    }

    if(input_string[*pointer_to_string - 1 + N] != ' ')
    {
        if(input_string[*pointer_to_string + N] != ' ')
        {

            int space_position = find_space_before_char(*pointer_to_string - 1 + N, input_string);
            int char_position = find_char_before_space(space_position, input_string);
            int numOfwhiteSpaces = N - (char_position - *pointer_to_string) - 1;

            print(0, numOfwhiteSpaces, *pointer_to_string, char_position, input_string);
            *count_of_chars -= char_position - *pointer_to_string + 1;
            *pointer_to_string += char_position - *pointer_to_string + 1;
            remove_starting_whitespaces(pointer_to_string, count_of_chars, input_string);  

        }
        else
        {
            
            print(0, -1, *pointer_to_string, *pointer_to_string - 1 + N, input_string);
            *count_of_chars -= N + 1;
            *pointer_to_string += N + 1;
        }
    }
    else
    {
        int char_position = find_char_before_space(*pointer_to_string + N - 1, input_string);
        int numOfwhiteSpaces = *pointer_to_string + N - char_position - 1;
        print(0, numOfwhiteSpaces, *pointer_to_string, char_position, input_string);
        *count_of_chars -= char_position - *pointer_to_string + 1;
        *pointer_to_string += char_position - *pointer_to_string + 1;
        remove_starting_whitespaces(pointer_to_string, count_of_chars, input_string);  
    }
   recursion(count_of_chars, pointer_to_string, N, input_string);  
}

int main(int argc, char *argv[])
{
   if(argc < 1)
      printf("No argument passed through command line.\n");   
   else
   {
        int N = atoi(argv[1]);
        char *input_string = argv[2];
        int len = strlen(argv[2]);
        int i = 0;

        int count_of_chars_sentence = 0;
        int tmp_count_of_chars_sentence = 0;
        int pointer_to_input_string = 0;
        int tmp_pointer_to_input_string = 0;

        while(1)
        {
            if(i >= len - 1)
                break;

            pointer_to_input_string += count_of_chars_sentence;
            count_of_chars_sentence = 1;

            remove_starting_whitespaces(&pointer_to_input_string, NULL, input_string);
            for(i = pointer_to_input_string; i < len; ++i)
            {
                if(input_string[i] == '.')
                    break;
                ++count_of_chars_sentence;
            }

            if(count_of_chars_sentence > N)
            {
                tmp_count_of_chars_sentence = count_of_chars_sentence;
                tmp_pointer_to_input_string = pointer_to_input_string;
                recursion(&tmp_count_of_chars_sentence, &tmp_pointer_to_input_string, N, input_string);
            }
            else
                print(0, N - count_of_chars_sentence, pointer_to_input_string, pointer_to_input_string + count_of_chars_sentence - 1, input_string);
        }
   }
    return 0;
}
