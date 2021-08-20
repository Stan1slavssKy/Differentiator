#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

#include "../libs/include.h"
#include "../libs/Onegin.h"
#include "../tree/tree.h"

//=============================================================================================

const int MAX_DEGREE = 255;

//=============================================================================================

void create_diff_article (text* formula_info, char* file_name);
void create_dftr_tree    (text* formula_info, char* file_name);

tree_node* create_nmb (diff_tree* dftr);
tree_node* create_exp (diff_tree* dftr);
tree_node* create_t   (diff_tree* dftr);
tree_node* create_p   (diff_tree* dftr);
tree_node* create_w   (diff_tree* dftr);

inline void skip_spaces   (diff_tree* dftr);
inline void input_operand (tree_node* cur_node, oper_value oper_value);

void node_input (tree_node* cur_node, type sym_info, oper_value oper_info, double sym_value);

//=============================================================================================

#endif