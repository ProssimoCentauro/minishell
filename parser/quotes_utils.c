#include "minishell.h"

static void line_left_shift(char *line, size_t j)
{
    while (line[j])
    {
        line[j] = line[j + 1];
        j++;
    }
}

void remove_quotes(char *line)
{
    size_t j = 0;
    char to_find = 0;

    while (line[j])
    {
        if (line[j] == '"' || line[j] == '\'')
        {
            to_find = line[j];
            line_left_shift(line, j);

            while (line[j] && line[j] != to_find)
                j++;

            if (line[j])
                line_left_shift(line, j);
        }
        else
            j++;
    }
}
