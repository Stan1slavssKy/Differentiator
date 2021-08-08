#ifndef TREE_INCLUDED
#define TREE_INCLUDED

#include "../libs/include.h"
#include "../libs/Onegin.h"   

//===================================================================================
struct tree_node 
{
    type   sym_data;
    double value; 

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
void  node_graph   (tree_node* cur_node, FILE* grph_viz);

tree_node* create_node (char* cur_buff_pos);

//===================================================================================

#endif