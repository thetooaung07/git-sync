#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void printPlayerChoice(int *array, char currPlayer, int startIndex,
                       int endIndex, int A2, int B2, int Atotal, int Btotal);

typedef enum Choice
{
    left,
    right,
    left2,
    right2,
    leftRight,
    undefined
} Choice;

typedef struct Result
{
    int Atotal;
    int Btotal;
    Choice choice;
} Result;

typedef struct ScoreResult
{
    int scoreA;
    int scoreB;
    int diff;
} ScoreResult;

void addToScoreResult(ScoreResult *sr, int scoreA, int scoreB, char currPlayer)
{

    sr->scoreA = scoreA;
    sr->scoreB = scoreB;
    if (currPlayer == 'A')
        sr->diff = scoreA - scoreB;
    else if (currPlayer == 'B')
        sr->diff = scoreB - scoreA;
}

Result computeBestMove(int *array, char currPlayer, int startIndex,
                       int endIndex, int A2, int B2)
{
    Result result, leftRes, rightRes, left2Res, right2Res, leftRightRes;
    ScoreResult leftSrRes, rightSrRes, left2SrRes, right2SrRes, leftRightSrRes;

    if (endIndex == startIndex)
    {
        if (currPlayer == 'A')
        {
            result.Atotal = array[endIndex];
            result.Btotal = 0;
        }
        else if (currPlayer == 'B')
        {
            result.Btotal = array[endIndex];
            result.Atotal = 0;
        }
        result.choice = left;

        return result;
    }

    if (endIndex < startIndex)
    {
        result.Atotal = 0;
        result.Btotal = 0;
        result.choice = undefined;
        return result;
    }

    if (currPlayer == 'A')
    {
        leftRes = computeBestMove(array, 'B', startIndex + 1, endIndex,
                                  1, B2);
        addToScoreResult(&leftSrRes, leftRes.Atotal + array[startIndex], leftRes.Btotal, currPlayer);

        rightRes = computeBestMove(array, 'B', startIndex, endIndex - 1,
                                   1, B2);
        addToScoreResult(&rightSrRes, rightRes.Atotal + array[endIndex], rightRes.Btotal, currPlayer);

        if (!A2)
        {
            if (rightSrRes.diff <= leftSrRes.diff)
            {
                leftRes.Atotal = leftSrRes.scoreA;
                leftRes.Btotal = leftSrRes.scoreB;
                leftRes.choice = left;
                return leftRes;
            }
            else
            {
                rightRes.Atotal = rightSrRes.scoreA;
                rightRes.Btotal = rightSrRes.scoreB;
                rightRes.choice = right;
                return rightRes;
            }
        }

        if (A2)
        {
            left2Res = computeBestMove(array, 'B', startIndex + 2, endIndex, 0, B2);
            addToScoreResult(&left2SrRes, left2Res.Atotal + array[startIndex] + array[startIndex + 1], left2Res.Btotal, currPlayer);

            right2Res = computeBestMove(array, 'B', startIndex, endIndex - 2, 0, B2);

            addToScoreResult(&right2SrRes, right2Res.Atotal + array[endIndex] + array[endIndex - 1], right2Res.Btotal, currPlayer);

            leftRightRes = computeBestMove(array, 'B', startIndex + 1, endIndex - 1, 0, B2);

            addToScoreResult(&leftRightSrRes, leftRightRes.Atotal + array[startIndex] + array[endIndex], leftRightRes.Btotal, currPlayer);

            int maxVal = leftSrRes.diff;

            if (rightSrRes.diff > maxVal)
                maxVal = rightSrRes.diff;

            if (left2SrRes.diff > maxVal)
                maxVal = left2SrRes.diff;

            if (right2SrRes.diff > maxVal)
                maxVal = right2SrRes.diff;

            if (leftRightSrRes.diff > maxVal)
                maxVal = leftRightSrRes.diff;

            if (maxVal == leftSrRes.diff)
            {
                leftRes.Atotal = leftSrRes.scoreA;
                leftRes.Btotal = leftSrRes.scoreB;
                leftRes.choice = left;
                return leftRes;
            }
            else if (maxVal == left2SrRes.diff)
            {
                left2Res.Atotal = left2SrRes.scoreA;
                left2Res.Btotal = left2SrRes.scoreB;
                left2Res.choice = left2;
                return left2Res;
            }
            else if (maxVal == leftRightSrRes.diff)
            {
                leftRightRes.Atotal = leftRightSrRes.scoreA;
                leftRightRes.Btotal = leftRightSrRes.scoreB;
                leftRightRes.choice = leftRight;
                return leftRightRes;
            }
            else if (maxVal == rightSrRes.diff)
            {
                rightRes.Atotal = rightSrRes.scoreA;
                rightRes.Btotal = rightSrRes.scoreB;
                rightRes.choice = right;
                return rightRes;
            }
            else if (maxVal == right2SrRes.diff)
            {
                right2Res.Atotal = right2SrRes.scoreA;
                right2Res.Btotal = right2SrRes.scoreB;
                right2Res.choice = right2;
                return right2Res;
            }
        }
    }

    else if (currPlayer == 'B')
    {
        leftRes = computeBestMove(array, 'A', startIndex + 1, endIndex,
                                  A2, 1);
        addToScoreResult(&leftSrRes, leftRes.Atotal, leftRes.Btotal + array[startIndex], currPlayer);

        rightRes = computeBestMove(array, 'A', startIndex, endIndex - 1,
                                   A2, 1);
        addToScoreResult(&rightSrRes, rightRes.Atotal, rightRes.Btotal + array[endIndex], currPlayer);

        if (!B2)
        {
            if (rightSrRes.diff <= leftSrRes.diff)
            {
                leftRes.Atotal = leftSrRes.scoreA;
                leftRes.Btotal = leftSrRes.scoreB;
                leftRes.choice = left;
                return leftRes;
            }
            else
            {
                rightRes.Atotal = rightSrRes.scoreA;
                rightRes.Btotal = rightSrRes.scoreB;
                rightRes.choice = right;
                return rightRes;
            }
        }

        if (B2)
        {
            left2Res = computeBestMove(array, 'A', startIndex + 2, endIndex, A2, 0);

            addToScoreResult(&left2SrRes, left2Res.Atotal, left2Res.Btotal + array[startIndex] + array[startIndex + 1], currPlayer);

            right2Res = computeBestMove(array, 'A', startIndex, endIndex - 2, A2, 0);

            addToScoreResult(&right2SrRes, right2Res.Atotal, right2Res.Btotal + array[endIndex] + array[endIndex - 1], currPlayer);

            leftRightRes = computeBestMove(array, 'A', startIndex + 1, endIndex - 1, A2, 0);

            addToScoreResult(&leftRightSrRes, leftRightRes.Atotal, leftRightRes.Btotal + array[startIndex] + array[endIndex], currPlayer);

            int maxVal = leftSrRes.diff;

            if (rightSrRes.diff > maxVal)
                maxVal = rightSrRes.diff;

            if (left2SrRes.diff > maxVal)
                maxVal = left2SrRes.diff;

            if (right2SrRes.diff > maxVal)
                maxVal = right2SrRes.diff;

            if (leftRightSrRes.diff > maxVal)
                maxVal = leftRightSrRes.diff;

            if (maxVal == leftSrRes.diff)
            {
                leftRes.Atotal = leftSrRes.scoreA;
                leftRes.Btotal = leftSrRes.scoreB;
                leftRes.choice = left;
                return leftRes;
            }
            else if (maxVal == left2SrRes.diff)
            {
                left2Res.Atotal = left2SrRes.scoreA;
                left2Res.Btotal = left2SrRes.scoreB;
                left2Res.choice = left2;
                return left2Res;
            }
            else if (maxVal == leftRightSrRes.diff)
            {
                leftRightRes.Atotal = leftRightSrRes.scoreA;
                leftRightRes.Btotal = leftRightSrRes.scoreB;
                leftRightRes.choice = leftRight;
                return leftRightRes;
            }
            else if (maxVal == rightSrRes.diff)
            {
                rightRes.Atotal = rightSrRes.scoreA;
                rightRes.Btotal = rightSrRes.scoreB;
                rightRes.choice = right;
                return rightRes;
            }
            else if (maxVal == right2SrRes.diff)
            {
                right2Res.Atotal = right2SrRes.scoreA;
                right2Res.Btotal = right2SrRes.scoreB;
                right2Res.choice = right2;
                return right2Res;
            }
        }
    }

    return result;
}

