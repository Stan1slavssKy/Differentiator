#include "tree.h"

//===================================================================================
/*
void create_tree (diff_tree* dftr, int idx)
{
    assert (dftr);

    if (dftr -> root == nullptr) 
    {

    }

    else
        fprintf (stderr, "Error, second create of dftr tree, %d", __LINE__);
}   
*/
//===================================================================================

tree_node* create_node (char* cur_buff_pos)
{
    assert (cur_buff_pos);

    tree_node* cur_node = (tree_node*) calloc (1, sizeof (tree_node));
    assert (cur_node);

    return cur_node;
}

//===================================================================================
/*
void node_graph (tree_node* cur_node, FILE* grph_viz)
{  
    assert (cur_node);
    assert (grph_viz);

    if (cur_node -> right != nullptr && cur_node -> left != nullptr)
    {
        fprintf (grph_viz, "\t\t\"%s\" -> \"%s\"[label = \"No\"];\n",  cur_node -> data, cur_node -> left -> data);        
        fprintf (grph_viz, "\t\t\"%s\" -> \"%s\"[label = \"Yes\"];\n", cur_node -> data, cur_node -> right -> data);
       
        node_graph (cur_node -> right, grph_viz);
        node_graph (cur_node -> left,  grph_viz);
    }
}

//===================================================================================

tree_node* add_node (diff_tree* dftr, tree_node* cur_node, char* data)
{
    if (dftr -> root == nullptr)
    {
        dftr -> root = (tree_node*) calloc (1, sizeof (tree_node));
        assert (dftr -> root);

        dftr -> root -> right = nullptr;
        dftr -> root -> left  = nullptr;
        dftr -> root -> data  = data;
    }
    
    if (dftr -> answer == 1)
    {
        cur_node -> right = (tree_node*) calloc (1, sizeof (tree_node));
        assert (cur_node -> right);
    
        cur_node -> right -> data = data;
    }
    else if (dftr -> answer == 0)
    {
        cur_node -> left = (tree_node*) calloc (1, sizeof (tree_node));
        assert (cur_node -> left);
    
        cur_node -> left -> data = data;
    }
}
*/
//===================================================================================

void node_destruct (tree_node* cur_node)
{
    if (cur_node == nullptr)
        return;

    node_destruct (cur_node -> left);
    node_destruct (cur_node -> right);

    free (cur_node);
    cur_node = nullptr;
}

//===================================================================================

void tree_destruct (tree_node* cur_node)
{
    if (cur_node == nullptr)
        return;

    node_destruct (cur_node -> left);
    node_destruct (cur_node -> right);

    cur_node -> left  = nullptr;
    cur_node -> right = nullptr;

    free (cur_node);
    cur_node = nullptr;
}

//===================================================================================