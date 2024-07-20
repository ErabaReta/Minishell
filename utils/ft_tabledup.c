#include "../minishell.h"
char  **ft_tabledup(char **table)
{
  int   i;
  char  **res;

  i = 0;
  while (table[i])
    i++;
  res = (char **)malloc(sizeof(char *) * (i + 1));
  i = 0;
  while (table[i])
  {
    res[i] = ft_strdup(table[i]);
    i++;
  }
  res[i] = NULL;
  return (res);
}
