#include <stdio.h>

unsigned long strlen(const char* str)
{
    int count = 0;
    for(count = 0; *str != '\0'; ++count)
        ++str;
    return count;
}

int main(int argc, char *argv[])
{   
   if(argc < 1){  
      printf("No argument passed through command line.\n");  
   }  
   else
   {
        char* input_string = argv[1];
        int i,j,k;

        char* tmp = input_string;
        int len = strlen(tmp);

        for(i = 0; i < len; ++i)
        {
           
            if(input_string[i] == ' ' && input_string[i+1] == ' ') 
            {
                printf( "%c", input_string[i]);
                for(j = i + 1; j< len; ++j)
                {
                    if(input_string[j] != ' ')
                        break;
                }
                i = j;
            }
            
            printf( "%c", input_string[i]);        
        }
        printf("\n");
    }
    return 0;
}
