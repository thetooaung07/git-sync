#include <stdio.h>

int possibleChange(int xArvTime, int xDepTime, int yArvTime, int yDepTime)
{
    if (yArvTime - xArvTime <= 3 * 60 && yDepTime - xArvTime >= 5)
        return 1;

    return -1;
}

int main()
{

    int aAHour, aAMinute, aDHour, aDMinute;
    int bAHour, bAMinute, bDHour, bDMinute;
    int cAHour, cAMinute, cDHour, cDMinute;

    printf("Train A arrival time:\n");
    if (scanf("%d:%d", &aAHour, &aAMinute) != 2 || aAMinute >= 60 || aAMinute < 0 || aAHour < 0 || aAHour >= 24)
    {
        printf("Invalid input.\n");
        return 0;
    }

    printf("Train A departure time:\n");
    if (scanf("%d:%d", &aDHour, &aDMinute) != 2 || aDMinute >= 60 || aDMinute < 0 || aDHour < 0 || aDHour >= 24)
    {
        printf("Invalid input.\n");
        return 0;
    }

    printf("Train B arrival time:\n");
    if (scanf("%d:%d", &bAHour, &bAMinute) != 2 || bAMinute >= 60 || bAMinute < 0 || bAHour < 0 || bAHour >= 24)
    {
        printf("Invalid input.\n");
        return 0;
    }

    printf("Train B departure time:\n");
    if (scanf("%d:%d", &bDHour, &bDMinute) != 2 || bDMinute >= 60 || bDMinute < 0 || bDHour < 0 || bDHour >= 24)
    {
        printf("Invalid input.\n");
        return 0;
    }

    printf("Train C arrival time:\n");
    if (scanf("%d:%d", &cAHour, &cAMinute) != 2 || cAMinute >= 60 || cAMinute < 0 || cAHour < 0 || cAHour >= 24)
    {
        printf("Invalid input.\n");
        return 0;
    }

    printf("Train C departure time:\n");
    if (scanf("%d:%d", &cDHour, &cDMinute) != 2 || cDMinute >= 60 || cDMinute < 0 || cDHour < 0 || cDHour >= 24)
    {
        printf("Invalid input.\n");
        return 0;
    }

    int flag = 0;
    if ((aAHour >= 22 || bAHour >= 22 || cAHour >= 22 || aDHour >= 22 || bDHour >= 22 || cDHour >= 22) &&
        (aAHour <= 2 || bAHour <= 2 || cAHour <= 2 || aDHour <= 2 || bDHour <= 2 || cDHour <= 2))
    {
        flag = 1;
    }

    if (flag == 1)
    {
        if (aAHour <= 2)
            aAHour += 24;
        if (bAHour <= 2)
            bAHour += 24;
        if (cAHour <= 2)
            cAHour += 24;
        if (aDHour <= 2)
            aDHour += 24;
        if (bDHour <= 2)
            bDHour += 24;
        if (cDHour <= 2)
            cDHour += 24;
    }

    int trainADepTime = aDHour * 60 + aDMinute;
    int trainAArrivalTime = aAHour * 60 + aAMinute;

    int trainBDepTime = bDHour * 60 + bDMinute;
    int trainBArrivalTime = bAHour * 60 + bAMinute;

    int trainCDepTime = cDHour * 60 + cDMinute;
    int trainCArrivalTime = cAHour * 60 + cAMinute;

    int fromAtoB = possibleChange(trainAArrivalTime, trainADepTime, trainBArrivalTime, trainBDepTime);
    int fromAtoC = possibleChange(trainAArrivalTime, trainADepTime, trainCArrivalTime, trainCDepTime);

    if (fromAtoB == 1 && fromAtoC == 1)
        printf("Can change to both B and C from A.\n");
    else if (fromAtoB == 1 && fromAtoC == -1)
        printf("Can change to B from A.\n");
    else if (fromAtoB == -1 && fromAtoC == 1)
        printf("Can change to C from A.\n");
    else
    {
        printf("No changes available from train A.\n");
    }

    int fromBtoA = possibleChange(trainBArrivalTime, trainBDepTime, trainAArrivalTime, trainADepTime);
    int fromBtoC = possibleChange(trainBArrivalTime, trainBDepTime, trainCArrivalTime, trainCDepTime);

    if (fromBtoA == 1 && fromBtoC == 1)
        printf("Can change to both A and C from B.\n");
    else if (fromBtoA == 1 && fromBtoC == -1)
        printf("Can change to A from B.\n");
    else if (fromBtoA == -1 && fromBtoC == 1)
        printf("Can change to C from B.\n");
    else
    {
        printf("No changes available from train B.\n");
    }

    int fromCtoA = possibleChange(trainCArrivalTime, trainCDepTime, trainAArrivalTime, trainADepTime);

    int fromCtoB = possibleChange(trainCArrivalTime, trainCDepTime, trainBArrivalTime, trainBDepTime);

    if (fromCtoA == 1 && fromCtoB == 1)
        printf("Can change to both A and B from C.\n");
    else if (fromCtoA == 1 && fromCtoB == -1)
        printf("Can change to A from C.\n");
    else if (fromCtoA == -1 && fromCtoB == 1)
        printf("Can change to B from C.\n");
    else
    {
        printf("No changes available from train C.\n");
    }

    return 0;
}