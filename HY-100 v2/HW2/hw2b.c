#include <stdio.h>
#include <math.h>


int main(int argv, char** argc)
{
    int repetition          = 0;
    int number              = 0;
    int N                   = 0;
    unsigned i              = 0;
    unsigned sum            = 0;
    unsigned sum_helper     = 0;
    unsigned get_degit      = 0;
    
    scanf("%d", &repetition);
    if(repetition <= 0)
    {
        printf("NO");
        return 0;
    }

    for(i = 0; i < repetition; ++i)
    {
        N = 0;
        number = 0;
        scanf("%d", &number);
        scanf("%d", &N);
        if(N < 0 || number < 0)
        {
            printf("\nNO");
            continue;
        }

        sum_helper = number;
        sum = 0;

        while(sum_helper != 0)
        {
            get_degit = sum_helper % 10;
            sum_helper = (sum_helper - get_degit) / 10;
            sum += pow(get_degit, N);
        }

        if(sum == number)
            printf("\nYES");
        else
            printf("\nNO");
    }
    return 0;
}
