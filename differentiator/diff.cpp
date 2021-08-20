#include "diff.h"

//=============================================================================================

void create_diff_article (text* formula_info, char* file_name)
{
    assert (formula_info);
    assert (file_name);

    create_dftr_tree (formula_info, file_name);
}

//=============================================================================================

void create_dftr_tree (text* formula_info, char* file_name)
{
    assert (formula_info);
    assert (file_name);

    input_inform (file_name, formula_info); 
    assert (formula_info -> file_buffer);

    diff_tree* dftr = (diff_tree*) calloc (1, sizeof (diff_tree));
    assert (dftr);
    
    dftr -> counter = formula_info -> file_buffer;
    dftr -> root    = create_exp (dftr);
    
    create_graph_dump (dftr -> root, "GraphViz/dump_file");

    tree_destruct (dftr -> root);
    free (dftr);
}

//=============================================================================================

tree_node* create_nmb (diff_tree* dftr)
{   
    skip_spaces (dftr);

    double out_nmb = atof (dftr -> counter);

    while (isdigit (*dftr -> counter) || *dftr -> counter == '.')
        dftr -> counter++;

    skip_spaces (dftr);

    tree_node* cur_node = create_node (dftr -> counter);
    assert (cur_node);                                      
                                                            
    node_input (cur_node, NMBR, NOT_OPER, out_nmb);

    return cur_node;
}

//=============================================================================================

tree_node* create_exp (diff_tree* dftr)
{
    skip_spaces (dftr);
    sign s = POS;

    if (*dftr -> counter == '-')
    {
        dftr -> counter++;
        s = NEG;  
    }

    tree_node* cur_node   = nullptr;
    tree_node* right_node = nullptr;
    tree_node* left_node  = create_nmb (dftr);
    
    while (*dftr -> counter == '+' || *dftr -> counter == '-')
    {
        if (*dftr -> counter == '+')
        {
            dftr -> counter++;
            s = POS;
            
            cur_node = create_node (dftr -> counter);
            assert (cur_node); 
            
            node_input (cur_node, OPRD, ADD, NOT_NMBR);
        }
        else if (*dftr -> counter == '-')
        {
            dftr -> counter++;
            s = NEG; 
            
            cur_node = create_node (dftr -> counter);
            assert (cur_node); 
            
            node_input (cur_node, OPRD, SUB, NOT_NMBR);
        }   

        skip_spaces (dftr);

        right_node = create_nmb (dftr);
    }

    cur_node -> right = right_node;
    cur_node -> left  = left_node;

    skip_spaces (dftr);
    
    return cur_node;
}

//=============================================================================================

tree_node* create_t (diff_tree* dftr)
{
    skip_spaces (dftr);
    
    tree_node* cur_node   = nullptr;
    tree_node* right_node = nullptr;
    tree_node* left_node  = create_w (dftr);

    while (*dftr -> counter == '*' || *dftr -> counter == '/')
    {
        skip_spaces (dftr);

        if (*dftr -> counter == '*')
        {
            dftr -> counter++;

            cur_node = create_node (dftr -> counter);
            assert (cur_node); 

            node_input (cur_node, OPRD, MUL, NOT_NMBR);
        }
        else if (*dftr -> counter == '/')
        {
            dftr -> counter++;

            cur_node = create_node (dftr -> counter);
            assert (cur_node); 

            node_input (cur_node, OPRD, DIV, NOT_NMBR);
        }   

        right_node = create_t (dftr);
    }

    cur_node -> right = right_node;
    cur_node -> left  = left_node;
    
    skip_spaces (dftr);
    
    return cur_node;
}

//=============================================================================================

tree_node* create_p (diff_tree* dftr)
{
    skip_spaces (dftr);

    tree_node* cur_node = nullptr;

    if (*dftr -> counter == '(')
    {
        dftr -> counter++;

        cur_node = create_exp (dftr);
        
        if (*dftr -> counter == ')')
            dftr -> counter++;
        else  
            fprintf (stderr, "Error, %d\n", __LINE__);
    }
    else
    {
        cur_node = create_nmb (dftr);
    }

    skip_spaces (dftr);

    return cur_node;
}

//=============================================================================================

tree_node* create_w (diff_tree* dftr)
{
    skip_spaces (dftr);

    tree_node* cur_node   = nullptr;
    tree_node* right_node = nullptr;
    tree_node* left_node  = create_p (dftr);

    while (*dftr -> counter == '^')
    {
        dftr -> counter++;

        cur_node = create_node (dftr -> counter);
        assert (cur_node); 

        node_input (cur_node, OPRD, POW, NOT_NMBR);
        
        right_node = create_w (dftr);
    }

    cur_node -> left  = left_node;
    cur_node -> right = right_node;

    skip_spaces (dftr);
   
    return cur_node;
}

//=============================================================================================

inline void skip_spaces (diff_tree* dftr)
{
    while (isspace (*dftr -> counter))
        dftr -> counter++;   
}

//=============================================================================================

void node_input (tree_node* cur_node, type sym_info, oper_value oper_info, double sym_value)
{   
    char* oper_sym = nullptr;

    if (oper_info != NOT_OPER) input_operand (cur_node, oper_info);

    cur_node -> sym_data = sym_info;
    cur_node -> value    = sym_value;
}

//=============================================================================================

inline void input_operand (tree_node* cur_node, oper_value oper_value)
{
    if (oper_value == ADD)
    {
        cur_node -> oper_data = ADD;
        cur_node -> dump_text[0] = '+'; 
        cur_node -> dump_text[1] = '\0'; 
    }
    else if (oper_value == SUB)
    {
        cur_node -> oper_data = SUB;
        cur_node -> dump_text[0] = '-'; 
        cur_node -> dump_text[1] = '\0'; 
    }
    else if (oper_value == DIV)
    {
        cur_node -> oper_data = DIV;
        cur_node -> dump_text[0] = '/'; 
        cur_node -> dump_text[1] = '\0'; 
    }
    else if (oper_value == MUL)
    {
        cur_node -> oper_data = MUL;
        cur_node -> dump_text[0] = '*'; 
        cur_node -> dump_text[1] = '\0'; 
    }
    else if (oper_value == POW)
    {
        cur_node -> oper_data = POW;
        cur_node -> dump_text[0] = '^'; 
        cur_node -> dump_text[1] = '\0'; 
    }
} 

//=============================================================================================
