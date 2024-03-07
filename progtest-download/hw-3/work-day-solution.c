#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct
{
    int m_TotalDays;
    int m_WorkDays;
} TResult;
#endif /* _PROGTEST_ */

bool isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) && (year % 4000 != 0));
}

bool isNationalHoliday(int m, int d)
{
    if (m == 1 && d == 1)
    {
        return 1;
    }
    if (m == 5 && d == 1)
    {
        return 1;
    }
    if (m == 5 && d == 8)
    {
        return 1;
    }
    if (m == 7 && d == 5)
    {
        return 1;
    }
    if (m == 7 && d == 6)
    {
        return 1;
    }
    if (m == 9 && d == 28)
    {
        return 1;
    }
    if (m == 10 && d == 28)
    {
        return 1;
    }
    if (m == 11 && d == 17)
    {
        return 1;
    }
    if (m == 12 && d == 24)
    {
        return 1;
    }
    if (m == 12 && d == 25)
    {
        return 1;
    }
    if (m == 12 && d == 26)
    {
        return 1;
    }

    return 0;
}

bool checkValidDate(int y, int m, int d)
{

    if (y < 2000 || d < 1 || d > 31 || m < 1 || m > 12)
    {
        return 0;
    }

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear(y))
    {
        daysInMonth[2] = 29;
    }

    if (d > daysInMonth[m])
    {
        return 0;
    }
    return 1;
}

int calculateDayOfWeek(int year, int month, int day)
{
    if (month < 3)
    {
        month += 12;
        year -= 1;
    }

    int remainder = 0;
    remainder = (day +
                 ((month + 1) * 13) / 5 +
                 year +
                 year / 4 -
                 year / 100 +
                 year / 400) %
                7;

    return remainder;
}

bool isWorkDay(int y, int m, int d)
{

    if (!checkValidDate(y, m, d))
    {
        return 0;
    }
    if (isNationalHoliday(m, d))
    {
        return 0;
    }

    int returnDate;
    returnDate = calculateDayOfWeek(y, m, d);

    if ((returnDate >= 2 && returnDate <= 6))
    {
        return 1;
    }

    return 0;
}

TResult countDays(int y1, int m1, int d1,
                  int y2, int m2, int d2)
{
    TResult tr;
    tr.m_TotalDays = -1;
    tr.m_WorkDays = -1;

    if ((y1 > y2) || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2) || !checkValidDate(y1, m1, d1) || !checkValidDate(y2, m2, d2))
    {
        return tr;
    }

    int totalDay = 0;
    int workingDay = 0;

    while (y1 != y2 || m1 != m2 || d1 != d2)
    {
        totalDay++;
        if (isWorkDay(y1, m1, d1))
        {
            workingDay++;
        }

        d1++;

        if (d1 > 31 || (d1 > 30 && (m1 == 4 || m1 == 6 || m1 == 9 || m1 == 11)) || (d1 > 29 && m1 == 2) || (d1 > 28 && m1 == 2 && !isLeapYear(y1)))
        {
            d1 = 1;
            m1++;
        }
        if (m1 > 12)
        {
            m1 = 1;
            y1++;
        }
    }
    if (isWorkDay(y2, m2, d2))
    {
        workingDay++;
    }
    totalDay++;

    tr.m_TotalDays = totalDay;
    tr.m_WorkDays = workingDay;
    return tr;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{

    TResult r;

    assert(isWorkDay(2023, 10, 10));

    assert(!isWorkDay(2023, 11, 11));

    assert(!isWorkDay(2023, 11, 17));

    assert(!isWorkDay(2023, 11, 31));

    assert(!isWorkDay(2023, 2, 29));

    assert(!isWorkDay(2004, 2, 29));

    assert(isWorkDay(2008, 2, 29));

    assert(!isWorkDay(2001, 2, 29));

    assert(!isWorkDay(1996, 1, 2));

    r = countDays(2023, 11, 1,
                  2023, 11, 30);
    assert(r.m_TotalDays == 30);
    assert(r.m_WorkDays == 21);

    r = countDays(2023, 11, 1,
                  2023, 11, 17);
    assert(r.m_TotalDays == 17);
    assert(r.m_WorkDays == 12);

    r = countDays(2023, 11, 1,
                  2023, 11, 1);
    assert(r.m_TotalDays == 1);
    assert(r.m_WorkDays == 1);

    r = countDays(2023, 11, 17,
                  2023, 11, 17);
    assert(r.m_TotalDays == 1);
    assert(r.m_WorkDays == 0);

    r = countDays(2023, 1, 1,
                  2023, 12, 31);
    assert(r.m_TotalDays == 365);
    assert(r.m_WorkDays == 252);

    r = countDays(2024, 1, 1,
                  2024, 12, 31);
    assert(r.m_TotalDays == 366);
    assert(r.m_WorkDays == 254);

    r = countDays(2000, 1, 1,
                  2023, 12, 31);
    assert(r.m_TotalDays == 8766);
    assert(r.m_WorkDays == 6072);

    r = countDays(2001, 2, 3,
                  2023, 7, 18);
    assert(r.m_TotalDays == 8201);
    assert(r.m_WorkDays == 5682);

    r = countDays(2021, 3, 31,
                  2023, 11, 12);
    assert(r.m_TotalDays == 957);
    assert(r.m_WorkDays == 666);

    r = countDays(2001, 1, 1,
                  2000, 1, 1);
    assert(r.m_TotalDays == -1);
    assert(r.m_WorkDays == -1);

    r = countDays(2001, 1, 1,
                  2023, 2, 29);
    assert(r.m_TotalDays == -1);
    assert(r.m_WorkDays == -1);

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
