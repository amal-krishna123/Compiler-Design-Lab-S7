#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = 0;

char precTable[9][9] = {
    // +    -    *    /    ^    i    (    )    $
    {'>', '>', '<', '<', '<', '<', '<', '>', '>'}, // +
    {'>', '>', '<', '<', '<', '<', '<', '>', '>'}, // -
    {'>', '>', '>', '>', '<', '<', '<', '>', '>'}, // *
    {'>', '>', '>', '>', '<', '<', '<', '>', '>'}, // /
    {'>', '>', '>', '>', '>', '<', '<', '>', '>'}, // ^
    {'>', '>', '>', '>', '>', 'e', 'e', '>', '>'}, // id
    {'<', '<', '<', '<', '<', '<', '<', '=', 'e'}, // (
    {'>', '>', '>', '>', '>', 'e', 'e', '>', '>'}, // )
    {'<', '<', '<', '<', '<', '<', '<', 'e', 'a'}  // $
};

char symbols[] = {'+', '-', '*', '/', '^', 'i', '(', ')', '$'};

int getIndex(char symbol)
{
    for (int i = 0; i < 9; i++)
    {
        if (symbols[i] == symbol)
            return i;
    }
    return -1;
}

void printStackInput(int i)
{
    printf("%-15s %-15s\n", stack, input + i);
}

int main()
{
    char a;
    int i = 0, idx1, idx2;

    printf("Enter the input string (use 'i' for id): ");
    scanf("%s", input);
    strcat(input, "$");
    stack[top] = '$';
    stack[top + 1] = '\0';

    printf("\nStack           Input\n");
    printf("------------------------------\n");

    while (1)
    {
        printStackInput(i);

        idx1 = getIndex(stack[top]);
        idx2 = getIndex(input[i]);

        if (idx1 == -1 || idx2 == -1)
        {
            printf("Error: Invalid symbol '%c'\n", input[i]);
            break;
        }

        a = precTable[idx1][idx2];
        if (a == '<' || a == '=')
        {
            stack[++top] = input[i++];
            stack[top + 1] = '\0';
        }
        else if (a == '>')
        {
            do
            {
                if (stack[top] == ')' && stack[top - 1] == '(')
                {
                    top -= 2;
                }
                else
                {
                    top--;
                }
                stack[top + 1] = '\0';

                idx1 = getIndex(stack[top]);
                idx2 = getIndex(input[i]);
                a = precTable[idx1][idx2];
            } while (a == '>');
        }
        else if (a == 'a')
        {
            printf("Parsing successful!\n");
            break;
        }
        else
        {
            printf("Error: Invalid precedence relation\n");
            break;
        }
    }
    return 0;
}