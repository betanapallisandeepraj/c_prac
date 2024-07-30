#include <stdio.h>
void fun(char *str)
{
    if((str[0]>=48) && (str[0]<=57))
        printf("number\n");
    else
        printf("not number\n");
}
int main()
{
    char buffer[10] = "version";
    fun(buffer);
    return 0;
}