void printLeft(int *array, char currPlayer, int startIndex, int endIndex, int A2, int B2, int Atotal, int Btotal)
{

    printf("%c [%d]: %d\n", currPlayer, startIndex, array[startIndex]);

    char nextPlayer = (currPlayer == 'A') ? 'B' : 'A';
    int nextStartIndex = startIndex + 1;
    int nextA2 = (currPlayer == 'A') ? 1 : A2;
    int nextB2 = (currPlayer == 'B') ? 1 : B2;
    int nextAtotal = (currPlayer == 'A') ? (Atotal + array[startIndex]) : Atotal;
    int nextBtotal = (currPlayer == 'B') ? (Btotal + array[startIndex]) : Btotal;

    printPlayerChoice(array, nextPlayer, nextStartIndex, endIndex, nextA2, nextB2, nextAtotal, nextBtotal);
}

void printLeft2(int *array, char currPlayer, int startIndex, int endIndex, int A2, int B2, int Atotal, int Btotal)
{

    printf("%c [%d], [%d]: %d + %d\n", currPlayer, startIndex, startIndex + 1, array[startIndex], array[startIndex + 1]);

    char nextPlayer = (currPlayer == 'A') ? 'B' : 'A';
    int nextStartIndex = startIndex + 2;
    int nextA2 = (currPlayer == 'A') ? 0 : A2;
    int nextB2 = (currPlayer == 'B') ? 0 : B2;
    int nextAtotal = (currPlayer == 'A') ? (Atotal + array[startIndex] + array[startIndex + 1]) : Atotal;
    int nextBtotal = (currPlayer == 'B') ? (Btotal + array[startIndex] + array[startIndex + 1]) : Btotal;

    printPlayerChoice(array, nextPlayer, nextStartIndex, endIndex, nextA2, nextB2, nextAtotal, nextBtotal);
}
void printLeftRight(int *array, char currPlayer, int startIndex, int endIndex, int A2, int B2, int Atotal, int Btotal)
{
    printf("%c [%d], [%d]: %d + %d\n", currPlayer, startIndex, endIndex, array[startIndex], array[endIndex]);
    char nextPlayer = (currPlayer == 'A') ? 'B' : 'A';
    int nextStartIndex = startIndex + 1;
    int nextEndIndex = endIndex - 1;
    int nextA2 = (currPlayer == 'A') ? 0 : A2;
    int nextB2 = (currPlayer == 'B') ? 0 : B2;
    int nextAtotal = (currPlayer == 'A') ? (Atotal + array[startIndex] + array[endIndex]) : Atotal;
    int nextBtotal = (currPlayer == 'B') ? (Btotal + array[startIndex] + array[endIndex]) : Btotal;

    printPlayerChoice(array, nextPlayer, nextStartIndex, nextEndIndex, nextA2, nextB2, nextAtotal, nextBtotal);
}

