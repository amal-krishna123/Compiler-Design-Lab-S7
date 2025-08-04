#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define EPSILON 'e'

int n_states, n_symbols;
char symbols[MAX];
int transitions[MAX][MAX][MAX];    
int epsilon_transitions[MAX][MAX]; 
int epsilon_closure[MAX][MAX];     
int epsilon_closure_size[MAX];

int is_final[MAX], new_final[MAX];

int get_symbol_index(char symbol)
{
    for (int i = 0; i < n_symbols; i++)
        if (symbols[i] == symbol)
            return i;
    return -1;
}

void compute_epsilon_closure()
{
    for (int i = 0; i < n_states; i++)
    {
        int visited[MAX] = {0};
        int stack[MAX], top = -1;
        stack[++top] = i;
        visited[i] = 1;
        epsilon_closure[i][epsilon_closure_size[i]++] = i;

        while (top >= 0)
        {
            int current = stack[top--];
            for (int j = 0; j < n_states; j++)
            {
                if (epsilon_transitions[current][j] && !visited[j])
                {
                    visited[j] = 1;
                    epsilon_closure[i][epsilon_closure_size[i]++] = j;
                    stack[++top] = j;
                }
            }
        }
    }
}

void remove_epsilon()
{
    for (int state = 0; state < n_states; state++)
    {
        for (int sym_idx = 0; sym_idx < n_symbols; sym_idx++)
        {
            int reachable[MAX] = {0};
            for (int i = 0; i < epsilon_closure_size[state]; i++)
            {
                int e_state = epsilon_closure[state][i];
                for (int j = 0; j < n_states; j++)
                {
                    if (transitions[e_state][sym_idx][j])
                        reachable[j] = 1;
                }
            }

            for (int j = 0; j < n_states; j++)
            {
                if (reachable[j])
                    transitions[state][sym_idx][j] = 1;
            }
        }
    }

    // Update final states
    for (int state = 0; state < n_states; state++)
    {
        for (int i = 0; i < epsilon_closure_size[state]; i++)
        {
            if (is_final[epsilon_closure[state][i]])
                new_final[state] = 1;
        }
    }
}

void print_nfa_without_epsilon()
{
    printf("\nNFA without epsilon transitions:\n");
    for (int state = 0; state < n_states; state++)
    {
        for (int sym_idx = 0; sym_idx < n_symbols; sym_idx++)
        {
            printf("From state %d on '%c' -> ", state, symbols[sym_idx]);
            int found = 0;
            for (int j = 0; j < n_states; j++)
            {
                if (transitions[state][sym_idx][j])
                {
                    printf("%d ", j);
                    found = 1;
                }
            }
            if (!found)
                printf("None");
            printf("\n");
        }
    }

    printf("Final states: ");
    for (int i = 0; i < n_states; i++)
    {
        if (new_final[i])
            printf("%d ", i);
    }
    printf("\n");
}

int main()
{
    printf("Enter number of states: ");
    scanf("%d", &n_states);

    printf("Enter number of input symbols (excluding epsilon): ");
    scanf("%d", &n_symbols);

    printf("Enter the input symbols:\n");
    for (int i = 0; i < n_symbols; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    printf("Enter transitions:\nFormat: from symbol to (enter -1 to stop)\n");
    while (1)
    {
        int from, to;
        char symbol;
        scanf("%d %c %d", &from, &symbol, &to);
        if (from == -1 || to == -1)
            break;
        if (symbol == EPSILON)
        {
            epsilon_transitions[from][to] = 1;
        }
        else
        {
            int sym_idx = get_symbol_index(symbol);
            if (sym_idx != -1)
            {
                transitions[from][sym_idx][to] = 1;
            }
        }
    }

    printf("Enter number of final states: ");
    int n_final;
    scanf("%d", &n_final);
    printf("Enter final states:\n");
    for (int i = 0; i < n_final; i++)
    {
        int state;
        scanf("%d", &state);
        is_final[state] = 1;
    }

    compute_epsilon_closure();
    remove_epsilon();
    print_nfa_without_epsilon();

    return 0;
}
