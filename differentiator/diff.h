#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

#include "../libs/include.h"
#include "../libs/Onegin.h"
#include "../tree/tree.h"

//=============================================================================================

#define NODE_CREATE(sym_info, sym_value)                    \
    cur_node -> sym_data = sym_info;                        \
    cur_node -> value    = sym_value;                       \

//=============================================================================================

const int MAX_DEGREE = 255;

//=============================================================================================

tree_node* create_nmb (diff_tree* dftr, FILE* formula);
tree_node* create_exp (diff_tree* dftr, FILE* formula);
tree_node* create_t   (diff_tree* dftr, FILE* formula);
tree_node* create_p   (diff_tree* dftr, FILE* formula);
tree_node* create_w   (diff_tree* dftr, FILE* formula);

inline void skip_spaces (diff_tree* dftr);

void create_diff_article (text* formula_info, char* file_name);

//=============================================================================================

#endif