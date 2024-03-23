#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct ContactInfo
{
    char phoneNumber[20 + 1];
    char *name;
} ContactInfo;

bool T9Conversion(char name, char digit)
{
    switch (digit)
    {
    case '2':
        if (name == 'a' || name == 'b' || name == 'c' || name == 'A' || name == 'B' || name == 'C')
            return true;
        break;
    case '3':
        if (name == 'd' || name == 'e' || name == 'f' || name == 'D' || name == 'E' || name == 'F')
            return true;
        break;
    case '4':
        if (name == 'g' || name == 'h' || name == 'i' || name == 'G' || name == 'H' || name == 'I')
            return true;
        break;
    case '5':
        if (name == 'j' || name == 'k' || name == 'l' || name == 'J' || name == 'K' || name == 'L')
            return true;
        break;
    case '6':
        if (name == 'm' || name == 'n' || name == 'o' || name == 'M' || name == 'N' || name == 'O')
            return true;
        break;
    case '7':
        if (name == 'p' || name == 'q' || name == 'r' || name == 's' || name == 'P' || name == 'Q' || name == 'R' || name == 'S')
            return true;
        break;
    case '8':
        if (name == 't' || name == 'u' || name == 'v' || name == 'T' || name == 'U' || name == 'V')
            return true;
        break;
    case '9':
        if (name == 'w' || name == 'x' || name == 'y' || name == 'z' || name == 'W' || name == 'X' || name == 'Y' || name == 'Z')
            return true;
        break;
    case '1':
        if (name == ' ')
            return true;
        break;

    default:
        return false;
    }

    return false;
}

bool T9Search(char *haystack, char *needle)
{
    int n = 0;
    int needle_length = strlen(needle);
    int haystack_length = strlen(haystack);

    if (haystack_length < needle_length)
        return false;

    for (int i = 0; i < needle_length; i++)
    {

        if (T9Conversion(haystack[n], needle[n]))
        {
            n++;
        }
        else
        {
            return false;
        }
        if (n == needle_length)
        {
            return true;
        }
    }
    return false;
}

void printArray(ContactInfo *ci, size_t size)
{

    printf("Inside Print Array: size %zu \n", size);
    for (size_t i = 0; i < size; i++)
    {
        printf("\nIndex %zu\n", i);
        printf("ph: %s \n", ci[i].phoneNumber);
        printf("%s\n", ci[i].name);
    }
}

void printContacts(ContactInfo *ci, size_t size, char *searchQuery, int **resultArray, int *resultArrayIndex, int *resultArrayCapacity)
{

    size_t searchQueryLength = strlen(searchQuery);
    if (size < 1 || searchQueryLength < 0)
    {
    }

    for (size_t i = 0; i < size; i++)
    {

        size_t result = strncmp(ci[i].phoneNumber, searchQuery, searchQueryLength);

        if (result == 0)
        {
            // printf("ph -%s %s\n", ci[i].phoneNumber, ci[i].name);
            (*resultArray)[*resultArrayIndex] = i;
            *resultArrayIndex = *resultArrayIndex + 1;
        }

        else
        {

            if (T9Search(ci[i].name, searchQuery))
            {
                // printf("T 9 - %s %s\n", ci[i].phoneNumber, ci[i].name);
                (*resultArray)[*resultArrayIndex] = i;
                *resultArrayIndex = *resultArrayIndex + 1;
            }
        }

        if (*resultArrayIndex == *resultArrayCapacity)
        {

            *resultArrayCapacity *= 2;
            *resultArray = (int *)realloc(*resultArray, *resultArrayCapacity * sizeof(int));
        }
    }

    if (*resultArrayIndex <= 10)
    {
        for (int i = 0; i < *resultArrayIndex; i++)
        {

            printf("%s %s\n", ci[(*resultArray)[i]].phoneNumber, ci[(*resultArray)[i]].name);
        }
    }

    printf("Total: %d\n", *resultArrayIndex);
}

bool checkDuplicate(ContactInfo *ci, size_t arrayIndex)
{

    if (arrayIndex < 1)
    {
        return false;
    }

    for (size_t i = 0; i < arrayIndex; i++)
    {
        if (strcmp(ci[i].name, ci[arrayIndex].name) == 0 &&
            strcmp(ci[i].phoneNumber, ci[arrayIndex].phoneNumber) == 0)
        {

            return true;
        }
    }
    return false;
}

