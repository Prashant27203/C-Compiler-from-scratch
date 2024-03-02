#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

// token field can be one of these values
enum {
    T_PLUS, // will be used for addition operator
    T_MINUS,// will be used for addition and subtraction operators
    T_STAR, // will be used for multiplication operator
    T_SLASH,// will be used for arithmetic operators
    T_INTLIT // will be used for integer literals
};

//Token structure
struct token{
    int token ;// will be used to store the token field
    int intvalue ;// will be used to store the value of the integer literal
};
