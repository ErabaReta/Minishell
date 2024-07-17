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
  if (table == NULL)
  {
    res = (char **)malloc(sizeof(char *) * 2);
    res[0] = new;
    res[1] = NULL;
    return (res);
  }
  while (table[i])
    i++;
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

t_data  *ft_split_args(char *str, int *i)
{
  int     start;
  int     end;
  char    *cmd;
  t_data  *data;
  char    **args;

  start = *i;
  end = 0;
  data = ft_lstnew();
  args = (char **)malloc(sizeof(char *));
  args[0] = NULL;
  while (str[start] && str[start] != '|')
  {
    while (str[start] && str[start] == ' ')
      start++;
    while (str[start] && str[start] != '|' && str[start] != ' ')
    {
      end = start;
      while (str[end] && str[end] != ' ' && str[end] != '|')
        end++;
      cmd = ft_substr(str, start, end - start);
      start = end;
      args = ft_tablejoin(args, cmd);
      free(cmd);
    }
  }
  if (str[start] == '|')
    start++;
  *i = start;
  data->args = args;
  return (data);
}

t_data  *lexer(char *str)
{
  int     i;
  int     j;
  t_data  *data;
  t_data  *new;

  j = 0;
  i = 0;
  data = NULL;
  while (str[i])
  {
    new = ft_split_args(str, &i);
    ft_lstadd_back(&data, new);
  }
  i = 0;
  while (data)
  {
    i = 0;
    while (data->args[i])
    {
      printf("cmd = %s\n", data->args[i]);
      i++;
    }
    data = data->next;
  }
  return (data);
}

