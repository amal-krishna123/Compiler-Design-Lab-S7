%{
    #include <bits/stdc++.h>
    using namespace std;

    void yyerror(const char *s);
    int yylex();

    typedef struct node {
        struct node *left, *right;
        string val;
        int label;
    } NODE;

    NODE* makeNode(string val, NODE* left, NODE* right) {
        NODE *temp = new NODE();
        temp->val = val;
        temp->left = left;
        temp->right = right;
        temp->label = 0;
        return temp;
    }

    NODE* synTree;
%}

%union {
    char *str;
    struct node *node;
}

%token <str> PL MI MUL DIV OP CL EQ ID VAL SC UNR POW
%type <node> s e t f g

%left PL MI
%left MUL DIV
%right POW

%%

s : e { synTree = $1; }
  ;

e : e PL t { $$ = makeNode($2, $1, $3); }
  | e MI t { $$ = makeNode($2, $1, $3); }
  | t      { $$ = $1; }
  ;

t : t MUL f { $$ = makeNode($2, $1, $3); }
  | t DIV f { $$ = makeNode($2, $1, $3); }
  | f       { $$ = $1; }
  ;

f : g POW f { $$ = makeNode($2, $1, $3); }
  | g       { $$ = $1; }
  ;

g : OP e CL       { $$ = $2; }
  | ID            { $$ = makeNode($1, NULL, NULL); }
  | VAL           { $$ = makeNode($1, NULL, NULL); }
  ;

%%

void inOrder(NODE* root) {
    if (root) {
        inOrder(root->left);
        cout << root->val << " ";
        inOrder(root->right);
    }
}

void postOrder(NODE* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->val << " ";
    }
}

void preOrder(NODE* root) {
    if (root) {
        cout << root->val << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void yyerror(const char *s) {
    cout << "Error: " << s << endl;
}

int main() {
    cout << "Enter expression:\n";
    yyparse();

    cout << "In Order:\n";
    inOrder(synTree);
    cout << "\nPre Order:\n";
    preOrder(synTree);
    cout << "\nPost Order:\n";
    postOrder(synTree);
    cout << endl;

    return 0;
}