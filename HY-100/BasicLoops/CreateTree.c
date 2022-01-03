#include <stdio.h>

int main(int argv, char** argc)
{
    int height_of_X         = 0;
    unsigned i              = 0;
    unsigned j              = 0;
	unsigned flag           = 0;

    scanf("%d", &height_of_X);

    if( ((height_of_X % 2) == 0) || (height_of_X < 3))
    {
        printf("Ypsos mi apodekto.\n");
        return 0;
    }

    for(i = 0; i < height_of_X; ++i)
    {
        if(i == height_of_X/2)
        {
            for(j = 0; j < height_of_X; ++j)
            {
                if(j == height_of_X/2)
                {
                    printf("*");
                    break;
                }
                else
                    printf(" ");
            }
        }
        else
        {
           for(j = 0; j < height_of_X; ++j)
            {
                if(j == i || j == (height_of_X - 1 - i))
                {
                    printf("*");
                    if(flag == 1)
                        break;
                    flag = 1;
                }
                else
                    printf(" ");
            }
        }
        flag = 0;
        printf("\n");
    }
    return 0;
}
