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
    res[0] = ft_strdup(new);
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

char *quotes_remove(char *str)
{
  int   begin;
  char  quote;
  int   start;
  int   end;
  char  *cmd;
  char  *mini_cmd;
  int   i;//for testing whiles

  begin = 0;
  i = 0;
  start = 0;
  end = 0;
  cmd = NULL;
  while (str[start])
  {
    mini_cmd = NULL;
    if (str[start] == '\"' || str[start] == '\'')
    {
      quote = str[start];
      start++;
      end = start;
      while (str[end] != quote && str[end])
        end++;
      if (str[end] == '\0')
        return (NULL);
      mini_cmd = ft_substr(str, start, end - start);
      start = end + 1;
      cmd = ft_strnjoin(cmd, mini_cmd, 0);
      free(mini_cmd);
    }
    else
    {
      cmd = ft_strnjoin(cmd, str + start, 1);
      start++;
    }
  }
  if (cmd == NULL)
    return (str);
  return (cmd);
}

t_data  *ft_split_args(char *str, int *i)
{
  int     start;
  int     end;
  char    *cmd;
  t_data  *data;
  char    **args;
  char    quote;

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
      {
        if (str[end] == '\"' || str[end] == '\'')
        {
          quote = str[end];
          end++;
          while (str[end] != quote && str[end])
            end++;
        }
        if (str[end])
          end++;
      }
      cmd = quotes_remove(ft_substr(str, start, end - start));
      if (cmd == NULL)
        return (NULL);
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

void  free_table(char **args)
{
  int i;

  i = 0;
  while (args[i])
  {
    free(args[i]);
    i++;
  }
  free(args);
}

void    del_elem_char(t_data *data, int i)
{
  char  **new;
  int   size;
  int   deff;

  deff = 0;
  size = 0;
  while (data->args[size])
    size++;
  new = (char **)malloc((sizeof(char *) * size) - 1);
  size = 0;
  while (data->args[size])
  {
    if (size == i)
      deff++;
    else
      new[size - deff] = ft_strdup(data->args[size]);
    size++;
  }
  free_table(data->args);
  data->args = new;
}

t_files_list  *add_last(t_files_list **head, t_files_list *new)
{
  t_files_list *curr;

  if (*head == NULL)
    *head = new;
  else 
  {
    curr = *head;
    while (curr->next)
      curr = curr->next;
    curr->next = new;
  }
  return (*head);
}

t_files_list  *make_new(char *redirection, char *file)
{
  t_files_list  *new;

  new = (t_files_list *)malloc(sizeof(t_files_list));
  new->redirection = ft_strdup(redirection);
  new->file = ft_strdup(file);
  new->next = NULL;
  return (new);
}

void  redirection(t_data *data)
{
  int   i;
  int   j;
  int   passed;
  char   **reds_in;
  char   **reds_out;
  char   **cmds;

  reds_in = ft_split("< <<", ' ');
  reds_out = ft_split("> >>", ' ');
  passed = -1;
  while (data)
  {
    i = 0;
    cmds = NULL;
    while (data->args[i])
    {
      j = 0;
      while (reds_in[j])
      {
        if (ft_strncmp(data->args[i], reds_in[j], 2) == 0)
        {
          passed = 1;
          data->in_files = add_last(&data->in_files, make_new(data->args[i], data->args[i + 1]));
          i++;
        }
        j++;
      }
      j = 0;
      while (reds_out[j])
      {
        if (ft_strncmp(data->args[i], reds_out[j], 2) == 0)
        {
          passed = 1;
          data->out_files = add_last(&data->out_files, make_new(data->args[i], data->args[i + 1]));
          i++;
        }
        j++;
      }
      if(passed == -1)
        cmds = ft_tablejoin(cmds, data->args[i]);
      passed= -1;
      i++;
    }
    if (cmds != NULL)
    {
      free_table(data->args);
      data->args = ft_tabledup(cmds);
      free_table(cmds);
    }
    data = data->next;
  }
}

t_data  *lexer(char *str)
{
  int     i;
  int     j;
  t_data  *data;
  t_data  *new;
  int     node;

  j = 0;
  i = 0;
  node = 0;
  data = NULL;
  str = ft_strnjoin(str, " ", 1);
  while (str[i])
  {
    new = ft_split_args(str, &i);
    if (new == NULL)
    {
      printf("syntax error near unexpected token\n");
      return (NULL);
    }
    ft_lstadd_back(&data, new);
  }
  if (syntax_error(data) == NULL)
    return (NULL);
  redirection(data);
  // ==== for debugging ===============================
  // i = 0;
  // while (data)
  // {
  //   node++;
  //   i = 0;
  //   while (data->args[i])
  //   {
  //     printf("cmd = %s\n", data->args[i]);
  //     i++;
  //   }
  //   printf("in files\n");
  //   while (data->in_files) 
  //   {
  //     printf("red = %s, file = %s\n", data->in_files->redirection, data->in_files->file);
  //     data->in_files = data->in_files->next;
  //   }
  //   printf("out files\n");
  //   while (data->out_files) 
  //   {
  //     printf("red = %s, file = %s\n", data->out_files->redirection, data->out_files->file);
  //     data->out_files = data->out_files->next;
  //   }
  //   data = data->next;
  //   if (data != NULL)
  //     printf("|\n");
  // }
  // printf("node = %d\n", node);
  // ==================================================
  return (data);
}

