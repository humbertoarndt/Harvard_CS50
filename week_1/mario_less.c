#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i;
    int sig;
    int dots;
    int height;
    int width;

    i = 0;
    width = 1;
    sig = 0;
    while (sig == 0)
    {
        height = get_int("Height: ");
        if (height >= 1 && height <= 8)
            sig = 1;
    }
    dots = height - 1;
    while (height--)
    {
        while (dots-- != 0)
            printf(" ");
        while (i++ < width)
            printf("#");
        i = 0;
        width++;
        dots = height - 1;
        printf("\n");
    }
    return (0);
}
