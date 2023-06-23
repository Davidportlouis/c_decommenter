#include <stdio.h>
#include <stdlib.h>
#define IN_COMMENT 1
#define OUT_COMMENT 0
#define SLASH_MARK 2
#define KLEENE_MARK 3
#define IN_QUOTES 4
#define OUT_QUOTES 5
#define NEWLINE 6
#define NONE 7
#define UNTERMINATED 8

int main(void) 
{
    int prev_state;
    int state = OUT_COMMENT;
    int quote_state = OUT_QUOTES;
    int nlineState = NONE;
    int x, prev;
    while((x = getchar()) != EOF)
    {
        if ((state == SLASH_MARK && (x != '*' && x != '/')) || (state == KLEENE_MARK && (x != '/' && x !='*')))
            state = prev_state;
        if ((x == '\'' || x == '\"') && state == OUT_COMMENT && prev != '\\')
        {
            if (quote_state == IN_QUOTES)
                quote_state = OUT_QUOTES;
            else 
                quote_state = IN_QUOTES;
        }
        else if (x == '*' && (quote_state == OUT_QUOTES || (quote_state == IN_QUOTES && state == IN_COMMENT)))
        {
            if(state == IN_COMMENT)
            {
                prev_state = state;
                state = KLEENE_MARK;
            }
            else if(state == SLASH_MARK)
                state = IN_COMMENT;
            else if(state == KLEENE_MARK && prev == '*')
            {
                putchar(prev);
                state = OUT_COMMENT;
            }
        }
        else if (x == '/' && (quote_state == OUT_QUOTES || (quote_state == IN_QUOTES && state == KLEENE_MARK)))
        {
            if(prev == '*' && state == OUT_COMMENT)
                state = OUT_COMMENT;
            else if(state == OUT_COMMENT)
            {
                prev_state = state;
                state = SLASH_MARK;
            }
            else if(state == KLEENE_MARK && prev_state == IN_COMMENT) {
                state = OUT_COMMENT;
                if (nlineState != NEWLINE)
                    putchar(' ');
                nlineState = NONE;
                continue;
            }
            else if(state == SLASH_MARK && prev == '/')
            {
                putchar(prev);
                state = OUT_COMMENT;
            }
        }
        if (state == OUT_COMMENT || (quote_state == IN_QUOTES && state == OUT_COMMENT) || (state == IN_COMMENT && x == '\n'))
        {
            if (state == IN_COMMENT && x == '\n')
                nlineState = NEWLINE;
            putchar(x);
        }
        prev = x;
    }
    if (comStat == UNTERMINATED)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
