#include "../minishell.h"

void  syntax_error(t_data *data)
{
  int     i;
  int     j;
  t_data  *curr;
  char    **reds;

  i = 0;
  reds = ft_split("< << > >>", ' ');
  curr = data;
  while (curr)
  {
    if (curr->next != NULL)
    {
      if (curr->next->args[0] == NULL || curr->args[0] == NULL)
        printf("syntax error near unexpected token `|'\n");
    }
    curr = curr->next;
  }
  curr = data;
  while (curr)
  {
    while (curr->args[i])
    {
      j = 0;
      while (reds[j])
      {
        if (ft_strncmp(curr->args[i], reds[j], 2) == 0 && curr->args[i + 1] == NULL)
        {
          printf("syntax error near unexpected token %s\n", curr->args[i]);
        }
        j++;
      }
      i++;
    }
    curr = curr->next;
  }
}
