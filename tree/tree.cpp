#include "tree.h"

//===================================================================================

tree_node* create_node (const char* cur_buff_pos)
{
    assert (cur_buff_pos);

    tree_node* cur_node = (tree_node*) calloc (1, sizeof (tree_node));
    assert (cur_node);

    return cur_node;
}

//===================================================================================

void create_graph_dump (tree_node* root, const char* dumpfile_name)
{
    char dot_f_name [150] = {};
    strcpy (dot_f_name, dumpfile_name);
    strcat (dot_f_name, ".dot");

    FILE* dump = fopen (dot_f_name, "wb");
    assert (dump);
    
    fprintf (dump, "digraph Differentiator\n{\n"
                   "\t\tnode [shape = \"circle\", color = \"darkgreen\", fontcolor = \"purple\"];\n"
		           "\t\tedge [color = \"darkgreen\"];\n\n");
    node_graph (root, dump);
    fprintf (dump, "}\n");

    fclose (dump);
    printf ("\t\t\tIS = [%s]\n", root -> dump_text);
    make_dump (dumpfile_name);
}

//===================================================================================

void make_dump (const char* dumpfile_name)
{
    char dump_syscall [150] = {};

    strcpy (dump_syscall, "dot -Tpng ");
    strcat (dump_syscall, dumpfile_name);
    strcat (dump_syscall, ".dot -o");
    strcat (dump_syscall, dumpfile_name);
    strcat (dump_syscall, ".png");

    system (dump_syscall);
}
//===================================================================================

void node_graph (tree_node* cur_node, FILE* grph_viz)
{  
    assert (cur_node);
    assert (grph_viz);

    if (cur_node -> right != nullptr && cur_node -> left != nullptr)
    {
        if (cur_node -> right -> sym_data == NMBR && cur_node -> left -> sym_data != NMBR)
        {
            fprintf (grph_viz, "\t\t\"%s\" -> \"%s\";\n",  cur_node -> dump_text, cur_node -> left  -> dump_text);        
            fprintf (grph_viz, "\t\t\"%s\" -> \"%lf\";\n", cur_node -> dump_text, cur_node -> right -> value);    
        }
        else if (cur_node -> right -> sym_data != NMBR && cur_node -> left -> sym_data == NMBR)
        {
            fprintf (grph_viz, "\t\t\"%s\" -> \"%lf\";\n", cur_node -> dump_text, cur_node -> left  -> value);        
            fprintf (grph_viz, "\t\t\"%s\" -> \"%s\";\n",  cur_node -> dump_text, cur_node -> right -> dump_text);    
        }
        else if (cur_node -> right -> sym_data == NMBR && cur_node -> left -> sym_data == NMBR)
        {
            fprintf (grph_viz, "\t\t\"%s\" -> \"%lf\";\n", cur_node -> dump_text, cur_node -> left  -> value);        
            fprintf (grph_viz, "\t\t\"%s\" -> \"%lf\";\n", cur_node -> dump_text, cur_node -> right -> value);    
        }
        else if (cur_node -> right -> sym_data != NMBR && cur_node -> left -> sym_data != NMBR)
        {
            fprintf (grph_viz, "\t\t\"%s\" -> \"%s\";\n", cur_node -> dump_text, cur_node -> left  -> dump_text);        
            fprintf (grph_viz, "\t\t\"%s\" -> \"%s\";\n", cur_node -> dump_text, cur_node -> right -> dump_text);    
        }
        else
        {
            fprintf (stderr, "ERROR in tree.cpp %d\n", __LINE__);
        }
        
        node_graph (cur_node -> right, grph_viz);
        node_graph (cur_node -> left,  grph_viz);
    }
}

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