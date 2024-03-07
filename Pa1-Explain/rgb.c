#include <stdio.h>

int main()
{
    char input[100];
    int r, g, b;
    char format[4];

    printf("Type color in RGB format:\n");

    if (scanf(" %3s ( %d , %d , %d )", format, &r, &g, &b) == 4 && format[0] == 'r' && format[1] == 'g' && format[2] == 'b')
    {
        if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
        {
            printf("#%02X%02X%02X\n", r, g, b);
        }
        else
        {
            printf("Invalid input.\n");
        }
    }
    else
    {
        printf("Invalid input.\n");
    }

    return 0;
}
