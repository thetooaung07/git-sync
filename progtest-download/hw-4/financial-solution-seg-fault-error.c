#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SEQ_ARRAY_SIZE 250000

typedef struct
{
    int startIndex;
    int endIndex;
    int length;

} resultSeq;

int main()
{
    int seqInput[250000];
    int max = INT_MIN;
    int inputIndex = 0;
    int count = 0;
    resultSeq seqArray[MAX_SEQ_ARRAY_SIZE];

    printf("Values:\n");

    while (inputIndex < 250000 && scanf("%d", &seqInput[inputIndex]) == 1)
    {
        inputIndex++;

        if (inputIndex == 250000)
        {
            printf("Invalid input.\n");
            return 1;
        }
    }

    if (!feof(stdin))
    {
        printf("Invalid input.\n");
        return 1;
    }

    if (inputIndex < 2)
    {
        printf("Invalid input.\n");
        return 1;
    }

    for (int i = 0; i < inputIndex - 1; i++)
    {
        for (int j = i + 1; j < inputIndex; j++)
        {
            if (seqInput[j] >= seqInput[i])
            {
                int currentLength = j - i + 1;
                if (currentLength > max)
                {
                    count = 0;
                    max = currentLength;
                }
                if (count < MAX_SEQ_ARRAY_SIZE)
                {
                    seqArray[count].length = currentLength;
                    seqArray[count].startIndex = i;
                    seqArray[count].endIndex = j;
                    count++;
                }
                else
                {
                    printf("Invalid input.\n");
                    return 1;
                }
            }
        }
    }

    if (max == INT_MIN)
    {
        printf("Does not exist.\n");
        return 1;
    }

    int answerCount = 0;
    for (int i = 0; i < count; i++)
    {
        if (seqArray[i].length == max)
        {
            printf("%d: %d - %d\n", seqArray[i].length,
                   seqArray[i].startIndex, seqArray[i].endIndex);
            answerCount++;
        }
    }

    printf("Answers: %d\n", answerCount);
    return 0;
}
