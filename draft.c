#include <stdio.h>
#include <strings.h>

int     _len(char **strings)
{
    int len;

    len = 0;
    while (strings[len])
        len++;
    return (len);
}

void    sort(char **strings)
{
    int     i;
    int     j;
    char    *swap;
    int     len;

    len = _len(strings);
    i = 1;
    while (i < len)
    {
        j = i;
        while (j > 0 && strcmp(strings[j-1], strings[j]) > 0)
        {
            swap = strings[j-1];
            strings[j - 1] = strings[j];
            strings[j] = swap;
            j--;
        }
        i++;
    }   
}

int main(void)
{
    char *strings[5] = {"hello", "how", "coco", "fuck", 0};
    int i;

    sort (strings);
    i = 0;
    while(strings[i])
    {
        printf("%s\n", strings[i]);
        i++;
    }
    return (0);
}