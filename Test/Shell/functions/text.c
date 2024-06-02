#include "../../include/stdio.h"
#include "../../include/terminal.h"
#include "../shellFunctions.h"
#define FDEF(name) void name(const char* s)


FDEF(echo){
    My_puts(s + 4);
}

FDEF(clear){
    terminal_initialize((uint16_t*)0xb8000);
}

double parseNumber(const char **expression);

FDEF(calc)
{
    char* exp = s+4;
    char op = '+';
    int used = 1;
    double num = 0;
    int sum = 0;
    while(*exp)
    {
        if(*exp == '*' || *exp == '/' || *exp == '+' || *exp == '-')
        {
            if(used == 0)
            {
                My_puts("Error: Invalid statment\n");
                return;
            }
            else
            {
                op = *exp;
                used = 0;
            }
            exp++;
        }
        else if(*exp >= '0' && *exp <= '9')
        {
            num = parseNumber(&exp);
            used = 1;
            if(op == '+')
            {
                sum += num;
            }
            else if(op == '-')
            {
                sum -= num;
            }
            else if(op == '*')
            {
                sum *= num;
            }
            else if(op == '/')
            {
                sum /= num;
            }
        }
        else
        {
            exp++;
        }
    }
    My_printf("RES: %d",sum);
}

double parseNumber(const char **expression) {
    double number = 0.0;
    while (**expression >= '0' && **expression <= '9') {
        number = number * 10 + (**expression - '0');
        (*expression)++;
    }
    if (**expression == '.') {
        (*expression)++;
        double decimal = 1.0;
        while (**expression >= '0' && **expression <= '9') {
            number = number + (**expression - '0') * (decimal *= 0.1);
            (*expression)++;
        }
    }
    return number;
}
