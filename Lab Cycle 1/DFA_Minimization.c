#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10

int dfa[MAX_STATES][MAX_SYMBOLS];
int final[MAX_STATES];           
int num_states, num_symbols;
char symbols[MAX_SYMBOLS];

int distinguish[MAX_STATES][MAX_STATES]; 
int marked[MAX_STATES][MAX_STATES];

int get_symbol_index(char sym)
{
    for (int i = 0; i < num_symbols; i++)
    {
        if (symbols[i] == sym)
            return i;
    }
    return -1;
}

void minimize_dfa()
{
    for (int i = 0; i < num_states; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if ((final[i] && !final[j]) || (!final[i] && final[j]))
            {
                distinguish[i][j] = 1;
            }
        }
    }

    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (int i = 0; i < num_states; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (distinguish[i][j])
                    continue;
                for (int k = 0; k < num_symbols; k++)
                {
                    int a = dfa[i][k];
                    int b = dfa[j][k];
                    if (a == b)
                        continue;
                    if (a < b)
                    {
                        if (distinguish[b][a])
                        {
                            distinguish[i][j] = 1;
                            changed = 1;
                            break;
                        }
                    }
                    else
                    {
                        if (distinguish[a][b])
                        {
                            distinguish[i][j] = 1;
                            changed = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    int groups[MAX_STATES];
    for (int i = 0; i < num_states; i++)
        groups[i] = -1;

    int group_id = 0;
    for (int i = 0; i < num_states; i++)
    {
        if (groups[i] == -1)
        {
            groups[i] = group_id;
            for (int j = 0; j < num_states; j++)
            {
                if (i != j && !distinguish[i > j ? i : j][i < j ? i : j])
                {
                    groups[j] = group_id;
                }
            }
            group_id++;
        }
    }

    printf("\nMinimized DFA:\n");
    printf("Total states: %d\n", group_id);
    printf("State\t");
    for (int i = 0; i < num_symbols; i++)
    {
        printf("%c\t", symbols[i]);
    }
    printf("\n");

    for (int i = 0; i < group_id; i++)
    {
        printf("Q%d\t", i);
        for (int j = 0; j < num_symbols; j++)
        {
            int target = -1;
            for (int k = 0; k < num_states; k++)
            {
                if (groups[k] == i)
                {
                    target = groups[dfa[k][j]];
                    break;
                }
            }
            if (target != -1)
                printf("Q%d\t", target);
            else
                printf("-\t");
        }
        printf("\n");
    }

    printf("Final states in minimized DFA: ");
    int printed[MAX_STATES] = {0};
    for (int i = 0; i < num_states; i++)
    {
        if (final[i] && !printed[groups[i]])
        {
            printf("Q%d ", groups[i]);
            printed[groups[i]] = 1;
        }
    }
    printf("\n");
}

int main()
{
    printf("Enter number of states in DFA: ");
    scanf("%d", &num_states);
    printf("Enter number of input symbols: ");
    scanf("%d", &num_symbols);
    printf("Enter input symbols:\n");
    for (int i = 0; i < num_symbols; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    printf("Enter transition table (state on symbol):\n");
    for (int i = 0; i < num_states; i++)
    {
        printf("For state %d:\n", i);
        for (int j = 0; j < num_symbols; j++)
        {
            printf("  On '%c': ", symbols[j]);
            scanf("%d", &dfa[i][j]);
        }
    }

    printf("Enter number of final states: ");
    int n;
    scanf("%d", &n);
    printf("Enter final state numbers:\n");
    for (int i = 0; i < n; i++)
    {
        int f;
        scanf("%d", &f);
        final[f] = 1;
    }

    minimize_dfa();
    return 0;
}