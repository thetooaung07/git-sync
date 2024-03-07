#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Review
{
    int year;
    int month;
    int day;
    int rating;
    char review[4097];

} TReview;

typedef struct ReviewStats
{
    double avg;
    int median;
    double diff;
    int capacity;
    int size;
    int startIndex;
    int endIndex;

} ReviewStats;

// leapYear 1 , else 0
int isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) && year % 4000 != 0);
}

// 1 - true , 0 - false
int validateDate(const TReview tr)
{

    if (tr.year < 1800 || tr.year > 3000 ||
        tr.day < 1 || tr.day > 31 ||
        tr.month < 1 || tr.month > 12)
    {

        // printf("Initial Validation fail\n");
        return 0;
    }

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear(tr.year))
    {
        daysInMonth[2] = 29;
    }

    if (tr.day > daysInMonth[tr.month])
    {
        // printf("Day > it should be fail\n");
        return 0;
    }
    return 1;
}

double calculateAverage(TReview *tr, int startIndex, int endIndex)
{
    double sum = 0.0;

    for (int i = startIndex; i <= endIndex; i++)
    {
        sum += tr[i].rating;
        // printf("Sum %lf", sum / (endIndex - startIndex + 1) * 1.0);
    }
    return sum / (endIndex - startIndex + 1) * 1.0;
}

int compare(const int *a, const int *b)
{
    return (*a < *b) - (*b < *a);
}

int calculateMedian(TReview *tr, int startIndex, int endIndex)
{

    int trSize = endIndex - startIndex + 1;
    int temp[5000];

    int median = 0;

    for (int i = startIndex, j = 0; i <= endIndex; i++, j++)
    {
        temp[j] = tr[i].rating;
    }

    qsort(temp, trSize, sizeof(int), (int (*)(const void *, const void *))compare);

    median = temp[trSize / 2];

    // printf("Median %d", median);
    return median;
}

// same day = 0, greater = 1; less = -1
int compareDate(TReview *tr, int compareIndex)
{
    if (compareIndex > 0 && tr[compareIndex].year < tr[compareIndex - 1].year)
    {
        return -1;
    }
    else if (compareIndex > 0 && tr[compareIndex].year == tr[compareIndex - 1].year && tr[compareIndex].month < tr[compareIndex - 1].month)
    {

        return -1;
    }
    else if (compareIndex > 0 && tr[compareIndex].year == tr[compareIndex - 1].year && tr[compareIndex].month == tr[compareIndex - 1].month && tr[compareIndex].day < tr[compareIndex - 1].day)
    {

        return -1;
    }

    if (compareIndex > 0 && tr[compareIndex].year == tr[compareIndex - 1].year && tr[compareIndex].month == tr[compareIndex - 1].month && tr[compareIndex].day == tr[compareIndex - 1].day)
    {
        return 0;
    }

    return 1;
}

void groupInterval(TReview *tr, int size, ReviewStats **rs, int *rsSize, int *capacity)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (i == 0)
            {
                if (compareDate(tr, j + 1) == 0)
                {
                    continue;
                }
            }
            else if (j == size - 1)
            {
                if (compareDate(tr, i) == 0)
                {
                    continue;
                }
            }
            else if (compareDate(tr, j + 1) == 0 || compareDate(tr, i) == 0)
            {
                continue;
            }

            (*rs)[*rsSize].avg = calculateAverage(tr, i, j);
            // printf("GroupInterval %lf\n",(*)rs[*rsSize].avg);
            (*rs)[*rsSize]
                .median = calculateMedian(tr, i, j);
            // printf("GroupInterval %d\n",(*)rs[*rsSize].median);
            (*rs)[*rsSize].diff = fabs((*rs)[*rsSize].avg - (*rs)[*rsSize].median);
            (*rs)[*rsSize].startIndex = i;
            (*rs)[*rsSize].endIndex = j;
            (*rs)[*rsSize].size = j - i + 1;
            // printf("GroupInterval startIndex - %d, endIndex  - %d\n",(*)rs[*rsSize].startIndex,(*)rs[*rsSize].endIndex);
            *rsSize = *rsSize + 1;
            if (*rsSize == *capacity)
            {
                *capacity *= 2;
                *rs = (ReviewStats *)realloc(*rs, *capacity * sizeof(ReviewStats));
            }
            (*rs)[*rsSize].capacity = *capacity;
        }
    }

    // printf("rsSize = %d\n", *rsSize);
}

