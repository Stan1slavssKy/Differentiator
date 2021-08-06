#include "diff.h"

//=============================================================================================

int main (int argc, char** argv)
{
    text formula_info = {};

    char* file_name = console_input (argc, argv);
    assert (file_name);

    FILE* formula = fopen ("test", "rb");
    assert (formula);

    create_diff_article (&formula_info, formula, file_name);

    fclose (formula);
    free_memory (&formula_info);

    return 0;
}

//=============================================================================================