void printRight(int *array, char currPlayer, int startIndex, int endIndex, int A2, int B2, int Atotal, int Btotal)
{
    printf("%c [%d]: %d\n", currPlayer, endIndex, array[endIndex]);
    char nextPlayer = (currPlayer == 'A') ? 'B' : 'A';
    int nextStartIndex = startIndex;
    int nextEndIndex = endIndex - 1;
    int nextA2 = (currPlayer == 'A') ? 1 : A2;
    int nextB2 = (currPlayer == 'B') ? 1 : B2;
    int nextAtotal = (currPlayer == 'A') ? (Atotal + array[endIndex]) : Atotal;
    int nextBtotal = (currPlayer == 'B') ? (Btotal + array[endIndex]) : Btotal;

    printPlayerChoice(array, nextPlayer, nextStartIndex, nextEndIndex, nextA2, nextB2, nextAtotal, nextBtotal);
}

void printRight2(int *array, char currPlayer, int startIndex, int endIndex, int A2, int B2, int Atotal, int Btotal)
{
    printf("%c [%d], [%d]: %d + %d\n", currPlayer, endIndex, endIndex - 1, array[endIndex], array[endIndex - 1]);
    char nextPlayer = (currPlayer == 'A') ? 'B' : 'A';
    int nextStartIndex = startIndex;
    int nextEndIndex = endIndex - 2;
    int nextA2 = (currPlayer == 'A') ? 0 : A2;
    int nextB2 = (currPlayer == 'B') ? 0 : B2;
    int nextAtotal = (currPlayer == 'A') ? (Atotal + array[endIndex] + array[endIndex - 1]) : Atotal;
    int nextBtotal = (currPlayer == 'B') ? (Btotal + array[endIndex] + array[endIndex - 1]) : Btotal;

    printPlayerChoice(array, nextPlayer, nextStartIndex, nextEndIndex, nextA2, nextB2, nextAtotal, nextBtotal);
}

void printPlayerChoice(int *array, char currPlayer, int startIndex,
                       int endIndex, int A2, int B2, int Atotal, int Btotal)
{

    if (endIndex < startIndex)
    {
        printf("A: %d, B: %d\n", Atotal, Btotal);
        return;
    }

    Result result = computeBestMove(array, currPlayer, startIndex,
                                    endIndex, A2, B2);

    switch (result.choice)
    {
    case left:
        printLeft(array, currPlayer, startIndex, endIndex, A2, B2, Atotal, Btotal);
        break;
    case left2:
        printLeft2(array, currPlayer, startIndex, endIndex, A2, B2, Atotal, Btotal);
        break;
    case leftRight:
        printLeftRight(array, currPlayer, startIndex, endIndex, A2, B2, Atotal, Btotal);
        break;
    case right:
        printRight(array, currPlayer, startIndex, endIndex, A2, B2, Atotal, Btotal);
        break;
    case right2:
        printRight2(array, currPlayer, startIndex, endIndex, A2, B2, Atotal, Btotal);
        break;
    case undefined:
        break;
    }
}

int main()
{
    int inputArr[100];
    int tokenCount = 0;
    int num = 0;

    printf("Tokens:\n");

    while (scanf(" %d", &num) == 1)
    {
        inputArr[tokenCount] = num;
        tokenCount++;
        if (tokenCount > 100)
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

    if (tokenCount == 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    printPlayerChoice(inputArr, 'A', 0, tokenCount - 1, 1, 1, 0, 0);

    return 0;
}
