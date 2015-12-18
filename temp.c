#include <stdio.h>

int main()
{
    float num;
    int i ;
    num = 0;
    for(i = 0; i < 100; i++)
    {
        num += 0.1;
    }
    printf("%f\n", num);
    return 0;
}