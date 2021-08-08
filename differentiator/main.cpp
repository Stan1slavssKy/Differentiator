#include "diff.h"

//=============================================================================================

int main (int argc, char** argv)
{
    text formula_info = {};

    char* file_name = console_input (argc, argv);
    assert (file_name);

    create_diff_article (&formula_info, file_name);

    free_memory (&formula_info);

    return 0;
}

//=============================================================================================