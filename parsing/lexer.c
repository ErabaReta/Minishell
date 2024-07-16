#include "../minishell.h"

void  *quotes(char *str, int *start, int *end)
{
  int i;
  char  quote;
  char  *betwen_quotes;

  i = 0;
  quote = '\0';
  betwen_quotes = NULL;
  while (str[i])
  {
    if (str[i] == '\"' || str[i] == '\'')
    {
      quote = str[i];
      i++;
      *start = i;
      *end = *start;
      break ;
    }
    i++;
  }
  while (str[i] != quote)
  {
    if (str[i] == '\0')
    {
      printf("quotes not closed\n");
      break ;
    }
    i++;
  }
  if (str[i] == quote && quote != '\0')
  {
    *end = i;
    betwen_quotes = ft_substr(str, *start, i - *start);
  }
  return (betwen_quotes);
}

char  *str_maker(char *first, char *second)
{
  char  *str;

  str = ft_strnjoin(first, second, 0);
  return (str);
}

char **ft_tablejoin(char **table, char *new)
{
  int     i;
  char   **res;

  i = 0;
  if (new == NULL)
    return (table);
  while (table[i])
    i++;
  printf("%d\n", i);
  res = (char **)malloc(sizeof(char *) * (i + 2));
  i = 0;
  while (table[i])
  {
    res[i] = ft_strdup(table[i]);
    i++;
  }
  res[i++] = ft_strdup(new);
  res[i] = NULL;
  return (res);
}

t_data  *ft_split_args(char *str)
{
  int     i;
  t_data  *data;
  char    *cmd;
  char    **args;

  data = (t_data *)malloc(sizeof(t_data));
  args = (char **)malloc(sizeof(char *));
  args[0] = NULL;
  cmd = NULL;
  i = 0;
  while (str[i] == ' ')
    i++;
  while (str[i] && str[i] != ' ' && str[i] != '|')
  {
    printf("letter = %c\n", str[i]);
    cmd = ft_strnjoin(cmd, &str[i], 1);
    i++;
  }
  printf("cmd = %s\n", cmd);
  args = ft_tablejoin(args, cmd);
  free(cmd);
  cmd = NULL;
  while (str[i] == ' ')
    i++;
  while (str[i] != '|' && str[i])
  {
    printf("letter = %c\n", str[i]);
    cmd = ft_strnjoin(cmd, &str[i], 1);
    i++;
  }
  args = ft_tablejoin(args, cmd);
  i = 0;
  while (args[i])
    printf("args = %s.\n", args[i++]);
  return (data);
}

t_data  *lexer(char *str)
{
  int     i;
  int     j;
  //int     start;
  //int     end;
  t_data  *data = NULL;
  //char    **cmds;

  j = 0;
  i = 0;
  data = ft_split_args(str);
  return (data);
}

