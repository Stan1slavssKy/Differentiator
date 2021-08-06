#include "Onegin.h"

char* read_file (char* file_name, int size_of_file)
{
    assert (file_name);

    FILE* file = fopen (file_name, "rb");
    assert (file);

    char* file_buffer = (char*) calloc (size_of_file, sizeof(char));
    assert (file_buffer);

    fread  (file_buffer, sizeof (char), size_of_file, file);
    fclose (file);

    return file_buffer;
}

//------------------------------------------------------------------------------------------------

int counter_line (char* file_buffer)
{
    assert (file_buffer);

    char* beg_line     = file_buffer;
    char* end_line     = nullptr;
    int   line_counter = 0;

    while ((end_line = strchr (beg_line, '\n')) != nullptr)
    {
        beg_line = end_line + 1;
        line_counter++;
    }

    printf ("The number of rows is %d\n", line_counter);

    return line_counter;
}

//------------------------------------------------------------------------------------------------

int file_size (char* file_name)
{
    assert (file_name);

    struct stat information_buffer = {};

    stat (file_name, &information_buffer);
    printf ("Size of \"%s\" is: %ld bytes.\n", file_name, information_buffer.st_size);

    return information_buffer.st_size;
}

//------------------------------------------------------------------------------------------------

void input_inform (char* file_name, struct text* text_info)
{
    assert (file_name);
    assert (text_info);

    int   size_of_file   = file_size (file_name);
    char* file_buffer    = read_file (file_name, size_of_file);
    int   number_line    = counter_line (file_buffer);

    text_info -> size_of_file   = size_of_file;
    text_info -> number_line    = number_line;
    text_info -> file_buffer    = file_buffer;
}

//------------------------------------------------------------------------------------------------

void place_pointers (struct text* text_info)
{
    assert (text_info);
    assert (text_info -> file_buffer);

    struct str* data = (struct str*) calloc (text_info -> number_line, sizeof (struct str));
    assert (data);

    text_info -> strings = data;

    char* p_beg_str = (text_info -> file_buffer);
    char* p_end_str = nullptr;

    for (int i = 0; i < (text_info -> number_line); i++)
    {
        p_end_str = strchr (p_beg_str, '\n');

        if (p_end_str != nullptr)
            *p_end_str = '\0';
        else 
            p_end_str = strchr (p_beg_str, '\0') + 1;

        (text_info -> strings + i) -> p_begin_str = p_beg_str;
        (text_info -> strings + i) -> str_length  = p_end_str - p_beg_str;

        p_beg_str = p_end_str + 1;
    }
}

//------------------------------------------------------------------------------------------------

void free_memory (struct text* text_info)
{
    assert (text_info               );
  //  assert (text_info -> strings    );
    assert (text_info -> file_buffer);

  //  free (text_info -> strings);
  //  text_info -> strings = nullptr;

    free (text_info -> file_buffer);   
    text_info -> file_buffer = nullptr;
}

//------------------------------------------------------------------------------------------------

char* console_input (int argc, char* argv[])
{
    char* file_name = nullptr;

    if (argc == 2)
    {
        file_name = argv[1];
        printf ("You want read \"%s\"\n", file_name);
        return file_name;
    }
    
    if (argc == 1)
    {
        printf ("You didn't enter the file name. Please return program and enter file name.\n");
        return nullptr;
    }
    
    printf ("Error: to few or too many arguments.\n");
    return nullptr;
}

//------------------------------------------------------------------------------------------------

int skip_spaces (text* text_info)
{
    assert (text_info);
    assert (text_info -> file_buffer);

    char* new_buffer = (char*) calloc (text_info -> size_of_file, sizeof (char));
    char* symbol     = text_info -> file_buffer;
     
    int   idx     = 0;
    int   new_idx = 0;     
    int   space_counter = 0;

    while (symbol[idx] != '\0')
    {
        if (isspace (symbol[idx]))
        {
            while (isspace (symbol[idx]))
                idx++;

            new_buffer[new_idx++] = ' ';
            new_buffer[new_idx++] = symbol[idx++];
            
            space_counter++;
        }

        else    
            new_buffer[new_idx++] = symbol[idx++];
    }

    new_buffer[new_idx] = '\0';

    printf ("[%s]\n", new_buffer);

    free (text_info -> file_buffer);
    text_info -> file_buffer = nullptr;

    text_info -> file_buffer = new_buffer;
    
    space_counter--;
    return space_counter;
}

//------------------------------------------------------------------------------------------------
// делает массив структур лексем и кладет указатель в каждую структуру
void parsing_lexems (text* text_info)
{
    assert (text_info);
    assert (text_info -> file_buffer);

    char* buffer = text_info -> file_buffer;
    char* cmd    = nullptr;

    int   nmb_lexems = token_counter (text_info);

    lexemes* lexems_arr = (lexemes*) calloc (nmb_lexems, sizeof (lexemes));
    assert  (lexems_arr);

    text_info -> lexem = lexems_arr;
    
    cmd = strtok (buffer, " \n");
    (text_info -> lexem) -> lexem_name = cmd;
    printf ("%s\n", cmd);
    
    for (int idx = 1; (cmd = strtok (nullptr, " \n")) != nullptr; idx++)
    {
        (text_info -> lexem + idx) -> lexem_name = cmd;
        printf ("%s\n", (text_info -> lexem + idx) -> lexem_name);
    }

    printf ("\n");
}

//------------------------------------------------------------------------------------------------

int token_counter (text* text_info)
{
    assert (text_info);
    assert (text_info -> file_buffer);

    char* symbol  = text_info -> file_buffer;

    int   idx     = 0;   
    int   token_counter = 0;

    while (symbol[idx] != '\0') 
    {
        if (symbol[idx] == ';')
        {
            while (symbol[idx] != '\n')
            idx++;
        }

        if (isspace (symbol[idx]))
        {
            while (isspace (symbol[idx]))
                idx++;
        }

        if (isascii (symbol[idx]) && isspace (symbol[idx + 1]))
            token_counter++;

        idx++;
    }

   // token_counter--;

    text_info -> number_lexems = token_counter;
    return token_counter;
}

//------------------------------------------------------------------------------------------------