#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 10

int nfa[MAX_STATES][MAX_SYMBOLS][MAX_STATES]; 
int nfa_final[MAX_STATES];                    
int nfa_num_states, nfa_num_symbols;
char symbols[MAX_SYMBOLS];

int dfa_states[1024][MAX_STATES]; 
int dfa_state_count = 0;
int dfa_final[1024] = {0};
int dfa_trans[1024][MAX_SYMBOLS]; 

int is_state_set_equal(int a[], int b[])
{
    for (int i = 0; i < nfa_num_states; i++)
    {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

int state_set_exists(int state_set[])
{
    for (int i = 0; i < dfa_state_count; i++)
    {
        if (is_state_set_equal(dfa_states[i], state_set))
            return i;
    }
    return -1;
}

void add_state_set(int state_set[])
{
    memcpy(dfa_states[dfa_state_count], state_set, sizeof(int) * MAX_STATES);
    dfa_state_count++;
}

void print_dfa()
{
    printf("\nDFA Transition Table:\n");
    for (int i = 0; i < dfa_state_count; i++)
    {
        printf("DFA State %d (", i);
        for (int k = 0; k < nfa_num_states; k++)
        {
            if (dfa_states[i][k])
                printf("%d", k);
        }
        printf("):\n");
        for (int j = 0; j < nfa_num_symbols; j++)
        {
            printf("  on '%c' -> DFA State %d\n", symbols[j], dfa_trans[i][j]);
        }
    }

    printf("\nDFA Final States: ");
    for (int i = 0; i < dfa_state_count; i++)
    {
        if (dfa_final[i])
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main()
{
    printf("Enter number of NFA states: ");
    scanf("%d", &nfa_num_states);
    printf("Enter number of input symbols: ");
    scanf("%d", &nfa_num_symbols);
    printf("Enter the input symbols:\n");
    for (int i = 0; i < nfa_num_symbols; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    printf("Enter NFA transitions (from symbol to_state), enter -1 to stop:\n");
    while (1)
    {
        int from, to;
        char sym;
        scanf("%d %c %d", &from, &sym, &to);
        if (from == -1 || to == -1)
            break;
        int idx = -1;
        for (int i = 0; i < nfa_num_symbols; i++)
        {
            if (symbols[i] == sym)
            {
                idx = i;
                break;
            }
        }
        if (idx != -1)
        {
            nfa[from][idx][to] = 1;
        }
    }

    printf("Enter number of NFA final states: ");
    int n;
    scanf("%d", &n);
    printf("Enter final state numbers:\n");
    for (int i = 0; i < n; i++)
    {
        int f;
        scanf("%d", &f);
        nfa_final[f] = 1;
    }

    int start_state[MAX_STATES] = {0};
    start_state[0] = 1; 
    add_state_set(start_state);

    for (int i = 0; i < dfa_state_count; i++)
    {
        for (int s = 0; s < nfa_num_symbols; s++)
        {
            int new_state[MAX_STATES] = {0};
            for (int q = 0; q < nfa_num_states; q++)
            {
                if (dfa_states[i][q])
                {
                    for (int r = 0; r < nfa_num_states; r++)
                    {
                        if (nfa[q][s][r])
                        {
                            new_state[r] = 1;
                        }
                    }
                }
            }
            int index = state_set_exists(new_state);
            if (index == -1)
            {
                add_state_set(new_state);
                index = dfa_state_count - 1;
            }
            dfa_trans[i][s] = index;
        }
    }

    for (int i = 0; i < dfa_state_count; i++)
    {
        for (int j = 0; j < nfa_num_states; j++)
        {
            if (dfa_states[i][j] && nfa_final[j])
            {
                dfa_final[i] = 1;
                break;
            }
        }
    }

    print_dfa();

    return 0;
}
