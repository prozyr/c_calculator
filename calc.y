%{
    #include <stdio.h>
    #include <math.h>

    extern int yylex();
    extern int yyparse();
    extern FILE* yyin;

    // Function to handle the result of the parser
    void handle_result(double result);
%}

%token NUMBER
%token ADD SUB MUL DIV POW

%left '+' '-'
%left '*' '/'
%left POW

%%
calc: expr   { handle_result($1); }
    ;

expr: expr ADD expr   { $$ = $1 + $3; }
    | expr SUB expr   { $$ = $1 - $3; }
    | expr MUL expr   { $$ = $1 * $3; }
    | expr DIV expr   { $$ = $1 / $3; }
    | expr POW expr   { $$ = pow($1, $3); }
    | NUMBER          { $$ = atof(yytext); }
    ;

%%