#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

int main()
{
    double x[4], y[4];
    char bracket[4];

    for (int i = 0; i < 4; i++)
    {
        printf("Point #%d:\n", i + 1);

        if (scanf(" ( %lf , %lf %c", &x[i], &y[i], &bracket[i]) != 3 || (bracket[i] != ')'))
        {
            printf("Invalid input.\n");
            return 1;
        }
    }

    double dotP1 = (x[0] - x[1]) * (x[2] - x[1]) + (y[0] - y[1]) * (y[2] - y[1]);
    double dotP2 = (x[1] - x[2]) * (x[3] - x[2]) + (y[1] - y[2]) * (y[3] - y[2]);
    double dotP3 = (x[2] - x[3]) * (x[0] - x[3]) + (y[2] - y[3]) * (y[0] - y[3]);

    if ((fabs(dotP1) <= DBL_EPSILON * 1000 * fabs((x[0] - x[1]) * (x[2] - x[1]))) && (fabs(dotP2) <= DBL_EPSILON * 1000 * fabs((x[1] - x[2]) * (x[3] - x[2]))) && (fabs(dotP3) <= DBL_EPSILON * 1000 * fabs((x[2] - x[3]) * (x[0] - x[3]))))
    {
        printf("The points form a rectangle.\n");
    }
    else
    {
        printf("The points do not form a rectangle.\n");
    }
}