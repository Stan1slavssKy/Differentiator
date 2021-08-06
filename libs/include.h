#ifndef LIBS_H_INCLUDED
#define LIBS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <locale.h>
#include <math.h>

//===================================================================================

enum sign
{
    POS =  1,
    NEG = -1
};

//===================================================================================

enum type
{
    NMBR = 1,
    OPRD,
    BRCT
};

enum oper_value
{
    ADD = 1,
    SUB,
    DIV,
    MUL,
    POW
};

enum brck_value 
{
    LEFT  = 1,
    RIGHT = 2
};

//===================================================================================

#endif