#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char *messageInput = NULL;
    size_t input_string_size = 0;
    int first[2];
    int second[2];
    int result[10000];
    int flag[4];

    for (int i = 0; i < 2; i++)
    {
        first[i] = 0;
        second[i] = 0;
    }

    printf("Messages:\n");
    for (int i = 0; i < 2; i++)
    {
        if (getline(&messageInput, &input_string_size, stdin) == EOF)
        {
            printf("Invalid input.\n");
            free(messageInput);
            return -1;
        }
        size_t len = strlen(messageInput);
        if (messageInput[len - 1] == '\n')
        {
            messageInput[len - 1] = '\0';
        }
        int count = 0;
        for (int j = 0; messageInput[j] != '\0'; j++)
        {
            if (messageInput[j] == '|')
            {
                count++;
            }
        }

        if (count != 1)
        {
            printf("Invalid input.\n");
            free(messageInput);
            return -1;
        }
        else
        {
            size_t index = 0;
            for (int j = 0; messageInput[j] != '|'; j++)
            {
                if (messageInput[j] == ' ' || !islower(messageInput[j]))
                {
                    printf("Invalid input.\n");
                    free(messageInput);
                    return -1;
                }
                else
                {

                    // bit shift
                    first[i] += 1 << (messageInput[j] - 'a');
                }
                index = j;
            }

            if (index == 0 && messageInput[0] == '|')
            {
                flag[i] = 1;
            }
            if (index == (len - 3))
            {
                flag[i + 2] = 1;
            }

            if (len == 3)
            {
                second[i] += 1 << (messageInput[1] - 'a');
            }

            for (int j = index + 2; messageInput[j] != '\0'; j++)
            {
                if (messageInput[j] == ' ' || !islower(messageInput[j]))
                {
                    printf("Invalid input.\n");
                    free(messageInput);
                    return -1;
                }
                else
                {
                    // bit shift
                    second[i] += 1 << (messageInput[j] - 'a');
                }
            }
        }
        free(messageInput);
        messageInput = NULL;
        input_string_size = 0;
    }

    second[0] += first[0];
    second[1] += first[1];

    if ((first[0] == 0 && second[0] == 0) || (first[1] == 0 && second[1] == 0))
    {
        printf("Invalid input.\n");
        return -1;
    }

    if ((flag[0] && flag[1]) || (flag[2] && flag[3]))
    {
        printf("Synchronized in: 0\n");
        return 0;
    }

    if (second[0] > second[1])
    {
        for (int i = 0; i < 10000; i++)
        {
            result[i] = first[0] + (i * second[0]);
            if (((result[i] - first[1]) % second[1]) == 0)
            {
                printf("Synchronized in: %d\n", result[i]);
                return 0;
            }
        }
    }

    if (second[1] >= second[0])
    {
        for (int i = 0; i < 10000; i++)
        {
            result[i] = first[1] + (i * second[1]);
            if (((result[i] - first[0]) % second[0]) == 0)
            {
                printf("Synchronized in: %d\n", result[i]);
                return 0;
            }
        }
    }

    printf("Never synchronizes.\n");
    return 0;
}
