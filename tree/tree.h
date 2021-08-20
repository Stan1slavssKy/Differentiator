#ifndef TREE_INCLUDED
#define TREE_INCLUDED

#include "../libs/include.h"
#include "../libs/Onegin.h"   

//===================================================================================

const int MAX_OPER_SYM = 2;

//===================================================================================

struct tree_node 
{
    oper_value oper_data;
    type       sym_data;
    double     value; 

    char dump_text[MAX_OPER_SYM] = {};

    tree_node* prev_node;
    tree_node* left;
    tree_node* right;
};

struct diff_tree
{
    int   nmb_nodes;
    int   error;
    char* counter;

    tree_node* root;
};

//===================================================================================

void node_destruct (tree_node* cur_tree);
void tree_destruct (tree_node* cur_node);

void  create_tree  (diff_tree* aktr, int idx);
void  node_graph (tree_node* cur_node, FILE* grph_viz);
void  create_graph_dump (tree_node* root, const char* dumpfile_name);
void make_dump (const char* dumpfile_name);

tree_node* create_node (const char* cur_buff_pos);

//===================================================================================

#endif