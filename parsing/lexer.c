#include "../minishell.h"

t_data  lexer(char *str)
{
  int     i;
  int     j;
  t_data  *data;

  i = 0;
  data = (t_data *)malloc(sizeof(t_data));
  while (str[i])
  {
    while (str[i] == ' ')
      i++;
    j = i;
    while (str[i] != ' ')
      i++;
    data->cmd = ft_substr(str, j, i - 1);
  }
  return (0);
}

