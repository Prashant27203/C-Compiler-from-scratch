#include"defs.h"
#include"data.h"
#include"decl.h"
#include<errno.h>

int chpros(char *s, int c)
{
    char *p;                 // Pointer to the character
    p = strchr(s, c);        // Find the character in the string
    return (p ? p - s : -1); // Return the position of the characters
}

// next - get the next character from the input source code file
static int next(void){
    int c ;
    if(Putback){// If there is a character in the putback buffer
        c = Putback ;// Get the character from the putback buffer
        Putback = 0 ;// Clear the putback buffer
        return c ;// Return the character
    }
    c = fgetc(Infile) ;// Get the next character from the input file
    if('\n' == c){// If the character is a newline
        line++ ;// Increment the line number
    }
    return c ;// Return the character
}



// putback - put a character back into the input
static void putback(int c){
    Putback = c ;// Put the character into the putback buffer
}



// skip - skip white space and comments in the input
static int skip(void){
    int c ;
    c = next() ;// Get the next character
    while(' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c || '\v' == c || '/' == c && '/' == next()){// While the character is a space, tab, newline, carriage return, form feed, vertical tab, or a comment
        if('/' == c){// If the character is a forward slash
            while('\n' != c && EOF != c){// While the character is not a newline and not the end of the file
                c = next() ;// Get the next character
            }
        }
        c = next() ;// Get the next character
    }
    return c ;// Return the character
}



// scanint - scan the input for an integer literal
int scanint(int c)
{
    int k, val = 0;
    while ((k = chpros("0123456789",c)) >= 0)
    {
        val = val * 10 + (k - '0');
        c = next();
    }
    putback(c);
    return val;
}
//chrpos - find a character in a string



//scanning the tokens 

//scans the input file and returns the token
int scan (struct token *t){
    int c ;
    c = skip() ;// Skip white space and comments
    switch (c){
        case EOF : return (0);// If the character is the end of the file, return the end of file token
        case '+' : t->token = T_PLUS;// If the character is a plus sign, return the plus token
        case '-' : t->token = T_MINUS;// If the character is a minus sign, return the minus token
        case '*' : t->token = T_STAR;// If the character is an asterisk, return the star token
        case '/' : t->token = T_SLASH;// If the character is a forward slash, return the slash token
        default:
            if(isdigit(c)){
                t->intvalue =  scanint(c);// Convert the character to an integer
                t->token = T_INTLIT ;// Return the integer literal token
                break;
            }
            printf("Unrecognised character %c on line %d\n", c, line) ;// Print an error message
            exit(1) ;// Exit the program

    }
    return (1);// Return the token
}


