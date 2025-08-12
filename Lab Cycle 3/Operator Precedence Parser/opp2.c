#include <stdio.h>
#include <string.h>

int main()
{
    char stack[50], ip[50], opt[10][10][2], ter[10];
    int i, j, k, n, top = 0, col = -1, row = -1;

    printf("Enter the number of terminals:\n");
    scanf("%d", &n);

    printf("\nEnter the terminals (no spaces):\n");
    scanf("%s", ter);

    printf("\nEnter the precedence table values (<, >, =, e):\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Enter the value for %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }

    printf("\n**** OPERATOR PRECEDENCE TABLE ****\n\t");
    for (i = 0; i < n; i++)
    {
        printf("%c\t", ter[i]);
    }
    printf("\n");
    for (i = 0; i < n; i++)
    {
        printf("%c\t", ter[i]);
        for (j = 0; j < n; j++)
        {
            printf("%c\t", opt[i][j][0]);
        }
        printf("\n");
    }

    stack[top] = '$';
    stack[top + 1] = '\0';

    printf("\nEnter the input string (use '$' at end): ");
    scanf("%s", ip);

    i = 0;
    printf("\nSTACK\t\tINPUT STRING\n");
    printf("------------------------------\n");

    while (1)
    {
        printf("%-15s", stack);
        for (k = i; k < strlen(ip); k++)
        {
            printf("%c", ip[k]);
        }
        printf("\n");

        col = -1;
        row = -1;
        for (k = 0; k < n; k++)
        {
            if (stack[top] == ter[k])
                col = k;
            if (ip[i] == ter[k])
                row = k;
        }

        if (col == -1 || row == -1)
        {
            printf("Error: Invalid symbol '%c'\n", (col == -1) ? stack[top] : ip[i]);
            break;
        }

        if (stack[top] == '$' && ip[i] == '$')
        {
            while (top > 0)
            {
                top--;
            }
            stack[top + 1] = '\0';

            printf("%-15s", stack);
            for (k = i; k < strlen(ip); k++)
            {
                printf("%c", ip[k]);
            }
            printf("\n");

            printf("\nACCEPTED\n");
            break;
        }

        if (opt[col][row][0] == '<' || opt[col][row][0] == '=')
        {
            stack[++top] = ip[i];
            stack[top + 1] = '\0';
            i++;
        }
        else if (opt[col][row][0] == '>')
        {
            do
            {
                top--;
                col = -1;
                for (k = 0; k < n; k++)
                {
                    if (stack[top] == ter[k])
                        col = k;
                }
            } while (col != -1 && stack[top] != '$' &&
                     opt[col][row][0] != '<');
        }
        else
        {
            printf("String is not accepted (no relation)\n");
            break;
        }
    }

    return 0;
}