int main()
{

    int resultArrayCapacity = 30;
    int resultArrayIndex = 0;
    int *resultArray = (int *)malloc(resultArrayCapacity * sizeof(int));

    size_t ciCapacity = 10;
    size_t arrayIndex = 0;
    // size_t nameSize = 100;
    char operation = '\0';

    ContactInfo *ci;
    ci = (ContactInfo *)malloc(ciCapacity * sizeof(ContactInfo));

    // Buffer to store the input line
    char *inputLine = NULL;
    size_t inputLineSize = 0;

    int phStart = 2;

    while (getline(&inputLine, &inputLineSize, stdin) != -1)
    {

        phStart = 2;
        if (inputLine[0] != '+' && inputLine[0] != '?')
        {
            printf("Invalid input.\n");
            continue;
        }

        size_t inputLength = strlen(inputLine);

        operation = inputLine[0];

        if (operation == '+')
        {

            if (inputLine[0] != '+' || inputLine[1] != ' ')
            {
                printf("Invalid input.\n");
                continue;
            }

            while (isdigit(inputLine[phStart]))
            {
                phStart++;
            }

            if (phStart > 22)
            {
                printf("Invalid input.\n");
                continue;
            }

            if ((int)inputLength - 1 == phStart)
            {
                printf("Invalid input.\n");
                continue;
            }

            if (!isspace(inputLine[phStart]) || isspace(inputLine[phStart + 1]))
            {

                printf("Invalid input.\n");
                continue;
            }

            int errorInName = 0;

            for (size_t i = phStart + 1; i < inputLength - 1; i++)
            {

                if (!isalpha(inputLine[i]) && !isspace(inputLine[i]))
                {
                    errorInName = 1;
                    i = inputLength - 1;
                }
            }

            if (errorInName == 1)
            {
                printf("Invalid input.\n");
                continue;
            }

            if (inputLine[inputLength - 2] == ' ')
            {
                printf("Invalid input.\n");
                continue;
            }

            ci[arrayIndex].name = (char *)malloc((inputLength - phStart + 1) * sizeof(char));

            sscanf(inputLine, "+ %20s %[^\n]", ci[arrayIndex].phoneNumber, ci[arrayIndex].name);

            if (checkDuplicate(ci, arrayIndex))
            {
                printf("Duplicate contact.\n");
            }
            else
            {
                printf("OK\n");
                arrayIndex++;
            }

            if (arrayIndex == ciCapacity)
            {
                ciCapacity *= 2;
                ci = (ContactInfo *)realloc(ci, ciCapacity * sizeof(ContactInfo));
            }
        }
        else if (operation == '?')
        {

            resultArrayIndex = 0;
            resultArrayCapacity = 10;
            char *searchQuery = inputLine + 2;

            if (inputLength < 3)
            {
                printf("Invalid input.\n");
                continue;
            }

            if (inputLength > 2 && inputLine[2] == ' ')
            {
                printf("Invalid input.\n");
                continue;
            }

            sscanf(inputLine, "? %[^\n]", searchQuery);

            size_t searchQLength = strlen(searchQuery);

            int searchQError = 0;
            for (size_t i = 2; i < searchQLength; i++)
            {
                if (!isdigit(searchQuery[i]))
                {
                    searchQError = 1;
                    i = searchQLength;
                }
            }

            if (searchQError == 1)
            {
                printf("Invalid input.\n");
                continue;
            }

            printContacts(ci, arrayIndex, searchQuery, &resultArray, &resultArrayIndex, &resultArrayCapacity);
        }
    }

    // free resources

    if (!feof(stdin))
    {
        for (size_t i = 0; i < arrayIndex; i++)
        {
            free(ci[i].name);
        }

        free(inputLine);
        free(ci);
        free(resultArray);
        return 0;
    }

    for (size_t i = 0; i < arrayIndex; i++)
    {
        free(ci[i].name);
    }

    free(inputLine);
    free(ci);
    free(resultArray);

    return 0;
}