// max
void findMaxDiff(char operation, int interval, TReview *tr, ReviewStats *rs, int *rsSize)
{

    ReviewStats rsInit = {0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < *rsSize; i++)
    {

        // printf("All - diff - %lf   , avg-%lf , median-%d  size = %d endIndex = %d  \n\n", rs[i].diff, rs[i].avg, rs[i].median, rs[i].size, rs[i].endIndex);

        if (rs[i].size >= interval)
        {

            if (rsInit.diff < rs[i].diff)
            {
                rsInit = rs[i];
            }
            else if (rsInit.diff == rs[i].diff)
            {
                // printf("Assigned without size - diff -%lf   , avg-%lf , median-%d  size = %d endIndex = %d  \n\n", rs[i].diff, rs[i].avg, rs[i].median, rs[i].size, rs[i].endIndex);

                if (rsInit.size < rs[i].size || rsInit.endIndex < rs[i].endIndex)
                {

                    // printf("Assigned - diff -%lf   , avg-%lf , median-%d   size = %d endIndex = %d  \n\n", rs[i].diff, rs[i].avg, rs[i].median, rs[i].size, rs[i].endIndex);
                    rsInit = rs[i];
                }
            }
        }
    }

    printf("%d-%d-%d - %d-%d-%d: %lf %d\n", tr[rsInit.startIndex].year, tr[rsInit.startIndex].month, tr[rsInit.startIndex].day, tr[rsInit.endIndex].year, tr[rsInit.endIndex].month, tr[rsInit.endIndex].day, rsInit.avg, rsInit.median);

    if (operation == '?')
    {
        for (int i = rsInit.startIndex; i <= rsInit.endIndex; i++)
        {
            printf("  %d: %s\n", tr[i].rating, tr[i].review);
        }
    }
}

int main()
{
    printf("Reviews:\n");
    char operation = '\0';

    int size = 10;
    TReview *tr = (TReview *)malloc(size * sizeof(TReview));
    ReviewStats *rs = (ReviewStats *)malloc(size * sizeof(ReviewStats));
    int count = 0;
    int interval = 0;

    int rsSize = 0;
    int capacity = 100;

    while (scanf(" %c", &operation) == 1)
    {

        if (count < 1 && operation == '?')
        {
            printf("Invalid input.\n");
            free(tr);
            free(rs);
            return 0;
        }

        if (operation == '+')
        {
            if (scanf("%d-%d-%d %d %4096[^\n]", &tr[count].year, &tr[count].month, &tr[count].day, &tr[count].rating, tr[count].review) != 5 || tr[count].rating < 1)
            {

                printf("Invalid input.\n");
                free(tr);
                free(rs);
                return 0;
            }

            if (compareDate(tr, count) == -1)
            {
                printf("Invalid input.\n");
                free(tr);
                free(rs);
                return 0;
            }

            if (!validateDate(tr[count]))
            {
                printf("Invalid input.\n");
                free(tr);
                free(rs);
                return 0;
            }

            count++;

            if (count == size)
            {
                size *= 2;
                tr = (TReview *)realloc(tr, size * sizeof(TReview));
            }
        }
        else if (operation == '?' || operation == '#')
        {
            rsSize = 0;
            capacity = 10;

            if (scanf("%d", &interval) != 1 || interval < 1)
            {
                printf("Invalid input.\n");
                free(tr);
                free(rs);
                return 0;
            }
            if (interval > count)
            {
                printf("No interval.\n");
            }
            else
            {
                groupInterval(tr, count, &rs, &rsSize, &capacity);
                findMaxDiff(operation, interval, tr, rs, &rsSize);
            }
        }
    }

    if (!feof(stdin))
    {
        free(tr);
        free(rs);
        printf("Invalid input.\n");
        return 0;
    }

    free(tr);
    free(rs);

    return 0;
}
