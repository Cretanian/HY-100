#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

unsigned int get_number_of_digits(unsigned long long int number)
{
    unsigned int counter;
    unsigned int get_degit;

    for (counter = 0; number != 0; ++counter)
    {
        get_degit = number % 10;
        number = (number - get_degit) / 10;
    }

    return counter;
}

unsigned long long int exec_func_0(int X, int Y)
{
    if(Y <= 0)
     return 1;

    if(X <= 0)
     return Y;
    
    return (X * exec_func_0(X - 1, Y - 1)) / Y;
}

void exec_func_1(int X, int Y)
{
    unsigned int tmp_X,tmp_Y;
    unsigned long long int res  = 0;
    unsigned int space = 0;
    unsigned int helper;

    unsigned long long int max_value = exec_func_0(X, X/2);
    unsigned int max_digit = get_number_of_digits(max_value);
    if(max_digit % 2 == 0)
        ++max_digit;

    unsigned int spaces_count = (max_digit/2 + 1);

    for(tmp_X = 0; X >= tmp_X; ++tmp_X) 
    {
        for(space = 0; space < ((X * spaces_count) - (tmp_X * spaces_count) ); ++space)
                printf(" ");
        
        for(tmp_Y = 0; tmp_X >= tmp_Y; ++tmp_Y)
        {
                res = exec_func_0(tmp_X, tmp_Y);
                helper = max_digit - get_number_of_digits(res);

                for (size_t i = 0; i < helper; ++i)
                    printf("0");

                if(!(tmp_X >= tmp_Y + 1))
                    printf("%llu", res);
                else
                    printf("%llu ", res);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{   
   if(argc != 4){  
      printf("Not enought argument passed through command line.\nTerminating app\n");  
   }  
   else
   {
        int X = atoi(argv[1]);
        int Y = atoi(argv[2]);
        int MODE = atoi(argv[3]);
       
        if(!(1 <= X && X <= 64) || !(1 <= Y && Y <= X) || !(0 <= MODE && MODE <= 2))
        {
            printf("Input (%d, %d, %d) is wrong. row, col must be in 1...64, col <= row and mode 0, 1 or 2.\n", X, Y, MODE);
            return 0;
        }

        if (X - 1 < 0)
            X = 1;

        if (Y - 1 < 0)
            Y = 1;

        if(MODE == 0)
            printf("%llu\n", exec_func_0(X - 1, Y - 1));
        else if(MODE == 1)
           exec_func_1(X - 1, Y - 1);
   }
    return 0;
}
