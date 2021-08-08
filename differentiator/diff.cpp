#include "diff.h"

//=============================================================================================

void create_diff_article (text* formula_info, char* file_name)
{
    assert (formula_info);
    assert (file_name);

    input_inform (file_name, formula_info); 
    assert (formula_info -> file_buffer);

    diff_tree* dftr = (diff_tree*) calloc (1, sizeof (diff_tree));
    assert (dftr);

    dftr -> counter = formula_info -> file_buffer;
 
    printf ("RESULT = [%lf]\n\n", create_exp (dftr, formula));

    free (dftr);
}

//=============================================================================================

tree_node* create_nmb (diff_tree* dftr, FILE* formula)
{   
    skip_spaces (dftr);

    double out_nmb = atof (dftr -> counter);

    while (isdigit (*dftr -> counter) || *dftr -> counter == '.')
        dftr -> counter++;

    skip_spaces (dftr);

    tree_node* cur_node = create_node (dftr -> counter);
    assert (cur_node);                                      
                                                            
    NODE_CREATE (NMBR, out_nmb)

    return cur_node;
}

//=============================================================================================

tree_node* create_exp (diff_tree* dftr, FILE* formula)
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
    tree_node* left_node  = create_t (dftr, formula);
    
    while (*dftr -> counter == '+' || *dftr -> counter == '-')
    {
        if (*dftr -> counter == '+')
        {
            dftr -> counter++;
            s = POS;
            
            cur_node = create_node (dftr -> counter);
            assert (cur_node); 
            
            NODE_CREATE (OPRD, NAN)
        }
        else if (*dftr -> counter == '-')
        {
            dftr -> counter++;
            s = NEG; 
            
            cur_node = create_node (dftr -> counter);
            assert (cur_node); 
            
            NODE_CREATE (OPRD, NAN)
        }   

        skip_spaces (dftr);

        right_node = create_t (dftr, formula);
    }

    cur_node -> right = right_node;
    cur_node -> left  = left_node;

    skip_spaces (dftr);
    
    return cur_node;
}

//=============================================================================================

tree_node* create_t (diff_tree* dftr, FILE* formula)
{
    skip_spaces (dftr);
    
    double res_nmb = create_w (dftr, formula);

    while (*dftr -> counter == '*' || *dftr -> counter == '/')
    {
        skip_spaces (dftr);

        if (*dftr -> counter == '*')
        {
            dftr -> counter++;
            res_nmb *= create_w (dftr, formula);

            NODE_CREATE (OPRD, NAN)
        }
        else if (*dftr -> counter == '/')
        {
            dftr -> counter++;
            res_nmb /= create_w (dftr, formula);

            NODE_CREATE (OPRD, NAN)
        }   
    }

    skip_spaces (dftr);
    
    return cur_node;
}

//=============================================================================================

tree_node* create_p (diff_tree* dftr, FILE* formula)
{
    skip_spaces (dftr);

    double res_nmb = 0;

    if (*dftr -> counter == '(')
    {
        dftr -> counter++;

        res_nmb = create_exp (dftr, formula);
        
        if (*dftr -> counter == ')')
            dftr -> counter++;
        else  
            fprintf (stderr, "Error, %d\n", __LINE__);
    }
    else
    {
        res_nmb = create_nmb (dftr, formula);
    }

    skip_spaces (dftr);

    return cur_node;
}

//=============================================================================================

tree_node* create_w (diff_tree* dftr, FILE* formula)
{
    skip_spaces (dftr);

    double res_nmb = create_p (dftr, formula);
    double degrees [MAX_DEGREE] = {};
   
    double x     = 1;
    int nmb_degr = 0;

    while (*dftr -> counter == '^')
    {
        dftr -> counter++;

        if (nmb_degr == MAX_DEGREE)
        {
            fprintf (stderr, "Too many degrees\n");
            return nullptr;
        }
        
        degrees [nmb_degr++] = create_p (dftr, formula);

        NODE_CREATE (OPRD, NAN)

        skip_spaces (dftr);
    }
    
    while (nmb_degr != 0)
    { 
        x = pow (degrees [--nmb_degr], x);
    }

    skip_spaces (dftr);

    res_nmb = pow (res_nmb, x);
   
    return cur_node;
}

//=============================================================================================

inline void skip_spaces (diff_tree* dftr)
{
    while (isspace (*dftr -> counter))
        dftr -> counter++;   
}

//=============================================================================================