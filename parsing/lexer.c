#include "../minishell.h"

int lexer(char *str)
{
  int i;
  int j;

  i = 0;
  while (str[i])
  {
    while (str[i] == ' ')
      i++;
    j = i;
    while (str[i] != ' ')
      i++;
    ft_substr(str, j, i - 1);
  }
  return (0);
}

