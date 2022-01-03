#include <stdio.h>
#include <assert.h>
#include <string.h>


int main(int argv, char** argc)
{
    int N                   = 0;
    unsigned K              = 0;
    unsigned i              = 0;
    int helper                   = 0;
    char messege[100];

    scanf("%d ", &N);
    scanf("%d ", &K);
    scanf("%99[^\n]%*c", messege);

    assert("Wrong input!" && (K == 0 || K == 1));
    
    N = N%26;
    if(N == 0)
        printf("%s\n", messege);

    if(K == 1)
        N = N * (-1);

    for(i = 0; i < strlen(messege); ++i)
    {
        if(!(64 < (int) messege[i] && (int) messege[i] < 91))
            continue;
            
        helper = (int) messege[i] + N;

        if(helper > 90)
            helper = (helper % 90) + 64;
        else if(helper < 65)
            helper = 91 - (65 - helper);

        messege[i] = (char) helper;
        
        if(strlen(messege) == i)
            break;
        
    }

    printf("%s\n",messege);

    return 0;

}
