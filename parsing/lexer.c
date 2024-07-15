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

char **ft_split_args(char *str)
{
  int i;
  int start;
  int end;

  i = 0;
  while (str[i])
  {
    if (str[i] == '\"' || str[i] == '\'')
    {
      start = i;
      while (str[i] && str[i] != '\"' & str[i] != '\'')
      {
        i++;
      }
      if (str[i] == '\"' || str[i] == '\'')
        end = i;
    }
    if (str[i] == '\0')
        printf("quote not closed\n");
    else
    {
      end = i;
    }
  }
}

t_data  *lexer(char *str)
{
  int     i;
  int     j;
  //int     start;
  //int     end;
  t_data  *data = NULL;
  char    **cmds;

  j = 0;
  i = 0;
  cmds = ft_split_args(str);
  i = 0;
  while (cmds[i])
    printf("quotes = %s\n", cmds[i++]);
  return (data);
}

