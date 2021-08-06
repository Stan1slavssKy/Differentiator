#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

#include "../libs/include.h"
#include "../libs/Onegin.h"
#include "../tree/tree.h"

//=============================================================================================

const int MAX_DEGREE = 255;

//=============================================================================================

double create_nmb (diff_tree* dftr, FILE* formula);
double create_exp (diff_tree* dftr, FILE* formula);
double create_t   (diff_tree* dftr, FILE* formula);
double create_p   (diff_tree* dftr, FILE* formula);
double create_w   (diff_tree* dftr, FILE* formula);

inline void skip_spaces (char* counter);

void create_diff_article (text* formula_info, FILE* formula, char* file_name);

//=============================================================================================

#endif