#include "diff.h"

//=============================================================================================

void create_diff_article (text* formula_info, FILE* formula, char* file_name)
{
    assert (formula_info);
    assert (formula);
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

double create_nmb (diff_tree* dftr, FILE* formula)
{   
    skip_spaces (dftr);

    double out_nmb = atof (dftr -> counter);

    while (isdigit(*dftr -> counter) || *dftr -> counter == '.')
        dftr -> counter++;

    skip_spaces (dftr);
            
    return out_nmb;
}

//=============================================================================================

double create_exp (diff_tree* dftr, FILE* formula)
{
    skip_spaces (dftr);
    sign s = POS;

    if (*dftr -> counter == '-')
    {
        dftr -> counter++;
        s = NEG;  
    }

    double res_nmb = create_t (dftr, formula) * s;

    while (*dftr -> counter == '+' || *dftr -> counter == '-')
    {
        if (*dftr -> counter == '+')
        {
            dftr -> counter++;
            s = POS;
        }
        else if (*dftr -> counter == '-')
        {
            dftr -> counter++;
            s = NEG; 
        }   

        skip_spaces (dftr);

        res_nmb += create_t (dftr, formula) * s;
    }

    skip_spaces (dftr);
    
    return res_nmb;
}

//=============================================================================================

double create_t (diff_tree* dftr, FILE* formula)
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
        }
        else if (*dftr -> counter == '/')
        {
            dftr -> counter++;
            res_nmb /= create_w (dftr, formula);
        }   
    }

    skip_spaces (dftr);

    return res_nmb;
}

//=============================================================================================

double create_p (diff_tree* dftr, FILE* formula)
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

    return res_nmb;
}

//=============================================================================================

double create_w (diff_tree* dftr, FILE* formula)
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
            return NAN;
        }
        
        degrees [nmb_degr++] = create_p (dftr, formula);

        skip_spaces (dftr);
    }
    
    while (nmb_degr != 0)
    { 
        x = pow (degrees [--nmb_degr], x);
    }

    skip_spaces (dftr);

    return pow (res_nmb, x);
}

//=============================================================================================

inline void skip_spaces (diff_tree* dftr)
{
    while (isspace (*dftr -> counter))
        dftr -> counter++;   
}

//=============================================================================================