%{
    
    #include "calc.tab.h"
    #include <FlexLexer.h>
     #undef yyFlexLexer
     #define yyFlexLexer xxFlexLexer
     #include <FlexLexer.h>

     #undef yyFlexLexer
     #define yyFlexLexer zzFlexLexer
     #include <FlexLexer.h>
%}

%option noyywrap

%%
[0-9]+(\.[0-9]+)?    { yylval = atof(yytext); return NUMBER; }
[-+*/()^]            { return yytext[0]; }
[ \t\n]              ;  // Skip whitespace
.                    { /* Ignore all other characters */ }

%%
